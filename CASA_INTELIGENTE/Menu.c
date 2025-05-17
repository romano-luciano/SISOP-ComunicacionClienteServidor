#include "Menu.h"

void seleccion_habitaciones(t_habitacion * hab){
    char opc;
    ///MOSTAR HABITACIONES DISPONIBLES EN LA CASA
    do{
        while(getchar() != '\n');  // LIMPIA EL BUFFER
        printf("%s", MENU_HABITACIONES);
        scanf("%c", &opc);

        opc = toupper(opc);
        if(strchr(OPC_MENU_HAB, opc) == NULL ){
            system("clear");
            printf("%s", MENU_HABITACIONES);
            printf("HABITACION INCORRECTA. INGRESE NUEVAMENTE: \n");
            printf("Presiona Enter para continuar...");
            getchar();
        }
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
            system("PAUSE");

        }
        system("clear");
        switch(opc_cli)
        {
            case 'A':///AIRES
                Menu_Aires(hab->aires,hab->cant_aires);
                break;
            case 'L':///LUCES
                break;
            case 'T':///SMART TV
                break;
        }
        system("clear");;
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
    char atributo, aux;
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
        while(getchar() != '\n');  // LIMPIA EL BUFFER
        //printf("SELECCIONE UN AIRE POR SU NUMERO: 1 - %d:", cant_aires);
        puts("SELECCIONE UN AIRE POR SU NUMERO (S para salir):");
        scanf("%c", &aux); /// ELIJE NUMERO DE AIRE
        if(aux == 'S' || aux == 's')
        {
            atributo = toupper(aux);
        }
        else
        {
            opc = atoi(&aux);
            if (opc <= 0 || opc > cant_aires) ///RANGO NUMERICO INVALIDO cant_aires > 1 &&
            {
                atributo = 'Z';
                system("clear");
                printf("NUMERO DE AIRE NO VALIDO\n.");
                system("pause");
            }
            else
            {
                while(getchar() != '\n');
                printf(MENU_AIRES, cant_aires); ///MENU DE ATRIBUTOS A MODIFICAR DE AIRE
                scanf("%c",&atributo);
                atributo = toupper(atributo);
                if(strchr(OPC_MENU_AIRES,atributo) == NULL)
                {
                    system("clear");
                    //printf("%s", MENU_AIRES);
                    printf("ATRIBUTO DE AIRE INCORRECTO. INGRESE NUEVAMENTE:\n");
                    system("pause");
                }
            }
        }

        system("clear");
        switch(atributo)
        {
            case 'E':///MODIFICAR ESTADO
                res = aire_encendido(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO EL ENCENDIDO\n");
                else
                    puts("ERROR AL MODIFICAR ENCENDIDO\n");
                break;
            case 'M':///MENU Y MODIFICACION DE MODO
                res = aire_modo(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO EL MODO\n");
                else
                    puts("ERROR AL MODIFICAR MODO\n");
                break;
            case 'T':///MODIFICAR TEMPERATURA
                res = aire_temperatura(&aires[opc - 1]);
                if(res)
                    puts("SE MODIFICO LA TEMPERATURA\n");
                else
                    puts("ERROR AL MODIFICAR MODO\n");
                break;
        }
        system("clear");
    }while(atributo != 'S');
}
