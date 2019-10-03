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
        System.out.println("=================Server started=================");
        try {
            this.server = new ServerSocket(this.port_);
        } catch (IOException e) {
            System.out.println(e);
        }

        while (true) {
            Socket clientSocket = null;
            try {
                clientSocket = this.server.accept();
                System.out.println("Found Socket " + clientSocket.toString()
                                    + " :: " + clientSocket.getPort());
            } catch (IOException e) {
                System.out.println(e);
            }

            new Thread(new Response(clientSocket, "Server")).start();
        }
    }

    public static void main(String[] args) {
        Server server = new Server(8080);
        server.start();
    }
}
