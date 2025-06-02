#ifndef DISPOSITIVOS_H_INCLUDED
#define DISPOSITIVOS_H_INCLUDED

#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

// Dispositivos.h
extern int clientes_activos;
extern int actividad;
extern pthread_mutex_t mutex_clientes;

#define LUCES    0
#define AIRES    1
#define SMART_TV 2

#define TAM_MODO 15
#define TAM_COLOR 10
#define TAM_FUENTE 20

#define TODO_OK 1
#define ERR_COM -1 //Error de comunicacion en sockets

typedef struct
{
    bool estado;
    int intensidad;
    char color[TAM_COLOR]; ///Menu
    pthread_rwlock_t lock;
}t_luz;

typedef struct
{
    bool estado;
    int temperatura;
    char modo[TAM_MODO]; ///Menu
    pthread_rwlock_t lock;
}t_aire;

typedef struct
{
	int estado;
	int volumen;
    char fuente[TAM_FUENTE]; ///Menu
	pthread_rwlock_t lock;
}t_televisor;

/*----------------LUZ-------------------*/
int luz_encendido(t_luz *luz);
int luz_color(t_luz *luz);
int luz_intensidad(t_luz *luz);
/*----------------AIRE------------------*/
int aire_encendido(t_aire *aire);
int aire_modo(t_aire *aire);
int aire_temperatura(t_aire *aire);
/*----------------SMART TV--------------*/
void smart_encendido(t_televisor *tv);
int smart_fuente(t_televisor * tv);
int smart_volumen(t_televisor * tv);
void modificar_volumen_smart(t_televisor * t);
/*------------------LUZ-SOCK---------------------------*/
int luz_encendido_sock(t_luz *luz);
int luz_color_sock(t_luz *luz, int sock_cli);
int luz_intensidad_sock(t_luz *luz, int sock_cli);
/*------------------AIRE-SOCK--------------------------*/
int aire_encendido_sock(t_aire *aire);
int aire_modo_sock(t_aire *aire, int sock_cli);
int aire_temperatura_sock(t_aire *aire, int sock_cli);
/*------------------SMART-TV-SOCK----------------------*/
int smart_encendido_sock(t_televisor *tv);
int smart_fuente_sock(t_televisor * tv, int sock_cli);
int smart_volumen_sock(t_televisor * tv, int sock_cli);

#endif // DISPOSITIVOS_H_INCLUDED
