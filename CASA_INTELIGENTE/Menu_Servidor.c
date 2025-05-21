#include "Menu.h"

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones_sock(t_habitacion *hab, int sock_cli, char *buffer)
{
    do
    {
        validar_opciones_sock(OPC_MENU_HAB, MENU_HABITACIONES, sock_cli, buffer);
        switch (*buffer)
        {
            case 'A':///DORMITORIO 1
                seleccion_dispositivos(&hab[DORMITORIO_1]);
                break;
            case 'B':///BAÑO
                seleccion_dispositivos(&hab[BANIO]);
                break;
            case 'C':///COCINA
                seleccion_dispositivos(&hab[COCINA]);
                break;
            case 'D':///DORMITORIO 2
                seleccion_dispositivos(&hab[DORMITORIO_2]);
                break;
            case 'L':///LIVING
                seleccion_dispositivos(&hab[LIVING]);
                break;
            case 'P':///PATIO
                seleccion_dispositivos(&hab[PATIO]);
                break;
        }
        ///GUARDAR Y ESCRIBIR EL ARCHIVO
    } while (*buffer != 'S');
}
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos_sock(t_habitacion *hab, int sock_cli)
{
    char buffer[TAM_BUFFER], opc_disp[CANT_HABITACIONES-1];
    int bytes_leidos, baytes_escritos;
    vector_opc_disp_sock(hab, opc_disp);
    do
    {
        baytes_escritos = sprintf(buffer, MENU_DISPOSITIVOS_2, hab->nombre_habitacion,
                                                                hab->cant_aires ? "A - Aires\n":" ",
                                                                hab->cant_luces ? "L - Luces\n":" ",
                                                                hab->hay_tele ? "T - Smart TV\n":" ");
        validar_opciones_sock(opc_disp, buffer, sock_cli, buffer); ///envia lo escrito, y dspues lo usa para 
        switch(*buffer)
        {
            case 'A':///AIRES
                Menu_Aires_sock(hab->aires,hab->cant_aires, sock_cli);
                break;
            case 'L':///LUCES
                Menu_Luces_sock(hab->luces, hab->cant_luces, sock_cli);
                break;
            case 'T':///SMART TV
                Menu_Smart_TV_sock(hab->tele, sock_cli);
                break;
        }
    } while (*buffer != 'S');
}
///TERCERMENU, ATRUBUTOS DEL DISPOSITIVO
void Menu_Aires_sock(t_aire * aires, int cant_aires, int sock_cli);
void Menu_Luces_sock(t_luz *luces, int cant_luces, int sock_cli);
void Menu_Smart_TV_sock(t_televisor *smart, int sock_cli);
///UTILITARIAS
void vector_opc_disp_sock(const t_habitacion *hab, char *opc_res)
{
    char * p = opc_res;
    if(hab->cant_aires > 0){
        *p = 'A';
        p ++;
    }
    if(hab->cant_luces > 0){
        *p = 'L';
        p ++;
    }
    if(hab->hay_tele){
        *p = 'T';
        p ++;
    }
    *p = 'S';
    p++;
    *p = '\0';
}
void validar_opciones_sock(const char *opc_val, const char *menu_atributo, int sock_cli, char *buffer)
{
    int bytes_leidos;
    send(sock_cli, menu_atributo, strlen(menu_atributo), 0);
    do
    {
        if(bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0) > 0)
            buffer[bytes_leidos] = '\0';
        else
            break; ///SALE Y CIERRA SERVIDOR SI NO ENVIA NADA????
        *buffer = toupper(*buffer);
        if(strchr(opc_val, *buffer) == NULL)
            send(sock_cli, "OPCION INVALIDA. INGRESE NUEVAMENTE.\n", 38, 0);
    }while (strchr(opc_val, buffer) == NULL);
}
int Validar_Nro_Dispositivo_sock(int cant_dispositivos, int tipo_disp, int sock_cli, char *buffer)
{
    int opc_int, bytes_leidos;
    send(sock_cli, "INDIQUE EL NUMERO DEL DISPOSITIVO.\n", 36, 0);
    do
    {
        if(bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0) > 0)
            buffer[bytes_leidos] = '\0';
        else
            break; ///SALE Y CIERRA SERVIDOR SI NO ENVIA NADA????
        if(*buffer == 's' || *buffer == 'S'){
            *buffer = 'S';
        }else 
            if(isdigit(*buffer)){
            opc_int = *buffer - '0';
                if(opc_int < 1 || opc_int > cant_dispositivos)
                send(sock_cli, "OPCION NO VALIDAD. INGRESE UN NUMERO DISPONIBLE O 'S' PARA SALIR.\n", 67, 0);
            else
                send(sock_cli, "ENTRADA NO VALIDA. INGRESE UN NUMERO O 'S' PARA SALIR.\n", 56, 0);
        }
    } while (*buffer != 'S' && (opc_int < 1 || opc_int > cant_dispositivos));
    return opc_int;
}
