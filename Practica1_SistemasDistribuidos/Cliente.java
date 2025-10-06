/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.practica1sockets;

/**
 *
 * @author aza06
 */
// Cliente.java
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        String servidor = "127.0.0.1"; // Cambiar si se conecta a otra IP
        int puerto = 4444;

        try (Socket socket = new Socket(servidor, puerto);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             Scanner scanner = new Scanner(System.in)) {

            System.out.println("Conectado al servidor en " + servidor + ":" + puerto);

            int numero;
            while (true) {
                System.out.print("Ingrese un número entero (0 para salir): ");
                numero = scanner.nextInt();

                // Enviar número al servidor
                out.println(numero);

                if (numero == 0) {
                    System.out.println("Cerrando cliente...");
                    break;
                }

                // Recibir respuesta
                String respuesta = in.readLine();
                System.out.println("Servidor respondió: " + respuesta);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
