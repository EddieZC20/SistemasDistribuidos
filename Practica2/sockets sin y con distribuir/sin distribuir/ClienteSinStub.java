import java.io.*;
import java.net.*;

public class ClienteSinStub {
    public static void main(String[] args) {
        // Permitir pasar IP y puerto por parámetros
        if (args.length != 3) {
            System.out.println("Uso: java ClienteSinStub <host> <puerto> <operacion>");
            System.out.println("Ejemplo: java ClienteSinStub localhost 12345 sumar");
            return;
        }

        String host = args[0];
        int puerto = Integer.parseInt(args[1]);
        String operacion = args[2]; // "sumar" o "restar"

        try (Socket socket = new Socket(host, puerto)) {
            DataInputStream entrada = new DataInputStream(socket.getInputStream());
            DataOutputStream salida = new DataOutputStream(socket.getOutputStream());

            // Enviar datos al servidor
            salida.writeUTF(operacion);
            salida.writeInt(10); // primer número
            salida.writeInt(4);  // segundo número

            // Recibir resultado
            int resultado = entrada.readInt();
            System.out.println("Resultado de la operación '" + operacion + "': " + resultado);
        } catch (IOException e) {
            System.err.println("Error en el cliente: " + e.getMessage());
        }
    }
}
