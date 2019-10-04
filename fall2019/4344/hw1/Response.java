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
        System.out.println("Processing Client on Socket " + this.clientSocket.getPort());
        try {
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();

            File currDirectory = new File(System.getProperty("user.dir") + File.separator + "hw1");
            handleRequest(input, output, currDirectory);

            input.close();
            output.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void handleRequest(InputStream in, OutputStream out, File dir) throws Exception {
		String line;
		BufferedReader bf = new BufferedReader(new InputStreamReader(in));
		while ((line = bf.readLine()) != null) {
			if (line.length() <= 0) {
				break;
			}
			if (line.startsWith("GET")) {
				String filename = line.split(" ")[1].substring(1);
				File resource = new File(dir + File.separator + filename);

                int httpCode = getHTTPCode(resource);
                System.out.println("RESPONSE CODE : " + httpCode);
                System.out.println("Requested :: " + resource.toString());
                populateResponse(resource, out, httpCode);
				break;
			}
		}
    }

    private int getHTTPCode(File file) {
        if (file.exists() && !file.isDirectory()) {
            return 200;
        }
        if (file.getName().equals(Server.movedFile)) {
            return 301;
        }
        return 404;
    }

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
