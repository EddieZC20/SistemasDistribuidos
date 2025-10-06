import java.net.*;
import java.io.*;

public class ProtocoloTocToc {
    private static final int ESPERANDO = 0;
    private static final int SALUDO_ENVIADO = 1;

    private int estado = ESPERANDO;

    public String processInput(String textoRecibido) {
        String textoDeSalida = null;

        if (estado == ESPERANDO) {
            // primera llamada con null → enviamos saludo
            textoDeSalida = "Hola, soy el servidor!";
            estado = SALUDO_ENVIADO;
        } else if (estado == SALUDO_ENVIADO) {
            // cuando el cliente responde → cerramos la conversación
            textoDeSalida = "Adios.";
            estado = ESPERANDO; // reiniciamos por si se conecta otro cliente
        }

        return textoDeSalida;
    }
}
