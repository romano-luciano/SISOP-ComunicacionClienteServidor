#include "Menu.h"
#include "Dispositivos.h"

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
                Menu_Nro_Aires_sock(hab->aires,hab->cant_aires, sock_cli);
                break;
            case 'L':///LUCES
                Menu_Nro_Luces_sock(hab->luces, hab->cant_luces, sock_cli);
                break;
            case 'T':///SMART TV
                Menu_Smart_TV_sock(hab->tele, sock_cli);
                break;
        }
    } while (*buffer != 'S');
}
///TERCERMENU, NUMERO DE DISPOSITIVO
void Menu_Nro_Aires_sock(t_aire * aires, int cant_aires, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int i, res, bytes_escritos, opc_cli;
    do
    {
        bytes_escritos = 0;
        for(i=0;i<cant_aires;i++){      ///cargo todo el vertor aires en el "buffer" para mandar
            if(pthread_rwlock_tryrdlock(&aires[i].lock) == 0)
            {
                bytes_escritos += sprintf(menu_aux + bytes_escritos,
                                    "AIRE %d\n------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n",
                                    i + 1,
                                    aires[i].estado ? "ENCENDIDO" : "APAGADO",
                                    aires[i].modo, aires[i].temperatura);
                pthread_rwlock_unlock(&aires[i].lock);
            }
            else
                bytes_escritos += sprintf(menu_aux + bytes_escritos,"AIRE %d esta siendo modificado\n---------------\n", i + 1);
        }
        sprintf(menu_aux + bytes_escritos, "INDIQUE EL NUMERO DE AIRE O 'S' PARA SALIR:");
        if(cant_aires > 1)
            opc_cli = Validar_Nro_Dispositivo_sock(cant_aires, sock_cli, buffer, menu_aux);
        else
            opc_cli = 1;
        if(*buffer != 'S')
            menu_aire_sock(&aires[opc_cli-1], sock_cli);
    } while (*buffer != 'S');

}
void Menu_Nro_Luces_sock(t_luz *luces, int cant_luces, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int i, bytes_escritos, opc_cli;
    do
    {
        bytes_escritos = 0;
        for(i=0;i<cant_luces;i++){
            if(pthread_rwlock_tryrdlock(&luces[i].lock) == 0)
            {
                bytes_escritos += sprintf(menu_aux + bytes_escritos,
                                        "LUZ %d\n------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\n",
                                        i + 1,
                                        luces[i].estado ? "ENCENDIDO" : "APAGADO",
                                        luces[i].intensidad, luces[i].color);
                pthread_rwlock_unlock(&luces[i].lock);
            }
            else
                bytes_escritos += sprintf(menu_aux + bytes_escritos, "Luz %d esta siendo modificado\n-----------------\n", i + 1);
        }
        sprintf(menu_aux + bytes_escritos, "INDIQUE EL NUMERO DE LUZ O 'S' PARA SALIR:");
        if(cant_luces > 1)
            opc_cli = Validar_Nro_Dispositivo_sock(cant_luces, sock_cli, buffer, menu_aux);
        else
            opc_cli = 1;
        if(*buffer != 'S')
            menu_luz_sock(&luces[opc_cli-1], sock_cli);
    } while (*buffer != 'S');
}
void Menu_Smart_TV_sock(t_televisor *smart, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int bytes_escritos;
    pthread_rwlock_wrlock(&smart->lock);
    do
    {
        bytes_escritos=sprintf(menu_aux, "SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n----------------\n",
                        smart->estado ? "ENCENDIDO" : "APAGADO",
                        smart->volumen,
                        smart->fuente);
        sprintf(menu_aux + bytes_escritos, MENU_SMART_TV);
        validar_opciones_sock(OPC_MENU_SMART_TV, menu_aux, sock_cli, buffer);
        switch(*buffer)
        {
            case 'E':
                smart_encendido(smart);
                break;
            case 'F':
                smart_fuente_sock(smart, sock_cli);
                break;
            case 'V':
                smart_volumen_sock(smart, sock_cli);
                break;
        }
    } while (*buffer != 'S');
    pthread_rwlock_unlock(&smart->lock);
}
///CUARTO MENU, ATRIBUTOS DE DISPOSITIVOS
void menu_aire_sock(t_aire *aire, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int res, bytes_escritos;
    pthread_rwlock_wrlock(&aire->lock);
    /*
    if(pthread_rwlock_wrlock(&aire->lock) < 0)
    {
        do
        {
            send(sock_cli, "La tele esta siendo modificada...\nIngres 'A' para actualizar o 'S' para salir");
            recv();
        } while(pthread_rwlock_wrlock(&aire->lock) < 0);
    }
    */
    do
    {
        bytes_escritos = 0;
        bytes_escritos = sprintf(menu_aux,
                                "AIRE\n-------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n",
                                aire->estado ? "ENCENDIDO" : "APAGADO",
                                aire->modo, aire->temperatura);
        sprintf(menu_aux + bytes_escritos, MENU_AIRES);
        validar_opciones_sock(OPC_MENU_AIRES, menu_aux, sock_cli, buffer);
        
        switch (*buffer)
        {
        case 'E': /// MODIFICAR ESTADO
            res = aire_encendido(aire);
            // send(sock_cli, res?"SE ENCENDIO EL AIRE\n":"ERROR AL ENCENDER EL AIRE\n", res?21:27,0);
            /*
            if(res = aire_encendido(aire))
                puts("SE MODIFICO EL ENCENDIDO");
            else
                puts("ERROR AL MODIFICAR ENCENDIDO");
            */
            break;
        case 'M': /// MENU Y MODIFICACION DE MODO
            aire_modo_sock(aire, sock_cli);
            /*
            if(res = aire_modo(aire))
                puts("SE MODIFICO EL MODO");
            else
                puts("ERROR AL MODIFICAR MODO");
            */
            break;
        case 'T': /// MODIFICAR TEMPERATURA
            aire_temperatura_sock(aire, sock_cli);
            /*
            if(res = aire_temperatura(aire))
                puts("SE MODIFICO LA TEMPERATURA");
            else
                puts("ERROR AL MODIFICAR MODO");
            */
            break;
        }
    }while(*buffer != 'S');
    pthread_rwlock_unlock(&aire->lock);
}
void menu_luz_sock(t_luz *luz, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int  bytes_escritos;
    pthread_rwlock_wrlock(&luz->lock);
    do
    {
        bytes_escritos = 0;
        bytes_escritos = sprintf(menu_aux,
                                 "LUZ\n--------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\n",
                                 luz->estado ? "ENCENDIDO" : "APAGADO",
                                 luz->intensidad, luz->color);
        sprintf(menu_aux + bytes_escritos, MENU_LUCES);
        validar_opciones_sock(OPC_MENU_LUCES, menu_aux, sock_cli, buffer);
        switch (*buffer)
        {
        case 'E': ///ENCIENDE LA LUZ
            luz_encendido_sock(luz);
            break;
        case 'C':///CAMBIA EL COLOR
            luz_color_sock(luz, sock_cli);
            break;
        case 'I':///MODIFICA LA INTENSIDAD
            luz_intensidad_sock(luz, sock_cli);
            break;
        }
    } while (*buffer != 'S');
    pthread_rwlock_unlock(&luz->lock);
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
        bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0); ///leemos de forma bloqueante
        bytes_leidos?buffer[bytes_leidos] = '\0':sprintf(buffer, "S");  ///leimos?? si no leimos escribimos una 'S' para desconectarte

        *buffer = toupper(*buffer);
        if(strchr(opc_val, *buffer) == NULL){
            send(sock_cli, "OPCION NO VALIDA.\nPresioná una tecla para continuar o 'S' para salir...", 73, 0);
            recv(sock_cli, buffer, sizeof(buffer)-1, 0);
        }
        //printf("ACA: %s\n", buffer); ///print
    }while (strchr(opc_val, *buffer) == NULL);
    //printf("Opcion valida, paso el menu\n"); ///print
}
int Validar_Nro_Dispositivo_sock(int cant_dispositivos, int sock_cli, char *buffer, char *menu_opciones)
{
    int opc_cli, bytes_leidos;
    do
    {
        opc_cli = 0;
        send(sock_cli, menu_opciones, strlen(menu_opciones), 0);
        bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0);
        bytes_leidos? buffer[bytes_leidos] = '\0':sprintf(buffer, "S");

        if(*buffer == 's' || *buffer == 'S'){
            *buffer = 'S';
        }else{
            if(isdigit(*buffer)){
                opc_cli = atoi(buffer); //*buffer - '0'; transforma el string a entero
                if(opc_cli < 1 || opc_cli > cant_dispositivos){
                    send(sock_cli, "NUMERO NO VALIDO.\nIngrese una letra para continuar o 'S' para salir...", 71, 0);
                    recv(sock_cli, buffer, sizeof(buffer)-1, 0);
                }
            }else
                send(sock_cli, "ENTRADA NO VALIDA.\nIngrese una letra para continuar o 'S' para salir...", 72, 0);
        }
    } while (*buffer != 'S' && (opc_cli < 1 || opc_cli > cant_dispositivos));
    return opc_cli;
}
/*------------------LUZ-SOCK---------------------------*/
int luz_encendido_sock(t_luz *luz)
{
    if(luz->estado)
        return luz->estado = false;
    else
        return luz->estado = true;
}
int luz_color_sock(t_luz *luz, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int baytes_escritos, res;
    do
    {
        baytes_escritos=sprintf(menu_aux ,
                                "LUZ\n--------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\n",
                                luz->estado ? "ENCENDIDO" : "APAGADO",
                                luz->intensidad, luz->color);
        sprintf(menu_aux + baytes_escritos, MENU_COLORES_LUCES);
        validar_opciones_sock(OPC_COLORES_LUCES, menu_aux, sock_cli, buffer);
        switch (*buffer)
        {
        case 'A':
            res = strcpy(luz->color, "AMARILLO")? 1 : 0;
            break;
        case 'B':
            res = strcpy(luz->color, "AZUL")? 1 : 0;
            break;
        case 'G':
            res = strcpy(luz->color, "VERDE")? 1 : 0;
            break;
        case 'N':
            res = strcpy(luz->color, "NARANJA")? 1 : 0;
            break;
        case 'R':
            res = strcpy(luz->color, "ROJO")? 1 : 0;
            break;
        case 'V':
            res = strcpy(luz->color, "VIOLETA")? 1 : 0;
            break;
        case 'W':
            res = strcpy(luz->color, "BLANCO")? 1 : 0;
            break;
        }
    } while (*buffer != 'S');
    return res;
}
int luz_intensidad_sock(t_luz *luz, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int  bytes_escritos, res;

    bytes_escritos = sprintf(menu_aux,
                             "LUZ\n--------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\n",
                             luz->estado ? "ENCENDIDO" : "APAGADO",
                             luz->intensidad, luz->color);
    sprintf(menu_aux + bytes_escritos, "VALORES VALIDOS SON 1 < INTENSIDAD < 11\nINGRESE INTENSIDAD NUEVA O 'S' PARA SALIR: ");
    res = Validar_Nro_Dispositivo_sock(11, sock_cli, buffer, menu_aux);
    return res?luz->intensidad = res:res;
}
/*------------------AIRE-SOCK--------------------------*/
int aire_encendido_sock(t_aire *aire)
{
    if(aire->estado == true)
        return  aire->estado = false;
    else
        return  aire->estado = true;
}
int aire_modo_sock(t_aire *aire, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int baytes_escritos, res;
    ///PODEMOS AGREGAR UN BLOQUEO SI EL AIRE NO ESTA ENCENDIDO
    do
    {
        baytes_escritos=sprintf(menu_aux,
                                "AIRE\n--------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n",
                                aire->estado ? "ENCENDIDO" : "APAGADO",
                                aire->modo, aire->temperatura);
        sprintf(menu_aux + baytes_escritos, MENU_AIRES_MODO);
        validar_opciones_sock(OPC_MODO_AIRE, menu_aux, sock_cli, buffer);
        switch(*buffer)
        {
        case 'C':
            res = strcpy(aire->modo, "CALOR")? 1 : 0;
            break;
        case 'F':
            res = strcpy(aire->modo, "FRIO")? 1 : 0;
            break;
        case 'V':
            res = strcpy(aire->modo, "VENTILACION")? 1 : 0;
            break;
        }
    } while (*buffer != 'S');
    return res;
}
int aire_temperatura_sock(t_aire *aire, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int bytes_leidos, bytes_escritos, res;
    ///PODEMOS AGREGAR UN BLOQUEO SI EL AIRE NO ESTA ENCENDIDO
    do
    {
        res = aire->temperatura;
        bytes_escritos=sprintf(menu_aux,
                                "AIRE\n------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n",
                                aire->estado ? "ENCENDIDO" : "APAGADO",
                                aire->modo, aire->temperatura);
        bytes_escritos += sprintf(menu_aux + bytes_escritos, "VALORES VALIDOS SON 15 < TEMPERATURA < 33\nINGRESE TEMPERATURA NUEVA O 'S' PARA SALIR: ");
        send(sock_cli, menu_aux, bytes_escritos, 0);
        bytes_leidos = recv(sock_cli, buffer, sizeof(buffer) - 1, 0);///Leemos el buffer
        bytes_leidos?buffer[bytes_leidos] = '\0':sprintf(buffer, "S");///si no leimos escribimos un 'S'
        if(*buffer == 's' || *buffer == 'S'){
            *buffer = 'S';
        }else{
            if(isdigit(*buffer)){
                res = atoi(buffer);//*buffer - '0'; transforma el UN string a entero
                if(res < 16 || res > 32){
                    send(sock_cli, "TEMPERATURA NO VALIDAD.\nIngrese una letra para continuar...", 60, 0);
                    recv(sock_cli, buffer, sizeof(buffer)-1, 0);
                }
            }else{
                send(sock_cli, "ENTRADA NO VALIDA.\nIngrese una letra  para continuar...", 56, 0);
                recv(sock_cli, buffer, sizeof(buffer)-1, 0);
            }
        }
    } while (*buffer != 'S' && (res < 16 || res > 32));
    return aire->temperatura = res;
}
/*------------------SMART-TV-SOCK----------------------*/
int smart_encendido_sock(t_televisor *tv)
{
    if(tv->estado)
        return tv->estado = false;
    else
        return tv->estado = true;
}
int smart_fuente_sock(t_televisor * tv, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int baytes_escritos, res;
    do
    {
        baytes_escritos=sprintf(menu_aux, "SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n-----------------\n",
                                tv->estado ? "ENCENDIDO" : "APAGADO",
                                tv->volumen,
                                tv->fuente);
        sprintf(menu_aux + baytes_escritos, MENU_FUENTE_TV);
        validar_opciones_sock(OPC_FUENTE_TV, menu_aux, sock_cli, buffer);
        switch(*buffer)
        {
            case 'P':
            res = strcpy(tv->fuente,"PRIME VIDEO")?1:0;
            break;
            case 'D':
            res = strcpy(tv->fuente,"DISNEY")?1:0;
            break;
            case 'N':
            res = strcpy(tv->fuente,"NETFLIX")?1:0;
            break;
            case 'Y':
            res = strcpy(tv->fuente,"YOUTUBE")?1:0;
            break;
        }
    } while (*buffer != 'S');
    return res;
}
int smart_volumen_sock(t_televisor * tv, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int bytes_escritos, res;
    bytes_escritos=sprintf(menu_aux, "SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n-----------------\n",
                                tv->estado ? "ENCENDIDO" : "APAGADO",
                                tv->volumen,
                                tv->fuente);
    sprintf(menu_aux + bytes_escritos, "Ingrese volumen (1 - 100) o 'S' para salir: ");
    res = Validar_Nro_Dispositivo_sock(101, sock_cli, buffer, menu_aux);
    return res?tv->volumen = res:res;
}
