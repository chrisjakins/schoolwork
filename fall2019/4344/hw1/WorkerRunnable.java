package hw1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.ServerSocket;
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
            PrintWriter out = new PrintWriter(output);

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            // 200 OK
            File file = new File("./hw1/index.html");
            int fileLength = (int) file.length();
            System.out.println(file.toString());
            byte[] fdata = readFileData(file, fileLength);

            out.println("HTTP/1.1 200 OK");
            out.println("Server: CSE4344 Multithreaded HTTP Server");
            out.println("Date: " + new Date());
            out.println("Content-type: text/html");
            out.print("Content-length: " + fileLength);
            out.print("/r/n");
            out.flush();

            //System.out.println(fdata);
            //output.write(fdata, 0, fileLength);
            //output.flush();

            output.close();
            input.close();
            out.close();
            reader.close();
            System.out.println("Request processed: ");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private byte[] readFileData(File file, int length) throws IOException {
        FileInputStream fileIn = null;
        byte[] data = new byte[length];
        try {
            fileIn = new FileInputStream(file);
            fileIn.read(data);
        } finally {
            if (fileIn != null) fileIn.close();
        }
        return data;
    }
}
