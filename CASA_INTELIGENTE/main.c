#include "Habitaciones.h"
#include "Menu.h"

#define PUERTO 8080
#define MAX_CLIENTES 5

int clientes_activos = 0;
pthread_mutex_t mutex_clientes; //= PTHREAD_MUTEX_INITIALIZER;
pthread_t hilos[MAX_CLIENTES]; // guardar los hilos
int hilo_cant = 0;

t_habitacion habitaciones[CANT_HABITACIONES]; ///variable global?

// Función que manejará cada cliente en un hilo separado
void* manejar_cliente(void* client_socket_ptr) {
    int client_socket = *(int*)client_socket_ptr;
    free(client_socket_ptr);  // Liberar memoria reservada en main

    char buffer[TAM_BUFFER];
    int bytes_leidos;

    printf("Cliente conectado. Socket: %d\n", client_socket);
    send(client_socket, "Conectado al servidor.\n", 24, 0);

    bytes_leidos = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if(bytes_leidos){
        buffer[bytes_leidos] = '\0';  // Asegurar terminación de cadena
        if(strncmp(buffer, "INICIAR", 7) == 0){
            seleccion_habitaciones_sock(habitaciones, client_socket);
            send(client_socket, "bye", 4, 0);
        }
    }
    printf("Cliente desconectado. Socket: %d\n", client_socket);
    close(client_socket);

    pthread_mutex_lock(&mutex_clientes);
    clientes_activos--;
    printf("Clientes Activos %d\n", clientes_activos);
    pthread_mutex_unlock(&mutex_clientes);

    return NULL;
}

int main(int argc, char * argv[])
{
    ///CARGAMOS LAS HABITACIONES DE LA CASA A MEMORIA
    inicializar_habitaciones(habitaciones, argv[1]);
    
    ///INICIAR SERVIDOR
    int socket_casa, *socket_cliente_ptr;
    struct sockaddr_in CASA_addr, cliente_addr;
    socklen_t addr_len = sizeof(cliente_addr); //un tamaño del socket
    pthread_mutex_init(&mutex_clientes, NULL);
    fd_set fd_leidos;   ///permite multiples lecturas y escrituras simultaneas con Select()
    struct timeval tiempo_fuera;    ///timpo que el select va a esperar para no bloquearse
    int fd_sock;

    ///CONFIGURAR LOS SOCKETS
    socket_casa = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_casa == -1){
        perror("Error al crearel socket");
        exit(EXIT_FAILURE);
    }
    fd_sock = socket_casa;
    CASA_addr.sin_family = AF_INET;
    CASA_addr.sin_port = htons(PUERTO);
    CASA_addr.sin_addr.s_addr = INADDR_ANY;

    //Enlazo al puerto con bind
    if(bind(socket_casa, (struct sockaddr*)&CASA_addr, sizeof(CASA_addr)) < 0){
        perror("Error en bind");
        close(socket_casa);
        exit(EXIT_FAILURE);
    }
    //Escucho conexiones entrantes
    if(listen(socket_casa, MAX_CLIENTES) < 0){ ///probar cola de espera
        perror("Error en listen");
        close(socket_casa);         ///EL SERVIDOR SE CIERRA SI HAY MAS DEL MAXIMO DE CLIENTES
        exit(EXIT_FAILURE);
    }
    printf("Servidor escuchando en el puerto %d...\n", PUERTO);
    ///CREACION DE HILOS PARA MULTIPLES CLIENTES
    while (1)
    {    
        FD_ZERO(&fd_leidos); ///inicializo file descriptor
        FD_SET(socket_casa, &fd_leidos);
        
        tiempo_fuera.tv_sec = 10;    //10 segundo
        tiempo_fuera.tv_usec = 0;   //microsegundos
        
        int actividad = select(fd_sock + 1, &fd_leidos, NULL, NULL, &tiempo_fuera);
        if(actividad < 0)
        {
            perror("Select");
            break;
        }
        if(actividad == 0)
        {
            //tiempo fuera verificamos si no hoy clinete nuevo. Se puede cerrar?
            pthread_mutex_lock(&mutex_clientes);
            printf("Timeout: activos=%d, hilos=%d\n", clientes_activos, hilo_cant);
            if(clientes_activos == 0 && hilo_cant > 0)
            {
                pthread_mutex_unlock(&mutex_clientes);
                break;
            }
            pthread_mutex_unlock(&mutex_clientes);
            continue;
        }
        if (FD_ISSET(socket_casa, &fd_leidos))
        {
            int cliente_socket = accept(socket_casa, (struct sockaddr *)&cliente_addr, &addr_len);
            if (cliente_socket < 0)
            {
                perror("Error en accept");
                continue;
            }
            pthread_mutex_lock(&mutex_clientes);
            clientes_activos++;
            printf("clintes activos %d\n", clientes_activos);
            pthread_mutex_unlock(&mutex_clientes);

            // Asignar memoria para poder pasar como argumento al hilo
            socket_cliente_ptr = malloc(sizeof(int));
            *socket_cliente_ptr = cliente_socket;

            // creo un hilo para manejar al cliente
            if (pthread_create(&hilos[hilo_cant], NULL, manejar_cliente, socket_cliente_ptr) != 0)
            {
                perror("Error al crear el hilo");
                free(socket_cliente_ptr);
                close(cliente_socket);
            }
            hilo_cant++;
            printf("Cantidad de Hilos %d\n", hilo_cant);
        }
    }

    // Esperar que todos los hilos terminen
    for (int i = 0; i < hilo_cant; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    close(socket_casa);
    printf("Servidor cerrado porque todos los clientes terminaron.\n");
    
    return 0;
}
