#include "Menu.h"

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones_sock(t_habitacion *hab, int sock_cli)
{
    char buffer[TAM_BUFFER];
    do
    {
        validar_opciones_sock(OPC_MENU_HAB, MENU_HABITACIONES, sock_cli, buffer);
        switch (*buffer)
        {
            case 'A':///DORMITORIO 1
                seleccion_dispositivos_sock(&hab[DORMITORIO_1], sock_cli);
                break;
            case 'B':///BAÑO
                seleccion_dispositivos_sock(&hab[BANIO], sock_cli);
                break;
            case 'C':///COCINA
                seleccion_dispositivos_sock(&hab[COCINA], sock_cli);
                break;
            case 'D':///DORMITORIO 2
                seleccion_dispositivos_sock(&hab[DORMITORIO_2], sock_cli);
                break;
            case 'L':///LIVING
                seleccion_dispositivos_sock(&hab[LIVING], sock_cli);
                break;
            case 'P':///PATIO
                seleccion_dispositivos_sock(&hab[PATIO], sock_cli);
                break;
        }
        ///GUARDAR Y ESCRIBIR EL ARCHIVO
    } while (*buffer != 'S');
}
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos_sock(t_habitacion *hab, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER], opc_disp[CANT_HABITACIONES-1];
    int baytes_escritos;
    vector_opc_disp_sock(hab, opc_disp);
    do
    {
        baytes_escritos = sprintf(menu_aux, MENU_DISPOSITIVOS_2, hab->nombre_habitacion,
                                                                hab->cant_aires ? "A - Aires\n":" ",
                                                                hab->cant_luces ? "L - Luces\n":" ",
                                                                hab->hay_tele ? "T - Smart TV\n":" ");
        validar_opciones_sock(opc_disp, menu_aux, sock_cli, buffer);
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
void Menu_Aires_sock(t_aire * aires, int cant_aires, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int i, res, baytes_escritos = 0, opc_cli;
    do
    {
        for(i=0;i<cant_aires;i++){
            baytes_escritos += sprintf(menu_aux + baytes_escritos,
                                    "AIRE %d\n------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\nINDIQUE EL NUMERO DE AIRE:",
                                    i + 1,
                                    aires[i].estado ? "ENCENDIDO" : "APAGADO",
                                    aires[i].modo, aires[i].temperatura) + 1;
        }
        if(cant_aires > 1)
            opc_cli = Validar_Nro_Dispositivo_sock(cant_aires, sock_cli, buffer, menu_aux);
        else
            opc_cli = 1;
        if(*buffer != 'S')
            validar_opciones_sock(OPC_MENU_AIRES, MENU_AIRES, sock_cli, buffer);
        switch(*buffer)
        {
            case 'E':///MODIFICAR ESTADO
                res = aire_encendido(&aires[opc_cli - 1]);
                send(sock_cli, res?"SE ENCENDIO EL AIRE\n":"ERROR AL ENCENDER EL AIRE\n", res?21:27,0);
                /*
                if(res = aire_encendido(&aires[opc_cli - 1]))
                    puts("SE MODIFICO EL ENCENDIDO");
                else
                    puts("ERROR AL MODIFICAR ENCENDIDO");
                */
                break;
            case 'M':///MENU Y MODIFICACION DE MODO
                //aire_modo(&aires[opc_cli - 1]);
                /*
                if(res = aire_modo(&aires[opc_cli - 1]))
                    puts("SE MODIFICO EL MODO");
                else
                    puts("ERROR AL MODIFICAR MODO");
                */
                break;
            case 'T':///MODIFICAR TEMPERATURA
                //aire_temperatura(&aires[opc_cli - 1]);
                /*
                if(res = aire_temperatura(&aires[opc_cli - 1]))
                    puts("SE MODIFICO LA TEMPERATURA");
                else
                    puts("ERROR AL MODIFICAR MODO");
                */
                break;
        }
        } while (*buffer != 'S');

}
void Menu_Luces_sock(t_luz *luces, int cant_luces, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int i, baytes_escritos = 0, opc_cli;
    do
    {
        for(i=0;i<cant_luces;i++){
            baytes_escritos += sprintf(menu_aux + baytes_escritos,
                                        "LUZ %d\n------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\nINDIQUE EL NUMERO DE LUZ:",
                                        i + 1,
                                        luces[i].estado ? "ENCENDIDO" : "APAGADO",
                                        luces[i].intensidad, luces[i].color) + 1;
        }
        opc_cli = Validar_Nro_Dispositivo_sock(cant_luces, sock_cli, buffer, menu_aux);
        if(*buffer != 'S')
            validar_opciones_sock(OPC_MENU_AIRES, MENU_AIRES, sock_cli, buffer);
        switch (*buffer)
        {
        case 'E': ///ENCIENDE LA LUZ
            luz_encendido(&luces[opc_cli - 1]);
            break;
        case 'C':///CAMBIA EL COLOR
            break;
        case 'I':///MODIFICA LA INTENSIDAD
            break;
        }
    } while (*buffer != 'S');
}
void Menu_Smart_TV_sock(t_televisor *smart, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    do
    {
        sprintf(menu_aux, "SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n",
                        smart->estado ? "ENCENDIDO" : "APAGADO",
                        smart->volumen,
                        smart->fuente);
        validar_opciones_sock(OPC_MENU_SMART_TV, menu_aux, sock_cli, buffer);
        switch(*buffer)
        {
            case 'E':
                smart_encendido(smart);
                break;
            case 'F':
                //smart_fuente(smart);
                break;
            case 'V':
                //smart_volumen(smart);
                break;
        }
    } while (*buffer != 'S');
}
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
    do
    {
        send(sock_cli, menu_atributo, strlen(menu_atributo), 0);
        bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0);
        bytes_leidos?buffer[bytes_leidos] = '\0':sprintf(buffer, "S");
/*        else
            break; ///SALE Y CIERRA SERVIDOR SI NO ENVIA NADA????   */
        *buffer = toupper(*buffer);
        if(strchr(opc_val, *buffer) == NULL)
            send(sock_cli, "OPCION INVALIDA. INGRESE NUEVAMENTE.\n", 38, 0);
        printf("ACA: %s\n", buffer); ///print
    }while (strchr(opc_val, *buffer) == NULL);
    printf("Opcion valida, paso el menu\n"); ///print
}
int Validar_Nro_Dispositivo_sock(int cant_dispositivos, int sock_cli, char *buffer, char *menu_opciones)
{
    int opc_int, bytes_leidos;
    do
    {
        send(sock_cli, menu_opciones, strlen(menu_opciones), 0);
        if((bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0)) > 0)
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
