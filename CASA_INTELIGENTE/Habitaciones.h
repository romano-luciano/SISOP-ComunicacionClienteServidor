#ifndef HABITACIONES_H_INCLUDED
#define HABITACIONES_H_INCLUDED

#include "Dispositivos.h"

#define CANT_HABITACIONES 6
#define DORMITORIO_1    0
#define BANIO           1
#define COCINA          2
#define DORMITORIO_2    3
#define LIVING          4
#define PATIO           5
#define TAM_BUFFER 1024

typedef struct
{
    char nombre_habitacion[20];
    unsigned cant_luces;
    t_luz * luces;
    unsigned cant_aires;
    t_aire * aires;
    int hay_tele;
    t_televisor * tele;

}t_habitacion;

void cargar_dispositivos(t_habitacion *hab, int cant, char *cad, int disp);
void trozar_aire(char * punt, t_habitacion * h);
void trozar_luz(char * punt, t_habitacion * h);
void trozar_tele(char * punt, t_habitacion * h);
void inicializar_habitaciones(t_habitacion * habitaciones, const char * archivo);
int  actualizar_casa(t_habitacion *casa, const char *archivo);
#endif // HABITACIONES_H_INCLUDED
