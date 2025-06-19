#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TAM_BUFFER 1024
#define TAM_IP 20
void mostrar_menu();
int leer_archivo_configuracion(const char * nombre_archivo, int * puerto_server, char * server_ip);
