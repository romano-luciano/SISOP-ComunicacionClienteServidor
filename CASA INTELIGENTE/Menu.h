#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Habitaciones.h"

/*-------------------------HABITACIONES-------------------------*/
#define MENU_HABITACIONES   "CASA INTELIGENTE\n"                \
                            "Elija una habitacion por favor:\n" \
                            "A - Dormitorio grande\n"           \
                            "B - Baño\n"                        \
                            "C - Cocina\n"                      \
                            "D - Dormitorio chico\n"            \
                            "L - Living\n"                      \
                            "P - Patio\n"                       \
                            "S - Salir\n"                       \
                            "-->"
#define OPC_MENU_HAB "ABCDLS"
/*--------------------------DISPOSITIVOS----------------------------------*/
#define MENU_DISPOSITIVOS_1  "DISPOSITIVOS\n"                                        \
                            "Elija un dispositivo de la habitacion: %s\n"           \
                            "A - Aires (%s)\n"                                       \
                            "L - Luces (%s)\n"                                       \
                            "T - Smart TV (%s)\n"                                    \
                            "S - Salir\n"                                           \
                            "PD: solo los dispositivos con 'D' estan disponibles\n" \
                            "-->"
#define MENU_DISPOSITIVOS_2  "DISPOSITIVOS\n"                                        \
                            "Elija tipo de dispositivo de: %s\n"           \
                            "%s\n"                                                  \
                            "%s\n"                                                  \
                            "%s\n"                                                  \
                            "S - Salir\n"                                           \
                            "-->"
#define OPC_MENU_DISP "ALTS"
/*---------------------------AIRES----------------------------------------*/
#define MENU_AIRES  "Seleccione un atributo del aire que desee modificar\n"  \
                    "E - Encendido\n"                                   \
                    "M - Modo\n"                                        \
                    "T - Temperatura\n"                                 \
                    "S - Salir\n"                                       \
                    "-->"
#define OPC_MENU_AIRES "EMTS"

#define MENU_AIRES_MODO "MODO DE AIRES\n"                               \
                        "Elija un modo para el aire acondicionado\n"    \
                        "C - Calor\n"                                   \
                        "F - Frio\n"                                    \
                        "V - Ventilacion\n"                             \
                        "S - salir\n"                                   \
                        "-->"
#define OPC_MODO_AIRE "CFVS"
/*-------------------------LUCES-----------------------------------------*/
#define MENU_LUCES  "LUCES MULTICOLRES\n"                               \
                    "Elija un atributo de las luces a cambiar\n"        \
                    "C - Color\n"                                       \
                    "E - Encendido\n"                                   \
                    "I - Intencidad\n"                                  \
                    "S - Salir\n"                                       \
                    "-->"
#define OPC_MENU_LUCES "CEIS"

#define MENU_COLORES_LUCES  "COLOR DE LUCES\n"                          \
                            "Elija un color para las luces\n"           \
                            "A - Amarillo\n"                            \
                            "B - Azul\n"                                \
                            "G - Verde\n"                               \
                            "N - Naranja\n"                             \
                            "R - Rojo\n"                                \
                            "V - Violeta\n"                             \
                            "W - Blanco\n"                              \
                            "S - Salir\n"                               \
                            "-->"
#define OPC_COLORES_LUCES   "ABCGNRVWS"
/*------------------------SMART-TV-------------------------------------*/
#define MENU_SMART_TV   "TELEVISION SMART\n"                            \
                        "Elija un atributo para modificar del smart\n"  \
                        "E - Encendido\n"                               \
                        "F - Fuente\n"                                  \
                        "V - Volumen\n"                                 \
                        "S - Salir\n"                                   \
                        "-->"
#define OPC_MENU_SMART_TV "EFVS"

#define MENU_FUENTE_TV  "FUENTE DE LA TELEVISION\n"                     \
                        "Elija una plataforma para reproducir\n"        \
                        "A - AmazonePrime\n"                            \
                        "D - Disney\n"                                  \
                        "N - Netflix\n"                                 \
                        "P - PrimeVideo\n"                              \
                        "Y - YouTube\n"                                 \
                        "S - Salir\n"                                   \
                        "-->"
#define OPC_FUENTE_TV "ADNPYS"
/*-----------------------------------------------------------------------*/

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones(t_habitacion *hab);
int val_opc(char opc);
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos(t_habitacion *hab);
void vector_opc_disp(const t_habitacion *hab, char *opc_res);
#endif // MENU_H_INCLUDED
