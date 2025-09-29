import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("127.0.0.1", 6013);
            System.out.println("Connected to server.");

            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            Thread readThread = new Thread(() -> {
                try {
                    String msg;
                    while ((msg = in.readLine()) != null) {
                        System.out.println("Server: " + msg);
                    }
                } catch (IOException e) {
                    System.out.println("Server disconnected.");
                }
            });

            readThread.start();

            BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
            String msg;
            while ((msg = console.readLine()) != null) {
                out.println(msg);
            }

            socket.close();

        } catch (IOException e) {
            System.err.println(e);
        }
    }
}
