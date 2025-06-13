#include "Menu.h"

int clientes_activos = 0;
int actividad = 0;
pthread_mutex_t mutex_clientes = PTHREAD_MUTEX_INITIALIZER;

///PRIMER MENU, HABITACIONES
void seleccion_habitaciones_sock(t_habitacion *hab, int sock_cli)
{
    char buffer[TAM_BUFFER];
    do
    {
        if(validar_opciones_sock(OPC_MENU_HAB, MENU_HABITACIONES, sock_cli, buffer)<0)
            pthread_exit(NULL);
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
    } while (*buffer != 'S');
}
///SEGUNDO MENU, DISPOSITIVOS
void seleccion_dispositivos_sock(t_habitacion *hab, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER], opc_disp[CANT_HABITACIONES-1];
    vector_opc_disp_sock(hab, opc_disp);
    do
    {
        sprintf(menu_aux, MENU_DISPOSITIVOS_2, hab->nombre_habitacion,
                                                                hab->cant_aires ? "A - Aires\n":" ",
                                                                hab->cant_luces ? "L - Luces\n":" ",
                                                                hab->hay_tele ? "T - Smart TV\n":" ");
        if(validar_opciones_sock(opc_disp, menu_aux, sock_cli, buffer)<0)
            pthread_exit(NULL);
        switch(*buffer)
        {
            case 'A':///AIRES
                hab->cant_aires>1?Menu_Nro_Aires_sock(hab->aires,hab->cant_aires, sock_cli):menu_aire_sock(hab->aires, sock_cli);
                break;
            case 'L':///LUCES
                hab->cant_luces>1?Menu_Nro_Luces_sock(hab->luces, hab->cant_luces, sock_cli):menu_luz_sock(hab->luces, sock_cli);
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
        if((opc_cli = Validar_Nro_Dispositivo_sock(cant_aires, sock_cli, buffer, menu_aux))<0)
            pthread_exit(NULL);
        if(*buffer != 'S' && *buffer != 's')
            menu_aire_sock(&aires[opc_cli-1], sock_cli);
    } while (*buffer != 'S' && *buffer != 's');

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
        if((opc_cli = Validar_Nro_Dispositivo_sock(cant_luces, sock_cli, buffer, menu_aux))<0)
            pthread_exit(NULL);
        if(*buffer != 'S' && *buffer != 's')
            menu_luz_sock(&luces[opc_cli-1], sock_cli);
    } while (*buffer != 'S' && *buffer != 's');
}
void Menu_Smart_TV_sock(t_televisor *smart, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int bytes_escritos;
    if(pedir_dispositivo_sock(&smart->lock, sock_cli, SMART_TV) == 0) //pido candado
        return;
    do
    {
        bytes_escritos=sprintf(menu_aux, "SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n----------------\n",
                        smart->estado ? "ENCENDIDO" : "APAGADO",
                        smart->volumen,
                        smart->fuente);
        sprintf(menu_aux + bytes_escritos, MENU_SMART_TV);
        if(validar_opciones_sock(OPC_MENU_SMART_TV, menu_aux, sock_cli, buffer)<0){ //si se desconecto el cliemte, libero candado
            pthread_rwlock_unlock(&smart->lock);
            pthread_exit(NULL);
        }
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
    int bytes_leidos, bytes_escritos;
    
    if(pedir_dispositivo_sock(&aire->lock, sock_cli, AIRES) == 0)   //pido candado, si devuelve 0 no me lo dio
        return;
    do
    {
        bytes_escritos = 0;
        bytes_escritos = sprintf(menu_aux,
                                "AIRE\n-------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n",
                                aire->estado ? "ENCENDIDO" : "APAGADO",
                                aire->modo, aire->temperatura);
        sprintf(menu_aux + bytes_escritos, MENU_AIRES);
        if(validar_opciones_sock(OPC_MENU_AIRES, menu_aux, sock_cli, buffer)<0){
            pthread_rwlock_unlock(&aire->lock);             //libero candado, si se desconecto el cliente
            pthread_exit(NULL);
        }
        
        switch (*buffer)
        {
        case 'E': /// MODIFICAR ESTADO
            aire_encendido(aire);
            break;
        case 'M': /// MENU Y MODIFICACION DE MODO
            aire_modo_sock(aire, sock_cli);
            break;
        case 'T': /// MODIFICAR TEMPERATURA
            if(aire_temperatura_sock(aire, sock_cli)<0)
            {
                pthread_rwlock_unlock(&aire->lock);
                pthread_exit(NULL);
            }
            break;
        }
    }while(*buffer != 'S');
    pthread_rwlock_unlock(&aire->lock);
}
void menu_luz_sock(t_luz *luz, int sock_cli)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int  bytes_escritos;
    
    if(pedir_dispositivo_sock(&luz->lock, sock_cli, LUCES) == 0)// si devuelve 1, tiene el candado
        return;
    do
    {
        bytes_escritos = 0;
        bytes_escritos = sprintf(menu_aux,
                                 "LUZ\n--------\nESTADO: %s\nINTENSIDAD: %d\nCOLOR: %s\n-----------------\n",
                                 luz->estado ? "ENCENDIDO" : "APAGADO",
                                 luz->intensidad, luz->color);
        sprintf(menu_aux + bytes_escritos, MENU_LUCES);
        if(validar_opciones_sock(OPC_MENU_LUCES, menu_aux, sock_cli, buffer)<0){
            pthread_rwlock_unlock(&luz->lock);
            pthread_exit(NULL);
        }
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
int enviar_mensaje(int sock, const char *msg) {
    int enviado = send(sock, msg, strlen(msg), 0);
    if (enviado <= 0) {
        perror("Error en send");
        close(sock);
        printf("Cliente %d desconectado...\n", sock);
        pthread_mutex_lock(&mutex_clientes);
        clientes_activos--;
        printf("Clientes activos: %d\n", clientes_activos);
        pthread_mutex_unlock(&mutex_clientes);
        return -1; // cliente desconectado o error
    }
    return enviado;
}
int recibir_mensaje(int sock, char *buffer, int tam) {
    int leido = recv(sock, buffer, tam - 1, 0);
    if (leido <= 0) {
        perror("Error en recv");
        close(sock);
        printf("Cliente %d desconectado...\n", sock);
        pthread_mutex_lock(&mutex_clientes);
        clientes_activos--;
        printf("Clientes activos :) %d\n", clientes_activos);
        pthread_mutex_unlock(&mutex_clientes);
        return -1; // cliente desconectado o error
    }
    buffer[leido] = '\0';
    return leido;
}
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
int validar_opciones_sock(const char *opc_val, const char *menu_atributo, int sock_cli, char *buffer)
{
    do
    {
        if(enviar_mensaje(sock_cli, menu_atributo)<0 || recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
            return ERR_COM;
        *buffer = toupper(*buffer);
        if(strchr(opc_val, *buffer) == NULL){
            if(enviar_mensaje(sock_cli, "OPCION NO VALIDA.\nPresioná una tecla para continuar o 'S' para salir...")<0)
                return ERR_COM;
            if(recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
                return ERR_COM;
        }
    }while (strchr(opc_val, *buffer) == NULL);
    return TODO_OK;
}
int  Validar_Nro_Dispositivo_sock(int cant_dispositivos, int sock_cli, char *buffer, char *menu_opciones)
{
    int opc_cli;
    do
    {
        opc_cli = 0;
        if(enviar_mensaje(sock_cli, menu_opciones)<0 || recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
            return ERR_COM;

        if(*buffer == 's' || *buffer == 'S'){
            *buffer = 'S';
        }else{
            if(isdigit(*buffer)){
                opc_cli = atoi(buffer); //transforma el string a entero
                if(opc_cli < 1 || opc_cli > cant_dispositivos){
                    if(enviar_mensaje(sock_cli, "NUMERO NO VALIDO.\nIngrese una letra para continuar o 'S' para salir...\n--->")<0 || 
                        recibir_mensaje(sock_cli, buffer, sizeof(buffer))<0)
                        return ERR_COM;
                }
            }else{
                if(enviar_mensaje(sock_cli, "ENTRADA NO VALIDA.\nIngrese una letra para continuar o 'S' para salir...\n--->")<0 ||
                    recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
                    return ERR_COM;
            }
        }
    } while ((*buffer != 'S' && *buffer != 's') && (opc_cli < 1 || opc_cli > cant_dispositivos));
    return opc_cli;
}
int  pedir_dispositivo_sock(pthread_rwlock_t *lock, int sock_cli, int disp)
{
    char buffer[TAM_BUFFER], menu_aux[TAM_BUFFER];
    int bytes_leidos;
    if(pthread_rwlock_trywrlock(lock) != 0)
    {
        do//entro al while si no me dio el candado
        {
            sprintf(menu_aux, "%s esta siendo modificada...\nIngrese 'A' para actualizar o 'S' para salir\n-->",
                    disp == LUCES?"La luz":disp == AIRES?"El aire":"La tele");
            if(enviar_mensaje(sock_cli, menu_aux)<0 || recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
                return ERR_COM;
        } while((*buffer != 'S' && *buffer != 's') && (pthread_rwlock_trywrlock(lock) != 0));
        if(*buffer == 'S' || *buffer == 's')
            return 0;
    }
    return TODO_OK; //optengo el candado
}
