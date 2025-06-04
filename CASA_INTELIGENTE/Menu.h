#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Habitaciones.h"

/*-------------------------HABITACIONES-------------------------*/
#define MENU_HABITACIONES   "CASA INTELIGENTE\n"                \
                            "Elija una habitacion por favor:\n" \
                            "A - Dormitorio grande\n"           \
                            "B - Banio\n"                       \
                            "C - Cocina\n"                      \
                            "D - Dormitorio chico\n"            \
                            "L - Living\n"                      \
                            "P - Patio\n"                       \
                            "S - Salir del SERVIDOR\n"          \
                            "-->"
#define OPC_MENU_HAB "ABCDLPS"
/*--------------------------DISPOSITIVOS----------------------------------*/

#define MENU_DISPOSITIVOS_2  "DISPOSITIVOS\n"                                     \
                            "Elija tipo de dispositivo de: %s\n"                  \
                            "%s"                                                  \
                            "%s"                                                  \
                            "%s"                                                  \
                            "S - Salir\n"                                         \
                            "-->"
#define OPC_MENU_DISP "ALTS"
/*---------------------------AIRES----------------------------------------*/
#define MENU_AIRES  "Seleccione un atributo del aire que desee modificar\n"     \
                    "E - Encendido\n"                                           \
                    "M - Modo\n"                                                \
                    "T - Temperatura\n"                                         \
                    "S - Salir\n"                                               \
                    "-->"
#define OPC_MENU_AIRES "EMTS"

#define MENU_AIRES_MODO "Elija un modo para el aire acondicionado\n"    \
                        "C - Calor\n"                                   \
                        "F - Frio\n"                                    \
                        "V - Ventilacion\n"                             \
                        "S - salir\n"                                   \
                        "-->"
#define OPC_MODO_AIRE "CFVS"
/*-------------------------LUCES-----------------------------------------*/
#define MENU_LUCES  "Elija un atributo de las luces a cambiar\n"        \
                    "C - Color\n"                                       \
                    "E - Encendido\n"                                   \
                    "I - Intensidad\n"                                  \
                    "S - Salir\n"                                       \
                    "-->"
#define OPC_MENU_LUCES "CEIS"

#define MENU_COLORES_LUCES  "Elija un color para las luces\n"           \
                            "A - Amarillo\n"                            \
                            "B - Azul\n"                                \
                            "G - Verde\n"                               \
                            "N - Naranja\n"                             \
                            "R - Rojo\n"                                \
                            "V - Violeta\n"                             \
                            "W - Blanco\n"                              \
                            "S - Salir\n"                               \
                            "-->"
#define OPC_COLORES_LUCES   "ABGNRVWS"
/*------------------------SMART-TV-------------------------------------*/
#define MENU_SMART_TV   "Elija un atributo para modificar del smart\n"  \
                        "E - Encendido\n"                               \
                        "F - Fuente\n"                                  \
                        "V - Volumen\n"                                 \
                        "S - Salir\n"                                   \
                        "-->"
#define OPC_MENU_SMART_TV "EFVS"

#define MENU_FUENTE_TV  "Elija una plataforma para reproducir\n"        \
                        "D - Disney\n"                                  \
                        "N - Netflix\n"                                 \
                        "P - Prime Video\n"                             \
                        "Y - YouTube\n"                                 \
                        "S - Salir\n"                                   \
                        "-->"
#define OPC_FUENTE_TV "DNPYS"
/*-----------------------------------------------------------------------*/

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones(t_habitacion *hab);
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos(t_habitacion *hab);
void vector_opc_disp(const t_habitacion *hab, char *opc_res);
///TERCERMENU, ATRUBUTOS DEL DISPOSITIVO
void Menu_Aires(t_aire * aires, int cant_aires);
void Menu_Luces(t_luz *luces, int cant_luces);
void Menu_SmartTV(t_televisor *smart);
///UTILITARIAS
void validar_atributos(char *opc_cli, const char *opc_val, const char *menu_atributo);
int Validar_Nro_Dispositivo(char * aux, int cant_dispositivos, int tipo_disp);

/*--------------------------------------------------------------------------*/

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones_sock(t_habitacion *hab, int sock_cli);
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos_sock(t_habitacion *hab, int sock_cli);
///TERCERMENU, NUMERO DE DISPOSITIVO
void Menu_Nro_Aires_sock(t_aire * aires, int cant_aires, int sock_cli);
void Menu_Nro_Luces_sock(t_luz *luces, int cant_luces, int sock_cli);
void Menu_Smart_TV_sock(t_televisor *smart, int sock_cli);
///CUARTO MENU, ATRIBUTOS DE DISPOSITIVOS
void menu_aire_sock(t_aire *aire, int sock_cli);
void menu_luz_sock(t_luz *luz, int sock_cli);
///UTILITARIAS
int recibir_mensaje(int sock, char *buffer, int tam);
int enviar_mensaje(int sock, const char *msg);
void vector_opc_disp_sock(const t_habitacion *hab, char *opc_res);
int  validar_opciones_sock(const char *opc_val, const char *menu_atributo, int sock_cli, char *buffer);
int  Validar_Nro_Dispositivo_sock(int cant_dispositivos, int sock_cli, char *buffer, char *menu_opciones);
int  pedir_dispositivo_sock(pthread_rwlock_t *lock, int sock_cli, int disp);

#endif // MENU_H_INCLUDED
