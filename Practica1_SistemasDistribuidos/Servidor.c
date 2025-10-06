// Servidor.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 4444
#define BUFFER_SIZE 256

int main() {
    WSADATA wsa;
    SOCKET sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    int cli_len;
    char buffer[BUFFER_SIZE];
    int num;

    // Inicializar WinSock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error al iniciar Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    // Crear socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configurar dirección
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Asociar socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Error en bind: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Escuchar
    listen(sockfd, 5);
    printf("Servidor esperando conexiones en puerto %d...\n", PORT);

    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    if (newsockfd == INVALID_SOCKET) {
        printf("Error en accept: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Cliente conectado.\n");

    // Bucle de comunicación
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = recv(newsockfd, buffer, BUFFER_SIZE-1, 0);
        if (n <= 0) {
            printf("Conexión cerrada por el cliente.\n");
            break;
        }

        num = atoi(buffer);
        printf("Servidor recibió: %d\n", num);

        if (num == 0) {
            printf("Cliente envió 0. Cerrando conexión.\n");
            break;
        }

        num++;
        sprintf(buffer, "%d", num);
        send(newsockfd, buffer, strlen(buffer), 0);
        printf("Servidor respondió: %s\n", buffer);
    }

    closesocket(newsockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
