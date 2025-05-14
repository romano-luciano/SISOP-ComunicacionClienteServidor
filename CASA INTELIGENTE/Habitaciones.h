#ifndef HABITACIONES_H_INCLUDED
#define HABITACIONES_H_INCLUDED

#define CANT_HABITACIONES 6
#define TAM_BUFFER 100
#include "Dispositivos.h"

typedef struct
{
    char nombre_habitacion[20];
    t_luz * luces;
    unsigned cant_luces;
    t_aire * aires; ///Va a tener asignacion dinamica de memoria, liberar memoria al finalizar.
    unsigned cant_aires;
    int hay_tele;
    t_televisor * tele;

}t_habitacion;

void cargar_dispositivos(t_habitacion *hab, int cant, char *cad, int disp);
void trozar_aire(char * punt, t_habitacion * h);
void trozar_luz(char * punt, t_habitacion * h);
void trozar_tele(char * punt, t_habitacion * h);
void inicializar_habitaciones(t_habitacion * habitaciones, const char * archivo);
///PATIO|3|FALSE;50;BLANCO|FALSE;10;ROJO|FALSE;60;VERDE|
///BANIO|1|FALSE;50;BLANCO|0|0
#endif // HABITACIONES_H_INCLUDED
