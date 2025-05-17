#ifndef DISPOSITIVOS_H_INCLUDED
#define DISPOSITIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define LUCES    0
#define AIRES    1
#define SMART_TV 2

#define TAM_MODO 15
#define TAM_COLOR 10
#define TAM_FUENTE 20

typedef struct
{
    bool estado;
    int intensidad;
    char color[TAM_COLOR]; ///Menu
    pthread_mutex_t mutex;
}t_luz;

typedef struct
{
    bool estado;
    int temperatura;
    char modo[TAM_MODO]; ///Menu
    pthread_mutex_t mutex;
}t_aire;

typedef struct
{
	int estado;
	int volumen;
    char fuente[TAM_FUENTE]; ///Menu
	pthread_mutex_t mutex;
}t_televisor;

/*----------------LUZ-------------------*/
/*----------------AIRE------------------*/
int aire_encendido(t_aire *aire);
int aire_modo(t_aire *aire);
int aire_temperatura(t_aire *aire);
/*----------------SMART TV--------------*/
#endif // DISPOSITIVOS_H_INCLUDED
