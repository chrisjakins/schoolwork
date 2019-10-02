package hw1;

import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;

class Server {
    private Socket socket = null;
    private ServerSocket server = null;
    private int port_ = 0;
    private Thread runningThread = null;

    public Server(int port) {
        this.port_ = port;
    }

    public void start() {
        System.out.println("Running one");
        try {
            this.server = new ServerSocket(this.port_);
        } catch (IOException e) {
            System.out.println(e);
        }

        while (true) {
            Socket clientSocket = null;
            try {
                clientSocket = this.server.accept();
            } catch (IOException e) {
                System.out.println(e);
            }

            new Thread(new WorkerRunnable(clientSocket, "Server")).start();
        }
    }

    private void handleRequest(String request) {
    
    }

    public static void main(String[] args) {
        System.out.println("Hello world");
        Server server = new Server(8080);
        server.start();
    }
}
