#include "Habitaciones.h"
#include "Menu.h"

#define PUERTO 8080
#define MAX_CLIENTES 5

int clientes_activos = 0;
pthread_mutex_t mutex_clientes; //= PTHREAD_MUTEX_INITIALIZER;
int actividad = 0; ///hubo actividad en el servidor

typedef struct
{
    struct sockaddr_in cliente_dir;
    socklen_t tam_dir_cliente;
    int socket_casa;
}t_cliente;

t_habitacion habitaciones[CANT_HABITACIONES]; ///variable global?

void* manejar_cliente(void* client_socket_ptr);
void* aceptar_clientes(void *cliente_t);

int main(int argc, char * argv[])
{
    ///CARGAMOS LAS HABITACIONES DE LA CASA A MEMORIA
    inicializar_habitaciones(habitaciones, argv[1]);

    ///INICIAR SERVIDOR
    int socket_casa;
    struct sockaddr_in CASA_addr;
    t_cliente cliente;

    cliente.tam_dir_cliente = sizeof(cliente.cliente_dir); //un tamaño del socket
    pthread_mutex_init(&mutex_clientes, NULL);
    pthread_t hilo_accept;

    ///CONFIGURAR LOS SOCKETS
    socket_casa = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_casa == -1){
        perror("Error al crearel socket");
        exit(EXIT_FAILURE);
    }
    
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
        close(socket_casa);
        exit(EXIT_FAILURE);
    }
    printf("Servidor escuchando en el puerto %d...\n", PUERTO);
    cliente.socket_casa = socket_casa;  // Asignar el socket correctamente

    ///CREACION DE HILO PARA MULTIPLES CLIENTES
    pthread_create(&hilo_accept, NULL, aceptar_clientes, &cliente);
    while (1)
    {
        sleep(1); // Esperar 1 segundo
        pthread_mutex_lock(&mutex_clientes);
        if(clientes_activos == 0 && actividad > 0)
        {
            // No hay clientes activos, cerramos el servidor
            printf("No hay clientes activos. Cerrando servidor...\n");
            pthread_mutex_unlock(&mutex_clientes);
            break;
        }
        pthread_mutex_unlock(&mutex_clientes);
    }
    close(socket_casa);
    printf("Servidor cerrado porque todos los clientes terminaron.\n");
    pthread_mutex_destroy(&mutex_clientes);
    return 0;
}
//Aceptar clientes y generar hilos
void* aceptar_clientes(void *cliente_t)
{
    t_cliente cliente = *(t_cliente*)cliente_t;
    while (1)
    {
        pthread_mutex_lock(&mutex_clientes);
        int current_clients = clientes_activos;
        pthread_mutex_unlock(&mutex_clientes);

        if (current_clients >= MAX_CLIENTES) {
            // Esperar un poco para evitar busy wait
            //usleep(100000); // 100ms
            sleep(1); // Esperar 1 segundo
            continue;
        }
        int sock_cliente = accept(cliente.socket_casa, (struct sockaddr *)&cliente.cliente_dir, &cliente.tam_dir_cliente);
        if (sock_cliente < 0)
        {
            perror("Error en accept");
            break;
        }
        pthread_mutex_lock(&mutex_clientes);
        if (actividad == 0)
            actividad = 1;
        clientes_activos++;
        printf("clientes activos %d\n", clientes_activos);
        pthread_mutex_unlock(&mutex_clientes);

        // Asignar memoria para poder pasar como argumento al hilo
        int *socket_cliente_ptr = malloc(sizeof(int));
        *socket_cliente_ptr = sock_cliente;

        // creo un hilo para manejar al cliente
        pthread_t hilo_cli;
        if (pthread_create(&hilo_cli, NULL, manejar_cliente, socket_cliente_ptr) != 0)
        {
            perror("Error al crear el hilo");
            free(socket_cliente_ptr);
            close(sock_cliente);
            pthread_mutex_lock(&mutex_clientes);
            clientes_activos--;
            // printf("Clientes Activos %d\n", clientes_activos);
            pthread_mutex_unlock(&mutex_clientes);
        }
        else
            pthread_detach(hilo_cli);
    }
}
// Función que manejará cada cliente en un hilo separado
void* manejar_cliente(void* client_socket_ptr) 
{
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