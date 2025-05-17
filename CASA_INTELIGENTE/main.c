#include "Habitaciones.h"
#include "Menu.h"


int main(int argc, char * argv[])
{
    t_habitacion habitaciones[CANT_HABITACIONES];

    char path_arch_Hab[30];
    int i;
    for(i=1;i < argc;i++){
        memcpy(&path_arch_Hab, argv[i], 30);
        inicializar_habitaciones(habitaciones, argv[i]);
        ///CARGAMOS LAS HABITACIONES DE LA CASA A MEMORIA
    }
    ///INICIAR SERVIDOR
    ///CONFIGURAR LOS SOCKETS

    ///PRUEBA DE MENU DISPOSITIVOS
    seleccion_habitaciones(habitaciones);
    i = 5;
    /*
    printf(MENU_DISPOSITIVOS_1, habitaciones[i].nombre_habitacion,
                                habitaciones[i].cant_aires?"D":"*",
                                habitaciones[i].cant_luces?"D":"*",
                                habitaciones[i].hay_tele?"D":"*");

    puts("\n");
    printf(MENU_DISPOSITIVOS_2, habitaciones[i].nombre_habitacion,
                                habitaciones[i].cant_aires?"A - Aires\n":"\0",
                                habitaciones[i].cant_luces?"L - Luces\n":"\0",
                                habitaciones[i].hay_tele?"T - Smart TV\n":"\0");
    */
    return 0;
}
