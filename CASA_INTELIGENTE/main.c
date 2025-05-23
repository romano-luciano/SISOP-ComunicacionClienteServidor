#include "Habitaciones.h"
#include "Menu.h"

#define PUERTO 8080
#define MAX_CLIENTES 5


t_habitacion habitaciones[CANT_HABITACIONES]; ///variable global?

// Función que manejará cada cliente en un hilo separado
void* handle_client(void* client_socket_ptr) {
    int client_socket = *(int*)client_socket_ptr;
    free(client_socket_ptr);  // Liberar memoria reservada en main

    char buffer[TAM_BUFFER];
    int bytes_read;

    printf("Cliente conectado. Socket: %d\n", client_socket);
    send(client_socket, "Conectado al servidor.\n", 24, 0);

    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';  // Asegurar terminación de cadena
        if(strncmp(buffer, "INICIAR", 7) == 0){
            printf("Entro al Servidor\n");
            seleccion_habitaciones_sock(habitaciones, client_socket);
            //break;
        }else if (strncmp(buffer, "SALIR", 5) == 0) {
            break;
        } else
            send(client_socket, "Comando no reconocido.\n", 24, 0);
    }

    printf("Cliente desconectado. Socket: %d\n", client_socket);
    close(client_socket);
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
    pthread_t tid; //hilo

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
    if(listen(socket_casa, MAX_CLIENTES) < 0){
        perror("Error en listen");
        close(socket_casa);         ///EL SERVIDOR SE CIERRA SI HAY MAS DEL MAXIMO DE CLIENTES
        exit(EXIT_FAILURE);
    }
    printf("Servidor escuchando en el puerto %d...\n", PUERTO);
    ///CREACION DE HILOS PARA MULTIPLES CLIENTES
    while (1)
    {                                                                               //tamaño 
        int cliente_socket = accept(socket_casa, (struct sockaddr*)&cliente_addr, &addr_len);
        if(cliente_socket < 0){
            perror("Error en accept");
            continue;
        }
        //Asignar memoria para poder pasar como argumento al hilo
        socket_cliente_ptr = malloc(sizeof(int));
        *socket_cliente_ptr = cliente_socket;
        //creo un hilo para manejar al cliente
        if(pthread_create(&tid, NULL, handle_client, socket_cliente_ptr) != 0){
            perror("Error al crear el hilo");
            free(socket_cliente_ptr);
            close(cliente_socket);
        }
        // Detach para liberar recursos automáticamente al terminar el hilo
        pthread_detach(tid); //?????
    }
    close(socket_casa);
    
    ///HILOS DE PRUEBA
    /*
    pthread_t hilo_prueba; //declaro el hilo
    pthread_create(&hilo_prueba, NULL, (void*)seleccion_dispositivos, habitaciones); 
    pthread_join(hilo_prueba, NULL); //espero a que terminen los hilos para terminar la ejecucion

    pthread_mutex_t mutex; //declaro mutex
    pthread_mutex_init(&mutex, NULL); //inicializo mutex
    pthread_mutex_lock(&mutex); //bloquea zona critica
    //zona critica
    pthread_mutex_unlock(&mutex);//desbloquea zona critica
    */
    ///PRUEBA DE MENU DISPOSITIVOS
    //seleccion_habitaciones(habitaciones);
    /*--------------------------------------------------------*/
    //primero configurar sockets y probar con un solo cliente
    //junto con el guardado de archivo
    /*---------------------------------------------------------*/
    return 0;
}
