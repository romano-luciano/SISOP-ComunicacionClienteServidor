#include "Menu.h"

void seleccion_habitaciones(t_habitacion * hab){
    char opc;
    ///MOSTAR HABITACIONES DISPONIBLES EN LA CASA
    do{
        validar_atributos(&opc, OPC_MENU_HAB, MENU_HABITACIONES);
        system("clear");
        switch(opc)
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
        system("clear");
        ///GUARDAR Y ESCRIBIR EL ARCHIVO
    }while(opc!='S');
}
void seleccion_dispositivos(t_habitacion * hab)
{
    char opc_cli;
    char opc_disp[CANT_HABITACIONES-1];
    vector_opc_disp(hab, opc_disp);
    do{
        while(getchar() != '\n');  // limpia buffer
        printf(MENU_DISPOSITIVOS_2, hab->nombre_habitacion,
                                    hab->cant_aires ? "A - Aires\n":" ",
                                    hab->cant_luces ? "L - Luces\n":" ",
                                    hab->hay_tele ? "T - Smart TV\n":" ");                                  
        scanf("%c", &opc_cli);
        opc_cli = toupper(opc_cli);
        if(strchr(opc_disp, opc_cli) == NULL)
        {
            puts("DISPOSITIVO NO VALIDO. INGRESE NUEVAMENTE:");
            //printf("DISPOSITIVO NO VALIDO. OPCIONES DISPONIBLES: %s. \nINGRESE NUEVAMENTE:",opc_disp);
            printf("Presioná Enter para continuar...");
            while (getchar() != '\n'); //limpia el buffer
            getchar();
        }
        system("clear");
        switch(opc_cli)
        {
            case 'A':///AIRES
                Menu_Aires(hab->aires,hab->cant_aires);
                break;
            case 'L':///LUCES
                Menu_Luces(hab->luces, hab->cant_luces);
                break;
            case 'T':///SMART TV
                Menu_SmartTV(hab->tele);
                break;
        }
        system("clear");
    }while(opc_cli!='S');
}
void vector_opc_disp(const t_habitacion * hab, char * opc_res)
{
   char * p = opc_res;
   if(hab->cant_aires > 0)
   {
        *p = 'A';
        p ++;
   }
   if(hab->cant_luces > 0)
   {
        *p = 'L';
        p ++;
   }
   if(hab->hay_tele)
   {
        *p = 'T';
        p ++;
   }
   *p = 'S';
   p++;
   *p = '\0';
   //puts(opc_res);
}
void Menu_Aires(t_aire * aires, int cant_aires)
{
    int i, res, opc;
    char atributo;
    do{
        printf("AIRES DISPONIBLES\n-----------------\n");
        for(i = 0; i < cant_aires; i++)
        {
            printf("AIRE %d\n------\n", i + 1);
            printf("ESTADO: %s\n",aires[i].estado ? "ENCENDIDO" : "APAGADO");
            printf("MODO: %s\n",aires[i].modo);
            printf("TEMPERATURA: %d\n",aires[i].temperatura);
            puts("-----------------");
        }
        if(cant_aires > 1){
            opc = Validar_Nro_Dispositivo(&atributo, cant_aires, AIRES);
            system("clear");
        }
        else
            opc = 1;

        if(atributo != 'S' || cant_aires == 1)
        {
            validar_atributos(&atributo, OPC_MENU_AIRES, MENU_AIRES);
        }
        system("clear");
        switch(atributo)
        {
            case 'E':///MODIFICAR ESTADO
                res = aire_encendido(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO EL ENCENDIDO");
                else
                    puts("ERROR AL MODIFICAR ENCENDIDO");
                break;
            case 'M':///MENU Y MODIFICACION DE MODO
                res = aire_modo(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO EL MODO");
                else
                    puts("ERROR AL MODIFICAR MODO");
                break;
            case 'T':///MODIFICAR TEMPERATURA
                res = aire_temperatura(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO LA TEMPERATURA");
                else
                    puts("ERROR AL MODIFICAR MODO");
                break;
        }
        system("clear");
    }while(atributo != 'S');
}
void Menu_Luces(t_luz * luces, int cant_luces)
{

    int i, res, opc;
    char atributo;

    do
    {
        printf("LUCES DISPONIBLES\n-----------------\n");
        for(i = 0; i < cant_luces; i++)
        {
            printf("LUZ %d\n------\n", i + 1);
            printf("ESTADO: %s\n",luces[i].estado ? "ENCENDIDO" : "APAGADO");
            printf("INTENSIDAD: %d\n",luces[i].intensidad);
            printf("COLOR: %s\n",luces[i].color);
            printf("-----------------\n");
        }

        opc = Validar_Nro_Dispositivo(&atributo, cant_luces, LUCES);
        system("clear");

        if(atributo != 'S')
        {
            validar_atributos(&atributo, OPC_MENU_LUCES, MENU_LUCES);
        }
        system("clear");
        switch (atributo)
        {
        case 'C':///modificar color
            res = luz_color(&luces[opc - 1]);
            if (res)
                puts("SE MODIFICO EL COLOR");
            else
                puts("ERROR AL MODIFICAR COLOR");
            break;
        case 'E':///modicicar encendido
            res = luz_encendido(&luces[opc - 1]);
            if (res)
                puts("SE MODIFICO EL ENCENDIDO");
            else
                puts("ERROR AL MODIFICAR ENCENDIDO");
            break;
        case 'I':///modificar intencidad
            res = luz_intensidad(&luces[opc - 1]);
            if (res)
                puts("SE MODIFICO LA INTENSIDAD");
            else
                puts("ERROR AL MODIFICAR LA INTENSIDAD");
            break;
        }
        system("clear");
    } while (atributo != 'S');

}
void validar_atributos(char *opc_cli, const char *opc_val, const char *menu_atributo)
{
    printf("%s", menu_atributo);
    do
    {
        do{
            *opc_cli = getchar();
        }while (*opc_cli == '\n');
        *opc_cli = toupper(*opc_cli);
        if(strchr(opc_val, *opc_cli) == NULL)
        {
            printf("OPCION INVALIDA. INGRESE NUEVAMENTE (%s):", opc_val);
            while (getchar() != '\n'); // Limpiar el buffer
        }
    }while (strchr(opc_val, *opc_cli) == NULL);
}
int Validar_Nro_Dispositivo(char * aux, int cant_dispositivos, int tipo_disp)
{
    int opc_int;
    printf("SELECCIONE");
    switch(tipo_disp)
    {
        case 0:
            printf(" UNA LUZ A MODIFICAR (S PARA SALIR):");
            break;
        case 1:
            printf(" UN AIRE A MODIFICAR (S PARA SALIR):");
            break;
    }

    do {
        do{
            *aux = getchar();
        }while (*aux == '\n');

        if (*aux == 's' || *aux == 'S') {
            *aux = 'S';
        } else if (isdigit(*aux)) {
            opc_int = *aux - '0';
            if (opc_int < 1 || opc_int > cant_dispositivos) {
                printf("Opción no válida. Ingrese del 1 al %d o S para salir.\n", cant_dispositivos);
            }
        } else {
            printf("Entrada no válida. Ingrese un número o S para salir.\n");
        }
    } while (*aux != 'S' && (opc_int < 1 || opc_int > cant_dispositivos));
    return opc_int;
}
void Menu_SmartTV(t_televisor * smart)
{
    char opc;
    do {
        printf("SMART TV\n--------\nESTADO: %s\nVOLUMEN: %d\nFUENTE: %s\n",smart->estado ? "ENCENDIDO" : "APAGADO",smart->volumen,smart->fuente);
        validar_atributos(&opc, OPC_MENU_SMART_TV, MENU_SMART_TV);
        system("clear");
        switch(opc)
        {
            case 'E':
                smart_encendido(smart);
                break;
            case 'F':
                smart_fuente(smart);
                break;
            case 'V':
                modificar_volumen_smart(smart);
                break;
        }
        system("clear");
    } while(opc != 'S');

}
