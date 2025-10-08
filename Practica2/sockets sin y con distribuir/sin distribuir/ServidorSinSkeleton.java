import java.io.*;
import java.net.*;

public class ServidorSinSkeleton {
    public static void main(String[] args) {
        int puerto = 12345; // Puerto del servidor

        try (ServerSocket serverSocket = new ServerSocket(puerto)) {
            System.out.println("Servidor esperando conexiones en el puerto " + puerto + "...");

            while (true) {
                Socket socket = serverSocket.accept(); // Espera cliente
                System.out.println("Cliente conectado desde " + socket.getInetAddress());

                // Flujos de datos
                DataInputStream entrada = new DataInputStream(socket.getInputStream());
                DataOutputStream salida = new DataOutputStream(socket.getOutputStream());

                // Recibir datos del cliente
                String operacion = entrada.readUTF();
                int num1 = entrada.readInt();
                int num2 = entrada.readInt();

                // Procesar operación
                int resultado = 0;
                if (operacion.equalsIgnoreCase("sumar")) {
                    resultado = sumar(num1, num2);
                } else if (operacion.equalsIgnoreCase("restar")) {
                    resultado = restar(num1, num2);
                } else {
                    System.out.println("Operación no reconocida: " + operacion);
                }

                // Enviar resultado al cliente
                salida.writeInt(resultado);

                System.out.println("Operación '" + operacion + "' con valores " + num1 + ", " + num2 + " = " + resultado);

                socket.close(); // Cerrar conexión
            }
        } catch (IOException e) {
            System.err.println("Error en el servidor: " + e.getMessage());
        }
    }

    public static int sumar(int a, int b) {
        return a + b;
    }

    public static int restar(int a, int b) {
        return a - b;
    }
}
