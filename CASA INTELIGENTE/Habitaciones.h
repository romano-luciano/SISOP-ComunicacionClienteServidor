#ifndef HABITACIONES_H_INCLUDED
#define HABITACIONES_H_INCLUDED
#define CANT_HABITACIONES 5
#include "Dispositivos.h"

typedef struct
{
    char nombre_habitacion[20];
    t_luz * luces;
    unsigned cant_luces;
    t_aire * aires; ///Va a tener asignacion dinamica de memoria, liberar memoria al finalizar.
    unsigned cant_aires;
    t_televisor * tele;

}t_habitacion;

void inicializar_habitaciones(t_habitacion * habitaciones);
///PATIO|3|FALSE;50;BLANCO|FALSE;10;ROJO|FALSE;60;VERDE|
///BANIO|1|FALSE;50;BLANCO|0|0
#endif // HABITACIONES_H_INCLUDED
