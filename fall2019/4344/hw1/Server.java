/***
 * Chris Jakins 1000802309
 */
import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;

/***
 * The main application class. Implements a multithreaded HTTP web server
 * using TCP sockets.
 *
 */
class Server {
    // The client socket.
    private Socket socket = null;

    // The socket that this server will host its connection on.
    private ServerSocket server = null;
    
    // The port that this server will be listening on.
    private int port_ = 0;
    
    // Moved files (example for status 301).
    final public static String movedFile = "movedIndex.html";

    public Server(int port) {
        this.port_ = port;
    }

    /***
     *  Main method for this server. Sets up TCP socket to accept new requests on
     *  and creates a new Response thread for each client request.
     */
    public void start() {
        System.out.println("=================Server started=================");
        System.out.println("Listening on port :: " + this.port_);
        try {
            this.server = new ServerSocket(this.port_);
        } catch (IOException e) {
            System.out.println(e);
        }

        while (true) {
            Socket clientSocket = null;
            try {
                clientSocket = this.server.accept();
                System.out.println("Found Client on Socket " + clientSocket.toString()
                                    + " :: " + clientSocket.getPort());
            } catch (IOException e) {
                System.out.println(e);
            }

            new Thread(new Response(clientSocket)).start();
        }
    }

    public static void main(String[] args) {
        Server server = new Server(8080);
        server.start();
    }
}
