#include "Habitaciones.h"
#include "Menu.h"

int main(int argc, char * argv[])
{
    t_habitacion habitaciones[CANT_HABITACIONES]; ///variable global?

    char path_arch_Hab[30];
    int i;
    for(i=1;i < argc;i++){
        memcpy(&path_arch_Hab, argv[i], 30);
        inicializar_habitaciones(habitaciones, argv[i]);
        ///CARGAMOS LAS HABITACIONES DE LA CASA A MEMORIA
    }
    ///INICIAR SERVIDOR
    ///CONFIGURAR LOS SOCKETS
    ///CREAR HILOS DE PRUEBA
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
    seleccion_habitaciones(habitaciones);
    /*--------------------------------------------------------*/
    //primero configurar sockets y probar con un solo cliente
    //junto con el guardado de archivo
    /*---------------------------------------------------------*/
    return 0;
}
