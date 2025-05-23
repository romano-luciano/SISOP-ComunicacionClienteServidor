#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define TAM_BUFFER 1024

void mostrar_menu() {
    ///menu de inicio del servidor
    printf("\n--- MENÚ ---\n");
    printf("I. Iniciar Servidor\n");
    printf("S. Salir\n");
    printf("Seleccione una opción: ");
}

int main() {
    int socket_cliente;
    struct sockaddr_in server_addr;
    char buffer[TAM_BUFFER];
    char opcion;

    // Crear socket
    socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_cliente < 0) {
        perror("Error creando socket");
        return 1;
    }

    // Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Conectar al servidor
    if (connect(socket_cliente, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error conectando al servidor");
        close(socket_cliente);
        return 1;
    }

    // Recibir mensaje de bienvenida
    int bytes = recv(socket_cliente, buffer, TAM_BUFFER - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }
    
    do
    {
        mostrar_menu();
        scanf("%c", &opcion);
        while (getchar() != '\n'); // Limpiar el buffer
        printf("ACA_CLI: %c\n", opcion);
        //getchar(); // limpiar '\n'
        if (opcion == 'I'){
            send(socket_cliente, "INICIAR", 8, 0);
            while (1){
                bytes = recv(socket_cliente, buffer, TAM_BUFFER - 1, 0);
                if(bytes > 0)
                {
                    buffer[bytes] = '\0';
                    printf("%s", buffer); // mensaje del servidor
                }
                else
                {
                    opcion = 'S';
                    break;
                }
                scanf("%c", &opcion);
                while (getchar() != '\n'); // Limpiar el buffer
                send(socket_cliente, &opcion, 2, 0);
                system("clear");
                //printf("ACA_CLI: %c\n", opcion);
            }
        }else if (opcion != 'S'){
            printf("Opcion no valida, intente denuevo:\n");
        }
        //printf("ACA_CLI: %c\n", opcion);
    } while (opcion != 'S');
    
    printf("Se desconcecto del servidor...\n");

    close(socket_cliente);
    return 0;
}
