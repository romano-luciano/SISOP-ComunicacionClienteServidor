#include "Cliente.h"

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

    // Menú interactivo
    while (1) {
        mostrar_menu();
        scanf("%c", &opcion);
        getchar(); // limpiar '\n'

        if (opcion == 'I') {
            send(socket_cliente, "INICIAR", 4, 0);
            // Recibir respuesta
            system("clear");
            while ((bytes = recv(socket_cliente, buffer, TAM_BUFFER - 1, MSG_DONTWAIT)) > 0) {
                buffer[bytes] = '\0';
                printf("%s", buffer);
                usleep(100000); // pequeña espera
                opcion = getchar();
                send(socket_cliente, opcion, 1, 0);
                system("clear");
            }
        }else if (opcion == 'S') {
            send(socket_cliente, "SALIR", 6, 0);
            break;
        } else {
            printf("Opción inválida.\n");
        }
    }

    close(socket_cliente);
    return 0;
}
