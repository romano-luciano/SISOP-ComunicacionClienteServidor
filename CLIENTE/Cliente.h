#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "172.24.64.1"
#define SERVER_PORT 8080
#define TAM_BUFFER 1024

void mostrar_menu() {
    ///menu de inicio del servidor
    printf("\n--- MENÚ ---\n");
    printf("I. Iniciar Servidor\n");
    printf("S. Salir\n");
    printf("Seleccione una opción: ");
}
