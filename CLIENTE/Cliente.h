#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define TAM_BUFFER 1024

void mostrar_menu() {
    ///menu de inicio del servidor
    printf("\n--- MENÚ ---\n");
    printf("I. Iniciar Servidor\n");
    printf("S. Salir\n");
    printf("Seleccione una opción: ");
}
int validar_puerto(int puerto) {
    if(puerto <= 1024 || puerto >= 49151){
        do
        {
            printf("El puerto no es valido, ingrese otro puerto.\n");
            scanf("%d", &puerto);
            while (getchar() != '\n');
            system("clear");
        } while (puerto <= 1024 || puerto >= 49151);
    }
    return puerto;
}