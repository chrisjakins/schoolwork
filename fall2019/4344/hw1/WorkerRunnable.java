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
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Date;

public class WorkerRunnable implements Runnable {

    protected Socket clientSocket = null;
    protected String serverText = null;

    public WorkerRunnable(Socket clientSocket, String serverText) {
        this.clientSocket = clientSocket;
        this.serverText   = serverText;
    }

    public void run() {
        try {
            InputStream input = clientSocket.getInputStream();
            OutputStream output = clientSocket.getOutputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            String line = reader.readLine();
            System.out.println(line);
            /*
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            */

            // 200 OK
            File file = new File("./hw1/index.html");
            int fileLength = (int) file.length();

            String response = "HTTP/1.1 200 OK\nDate: " + new Date() + "\nServer: My Server\nContent-type: text/html\nContent-length: " + fileLength + "\n\n";

            output.write(response.getBytes());
            Files.copy(Paths.get("./hw1/index.html"), output);
            output.flush();

            System.out.println("Request processed: ");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String readFileData(File file, int length) throws IOException {
        String data = "";
        BufferedReader fileIn = null;
        try {
            fileIn = new BufferedReader(new FileReader(file));
            String st;
            while ((st = fileIn.readLine()) != null) {
                data += st;
            }
        } finally {
            if (fileIn != null) fileIn.close();
        }
        return data;
    }
}
