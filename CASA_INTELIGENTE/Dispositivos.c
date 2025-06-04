#include "Dispositivos.h"
#include "Menu.h"

/*------------------------AIRES-------------------------------------------*/
int aire_encendido(t_aire *aire)
{
    if(aire->estado == true)
        return  aire->estado = false;
    else
        return  aire->estado = true;

}
int aire_modo(t_aire *aire)
{
    int res;
    char modo;
    if(!aire->estado){
        printf("El aire está apagado. No se puede modificar el modo.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return 1;
    }
    do
    {
        //system("clear"); ///observar
        printf("AIRE\n------\n");
        printf("ESTADO: %s\n", aire->estado ? "ENCENDIDO" : "APAGADO");
        printf("MODO: %s\n", aire->modo);
        printf("TEMPERATURA: %d\n", aire->temperatura);
        puts("-----------------");
        validar_atributos(&modo, OPC_MODO_AIRE, MENU_AIRES_MODO);
        switch(modo)
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
        system("clear");
    }while(modo!='S');
    return res;
}
int aire_temperatura(t_aire *aire)
{
    int res, opc_temp;
    if(!aire->estado){
        printf("El aire está apagado. No se puede modificar la temperatura.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return 1;
    }
    do
    {
        printf("AIRE\n------\n");
        printf("ESTADO: %s\n", aire->estado ? "ENCENDIDO" : "APAGADO");
        printf("MODO: %s\n", aire->modo);
        printf("TEMPERATURA: %d\n", aire->temperatura);
        puts("-----------------");
        puts("VALORES VALIDOS SON 15 < TEMPERATURA < 33\nINGRESE TEMPERATURA NUEVA:");
        scanf("%d", &opc_temp);
        if(opc_temp < 16 || opc_temp > 32)
        {
            system("clear");
            puts("TEMPERATURA INCORRECTA. INGRESE NUEVAMENTE:\n");
            printf("Presioná Enter para continuar...");
            while (getchar() != '\n'); // LIMPIA EL BUFFER
            getchar();
        }
        else
        {
            aire->temperatura = opc_temp;
            res = 1;
        }
        system("clear");
    } while (opc_temp < 16 || opc_temp > 32);

    return res;
}
/*------------------------LUZ---------------------------------------------*/
int luz_encendido(t_luz *luz)
{
    if(luz->estado)
        return luz->estado = false;
    else
        return luz->estado = true;
}
int luz_color(t_luz *luz)
{
    int res;
    char color;
    if(!luz->estado){
        printf("La luz está apagada. No se puede modificar el color.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return 1;
    }
    do
    {
        //system("clear"); ///observar
        printf("LUZ\n------\n");
        printf("ESTADO: %s\n", luz->estado ? "ENCENDIDO" : "APAGADO");
        printf("COLOR: %s\n", luz->color);
        printf("INTENCIDAD: %d\n", luz->intensidad);
        printf("-----------------\n");
        validar_atributos(&color, OPC_COLORES_LUCES, MENU_COLORES_LUCES);
        system("clear");
        switch (color)
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
    } while (color != 'S');
    return res;
}
int luz_intensidad(t_luz *luz)
{
    int res, opc_temp;
    if(!luz->estado){
        printf("La luz está apagada. No se puede modificar la intensidad.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return 1;
    }
    do
    {
        printf("LUZ\n------\n");
        printf("ESTADO: %s\n", luz->estado ? "ENCENDIDO" : "APAGADO");
        printf("INTENSIDAD: %d\n", luz->intensidad);
        printf("COLOR: %s\n", luz->color);
        printf("-----------------\n");
        puts("VALORES VALIDOS SON 1 < INTENSIDAD < 10\nINGRESE INTENSIDAD NUEVA:");
        scanf("%d", &opc_temp);
        if(opc_temp < 1 || opc_temp > 10)
        {
            system("clear");
            puts("VALOR INCORRECTO. INGRESE NUEVAMENTE:\n");
            printf("Presioná Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }
        else
        {
            luz->intensidad = opc_temp;
            res = 1;
        }
        system("clear");
    } while (opc_temp < 1 || opc_temp > 10);

    return res;
}
/*------------------------SMAR-TV-----------------------------------------*/
void smart_encendido(t_televisor *tv)
{
    tv->estado = !tv->estado;
}
int smart_fuente(t_televisor * tv)
{
    char opc;
    int res=1;
    if(!tv->estado){
        printf("El televisor está apagado. No se puede modificar la fuente.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return res;
    }
    printf("%s",MENU_FUENTE_TV);
    do
    {
        while(getchar() != '\n');
        scanf("%c",&opc);
        if(isalpha(opc))
            opc = toupper(opc);
        if(!strchr(OPC_FUENTE_TV,opc))
        {
            printf("Opcion no valida. Ingrese nuevamente (%s):",OPC_FUENTE_TV);
        }
    } while (!strchr(OPC_FUENTE_TV,opc));
    system("clear");\
    switch(opc)
    {
        case 'P':
            strcpy(tv->fuente,"PRIME VIDEO");
            break;
        case 'D':
            strcpy(tv->fuente,"DISNEY");
            break;
        case 'N':
            strcpy(tv->fuente,"NETFLIX");
            break;
        case 'Y':
            strcpy(tv->fuente,"YOUTUBE");
            break;
    }
    return res;
}
int smart_volumen(t_televisor * tv)
{
    int volumen;
    printf("Ingrese volumen (0 - 100):");
    do
    {
        while(getchar() != '\n');
        scanf("%d",&volumen);
        if(volumen < 0 || volumen > 100)
            printf("Volumen fuera de rango. Ingrese un valor del 0 al 100:");
    } while (volumen < 0 || volumen > 100);
    tv->volumen = volumen;
    return tv->volumen;
}
void modificar_volumen_smart(t_televisor * t)
{
    char opcion;

    if(!t->estado){
        printf("El televisor está apagado. No se puede modificar el volumen.\n");
        printf("Presioná Enter para continuar...");
        while (getchar() != '\n');
        getchar();
        return;
    }
    do 
    {
        printf("Ingrese A para aumentar, B para bajar volumen, S para salir: ");
        do{
            do{
                opcion = getchar();
            }while(opcion == '\n');
            if (isalpha(opcion))
                opcion = toupper(opcion);
            if(opcion != 'A' && opcion != 'B' && opcion != 'S') {
                printf("Opción inválida. Ingrese A (aumentar), B (bajar) o S (salir): ");
            }
        }while(opcion != 'A' && opcion != 'B' && opcion != 'S');

        if(opcion == 'A'){
            if (t->volumen <= 95)
                t->volumen += 5;
            else
                t->volumen = 100;
        }else if(opcion == 'B'){
            if (t->volumen >= 5)
                t->volumen -= 5;
            else
                t->volumen = 0;
        }

        if (opcion != 'S') {
            printf("Volumen actual: %d\n", t->volumen);
        }

    } while (opcion != 'S');
}
////////////////////////////////////////////////////////////////////////////
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
        if(validar_opciones_sock(OPC_COLORES_LUCES, menu_aux, sock_cli, buffer)<0)
        {
            pthread_rwlock_unlock(&luz->lock);
            pthread_exit(NULL);
        }
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
    sprintf(menu_aux + bytes_escritos, "VALORES VALIDOS SON 1 < INTENSIDAD < 11\nINGRESE INTENSIDAD NUEVA O 'S' PARA SALIR...\n--->");
    if((res = Validar_Nro_Dispositivo_sock(11, sock_cli, buffer, menu_aux))<0)
    {
        pthread_rwlock_unlock(&luz->lock);
        pthread_exit(NULL);
    }
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
        if(validar_opciones_sock(OPC_MODO_AIRE, menu_aux, sock_cli, buffer)<0)
        {
            pthread_rwlock_unlock(&aire->lock);
            pthread_exit(NULL);
        }
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
    int  res;
    ///PODEMOS AGREGAR UN BLOQUEO SI EL AIRE NO ESTA ENCENDIDO
    do
    {
        res = aire->temperatura;
        sprintf(menu_aux,
                                "AIRE\n------\nESTADO: %s\nMODO: %s\nTEMPERATURA: %d\n-----------------\n"
                                "VALORES VALIDOS SON 15 < TEM < 33\nINGRESE TEMPERATURA NUEVA O 'S' PARA SALIR...\n-->",
                                aire->estado ? "ENCENDIDO" : "APAGADO",
                                aire->modo, aire->temperatura);
        if(enviar_mensaje(sock_cli, menu_aux)<0 || recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
            return ERR_COM;
        
        if(*buffer == 's' || *buffer == 'S'){
            *buffer = 'S';
        }else{
            if(isdigit(*buffer)){
                res = atoi(buffer);//*buffer - '0'; transforma el UN string a entero
                if(res < 16 || res > 32){
                    if(enviar_mensaje(sock_cli, "TEMPERATURA NO VALIDAD.\nIngrese una letra para continuar o 'S' para salir...\n-->")<0 ||
                        recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
                        return ERR_COM;
                }
            }else{
                if(enviar_mensaje(sock_cli, "ENTRADA NO VALIDAD.\nIngrese una letra para continuar o 'S' para salir...\n-->")<0 ||
                    recibir_mensaje(sock_cli, buffer, sizeof(buffer)-1)<0)
                    return ERR_COM;
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
        if(validar_opciones_sock(OPC_FUENTE_TV, menu_aux, sock_cli, buffer)<0){
            pthread_rwlock_unlock(&tv->lock);
            pthread_exit(NULL);
        }
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
    if((res = Validar_Nro_Dispositivo_sock(101, sock_cli, buffer, menu_aux))<0){
        pthread_rwlock_unlock(&tv->lock);
        pthread_exit(NULL);
    }
    return res?tv->volumen = res:res;
}
