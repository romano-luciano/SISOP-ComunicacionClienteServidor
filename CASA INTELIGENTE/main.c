#include "Habitaciones.h"
#include "Menu.h"


int main(int argc, char *argv[])
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

    ///PRUEBA DE INICIO DE MENU

    return 0;
}
