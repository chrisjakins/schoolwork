package hw1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.ServerSocket;
import java.net.URLConnection;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Date;

public class Response implements Runnable {

    protected Socket clientSocket = null;
    protected String serverText = null;

    public Response(Socket clientSocket, String serverText) {
        this.clientSocket = clientSocket;
        this.serverText   = serverText;
    }

    public void run() {
        System.out.println("Processing " + this.clientSocket.getPort());
        try {
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();

            File currDirectory = new File(System.getProperty("user.dir") + File.separator + "hw1");
            System.out.println(currDirectory.toString());

            handleRequest(input, output, currDirectory);

            input.close();
            output.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void handleRequest(InputStream in, OutputStream out, File dir) throws Exception {
		String line;
        String res;
		BufferedReader bf = new BufferedReader(new InputStreamReader(in));
		while ((line = bf.readLine()) != null) {
			if (line.length() <= 0) {
				break;
			}
			if (line.startsWith("GET")) {
				String filename= line.split(" ")[1].substring(1);
				File resource = new File(dir + File.separator + filename);
                System.out.println("Requested :: " + resource.toString());
				if (resource.isFile()) {
					res = filename;
					populateResponse(resource, out);
				} else {
					String Content_NOT_FOUND = "<html><head></head><body><h1>" +
                        "File Not Found</h1></body></html>";
					
					String REQ_NOT_FOUND = "HTTP/1.1 404 Not Found\n\n";
					String header = REQ_NOT_FOUND+ Content_NOT_FOUND;
					
					out.write(header.getBytes());
				}
				break;
			}
		}
            /*
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            //String line = reader.readLine();
            // 200 OK
            File file = new File("./hw1/index.html");
            int fileLength = (int) file.length();
            String response = "HTTP/1.1 200 OK\nDate: " + new Date()
                               + "\nServer: My Server\nContent-type: "
                               + "text/html\nContent-length: " + fileLength + "\n\n";
            System.out.println("Sending response :" + response + " to "
                                + this.clientSocket.getPort());
            output.write(response.getBytes());
            Files.copy(Paths.get("./hw1/index.html"), output);
            output.flush();
            System.out.println("Request processed: ");
            */
    }

    private void populateResponse(File resource, OutputStream out) throws IOException {
		String REQ_FOUND = "HTTP/1.0 200 OK\n";
		String SERVER = "Server: HTTP server/0.1\n";
		String DATE = "Date: " + new Date();
		String CONTENT_TYPE = "Content-type: "
            + URLConnection.guessContentTypeFromName(resource.getName());
		String LENGTH = "Content-Length: " + (resource.length()) + "\n\n";

		String header = REQ_FOUND + SERVER + DATE + CONTENT_TYPE + LENGTH;
		out.write(header.getBytes());
		
		Files.copy(Paths.get(resource.toString()), out);
		out.flush();
    }
}
