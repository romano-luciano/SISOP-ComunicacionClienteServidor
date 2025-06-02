#include "Cliente.h"

int main() {
    int socket_cliente;
    struct sockaddr_in server_addr;
    char buffer[TAM_BUFFER];
    char opcion[3];

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
        scanf("%s", opcion);
        while (getchar() != '\n'); // Limpiar el buffer
        //printf("ACA_CLI: %c\n", opcion);
        
        if (*opcion == 'I' || *opcion == 'i'){
            if(send(socket_cliente, "INICIAR", 8, 0)<0){
                printf("Cierre inesperado...\n");
                break;
            }
            system("clear");
            while (1){
                bytes = recv(socket_cliente, buffer, TAM_BUFFER - 1, 0);
                if(bytes > 0)
                {
                    buffer[bytes] = '\0';
                    if(strncmp(buffer, "bye", 3) == 0)
                    {
                        printf("hasta luego! vuelva pronto!... :)\n");
                        *opcion = 'S';
                        break;
                    }
                    printf("%s", buffer); // mensaje del servidor
                }
                else
                {
                    printf("Cierre inesperado...\n"); ///manejo de cierre inesperado
                    *opcion = 'S';              ///si recv() no lee nada, cierra la conexion
                    break;
                }
                scanf("%s", opcion);
                while (getchar() != '\n'); // Limpiar el buffer
                if(send(socket_cliente, opcion, sizeof(opcion), 0)<0){
                    printf("Cierre inesperado...\n");
                    *opcion = 'S';
                    break;
                }
                system("clear");
                printf("ACA_CLI: %s\n", opcion);
            }
        }else if (*opcion != 'S' && *opcion != 's'){
            printf("Opcion no valida, intente denuevo:\n");
        }
        //printf("ACA_sali: %s\n", opcion);
    } while (*opcion != 'S');
    
    printf("Se desconecto del servidor...\n");

    close(socket_cliente);
    return 0;
}
