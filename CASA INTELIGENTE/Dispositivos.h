#ifndef DISPOSITIVOS_H_INCLUDED
#define DISPOSITIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

typedef struct
{
    bool estado;
    int intensidad;
    char color[10]; ///Menu
    pthread_mutex_t mutex;
}t_luz;

typedef struct
{
    bool estado;
    int temperatura;
    char modo[10]; ///Menu
    pthread_mutex_t mutex;
}t_aire;

typedef struct
{
	int estado;
	int volumen;
    char fuente[20]; ///Menu
	pthread_mutex_t mutex;
}t_televisor;

#endif // DISPOSITIVOS_H_INCLUDED
