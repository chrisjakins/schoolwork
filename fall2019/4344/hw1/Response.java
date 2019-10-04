/***
 * Chris Jakins 1000802309
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.URLConnection;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Date;

/***
 *  This class creates the proper HTTP response for a client. It is hooked
 *  up to a single socket and sends a single message back.
 *
 *  The messages implemented in this class are:
 *  200 - Request was OK'd and the corresponding file or information is being
 *      sent back.
 *  301 - The file was permanently moved to a different file, and the new
 *      location will be sent back.
 *  404 - The file was not found.
 *
 ***/
public class Response implements Runnable {
    // The client socket to communicate with
    protected Socket clientSocket = null;

    public Response(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    /***
     * This method is the entry point for this class once it is spawned
     * on a new thread.
     *
     * We receive the input and output streams, pass them along to the
     * request handler, and then close both streams.
     */
    public void run() {
        System.out.println("Processing Client on Socket " + this.clientSocket.getPort());
        try {
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();

            // currDirectory will point to the current directory that this application was run from
            // change this to be the root for where files are placed.
            File currDirectory = new File(System.getProperty("user.dir"));
            handleRequest(input, output, currDirectory);

            input.close();
            output.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /***
     *  This function parses the input request, generates the corresponding response, and sends it
     *  out to the client.
     *
     *  @param in The input stream that holds the request from the client.
     *  @param out The output stream on which to send the response back.
     *  @param dir The current working directory.
     */
    private void handleRequest(InputStream in, OutputStream out, File dir) throws Exception {
		String line;
		BufferedReader bf = new BufferedReader(new InputStreamReader(in));
		while ((line = bf.readLine()) != null) {
			if (line.length() <= 0) {
				break;
			}
            // we are only handling get requests
			if (line.startsWith("GET")) {
                // filename will be whatever file the client is requesting.
				String filename = line.split(" ")[1].substring(1);
				File resource = new File(dir + File.separator + filename);

                // 200, 301, 404
                int httpCode = getHTTPCode(resource);
                System.out.println("RESPONSE CODE : " + httpCode);
                System.out.println("Requested :: " + resource.toString());
                populateResponse(resource, out, httpCode);
				break;
			}
		}
    }

    /***
     *  This function determines which HTTP code to produce given that
     *  status of the requested file.
     *
     *  @param file The file to check on the system for.
     *  @return 200, 301, 404 corresponding to the state of the requested file.
     */
    private int getHTTPCode(File file) {
        if (file.exists() && !file.isDirectory()) {
            return 200;
        }
        if (file.getName().equals(Server.movedFile)) {
            return 301;
        }
        return 404;
    }

    /***
     *  Does the string processing to create the properly formatted response, and sends the
     *  full response including the file if applicable back to the client.
     *
     *  @param resource The file requested (if it exists).
     *  @param out The stream to send the information on back to the client.
     *  @param code The corresponding HTTP code.
     */
    private void populateResponse(File resource, OutputStream out, int code) throws IOException {
        String RESPONSE = "HTTP/1.0 ";
        String CONTENT_TYPE = "Content-type: ";
        String LENGTH = "Content-Length: ";
		String SERVER = "Server: CSE4344 HW1 Server\n";
		String DATE = "Date: " + new Date();
        String header;

        switch (code) {
            case 200:
                RESPONSE += "200 OK\n";
                CONTENT_TYPE += URLConnection.guessContentTypeFromName(resource.getName());
                LENGTH += resource.length() + "\n\n";
                header = RESPONSE + SERVER + DATE + CONTENT_TYPE + LENGTH;
                out.write(header.getBytes());
                Files.copy(Paths.get(resource.toString()), out);
                break;
            case 301:
                RESPONSE += "301 Moved Permanently\n";
                CONTENT_TYPE += "text/html";
                LENGTH += "index.html".length() + "\n\nindex.html";
                header = RESPONSE + SERVER + DATE + CONTENT_TYPE + LENGTH;
                out.write(header.getBytes());
                break;
            case 404:
                RESPONSE += "404 Not Found\n\n";
                RESPONSE += "<html><head></head><body><h1>" +
                    "File Not Found</h1></body></html>";
                out.write(RESPONSE.getBytes());
                break;
            default:
                break;
        }
        out.flush();
    }
}
