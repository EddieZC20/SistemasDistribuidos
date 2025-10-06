// ClienteTocToc.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // close()
#include <string.h>     // strlen(), memset()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in
#include <netdb.h>      // gethostbyname()

#define PORT 4444
#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        fprintf(stderr,"Uso: %s hostname\n", argv[0]);
        exit(0);
    }

    // 1. Crear socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al abrir el socket");
        exit(1);
    }

    // 2. Obtener dirección del servidor (ej: localhost o IP)
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error: no existe el host\n");
        exit(0);
    }

    // 3. Preparar estructura de conexión
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr,
           (char *)server->h_addr,
           server->h_length);
    serv_addr.sin_port = htons(PORT);

    // 4. Conectar al servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error al conectar");
        exit(1);
    }

    // 5. Ciclo de comunicación
    while (1) {
        // Recibir mensaje del servidor
        memset(buffer, 0, BUFFER_SIZE);
        n = read(sockfd, buffer, BUFFER_SIZE-1);
        if (n < 0) {
            perror("Error al leer del socket");
            break;
        }
        printf("Servidor: %s\n", buffer);

        if (strncmp(buffer, "Adios.", 6) == 0) {
            break; // el servidor terminó la conversación
        }

        // Escribir mensaje al servidor
        printf("Cliente: ");
        memset(buffer, 0, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE-1, stdin);

        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error al escribir en el socket");
            break;
        }
    }

    close(sockfd);
    return 0;
}
