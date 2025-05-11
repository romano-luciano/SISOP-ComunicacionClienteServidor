#include "Habitaciones.h"

///recive los archivos de los dispositivos por argumentos a main
int main(int argc, char *argv[])
{
    t_habitacion habitaciones[CANT_HABITACIONES];
    int i;
    for(i=1;i<argc;i++){
        inicializar_habitaciones(&habitaciones[i], argv[i]);
        ///le pasamos los archivos para inicializar las variables
    }


    return 0;
}
