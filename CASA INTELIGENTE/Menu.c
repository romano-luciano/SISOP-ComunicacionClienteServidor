#include "Menu.h"

void seleccion_habitaciones(t_habitacion * hab){
    char opc;
    ///MOSTAR HABITACIONES DISPONIBLES EN LA CASA
    do{
        while(getchar() != '\n');  // limpia buffer
        printf("%s", MENU_HABITACIONES);
        scanf("%c", &opc);

        opc = toupper(opc);
        if(strchr(OPC_MENU_HAB, opc) == NULL ){
            system("CLS");
            printf("%s", MENU_HABITACIONES);
            printf("HABITACION INCORRECTA. INGRESE NUEVAMENTE: \n");
            system("PAUSE");
            system("CLS");
        }
        system("CLS");
        switch(opc)
        {
            case 'A':///DORMITORIO 1
                break;
            case 'B':///BAÑO
                break;
            case 'C':///COCINA
                break;
            case 'D':///DORMITORIO 2
                break;
            case 'L':///LIVING
                break;
            case 'P':///PATIO
                break;
        }
        system("CLS");
    }while(opc!='S');
}
//int val_opc(char opc){
//    char *aux = opc++;
//    return aux?0:1; ///VALIDO SI ES UNA LETRA SOLA
//}
///SEGUNDO MENU, DISPOSITIVOS

void seleccion_dispositivos(t_habitacion * hab)
{
    char opc_cli;
    char opc_disp[5];
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
            printf("DISPOSITIVO NO VALIDO. OPCIONES DISPONIBLES: %s. \nINGRESE NUEVAMENTE:",opc_disp);
            system("PAUSE");
            system("CLS");
        }
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
        system("CLS");
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
   puts(opc_res);
}
void Menu_Aires(t_aire * aires, int cant_aires)
{
    int i;
    int opc;
    char atributo;
    printf("Aires disponibles\n----------------\n");
    for(i = 0; i < cant_aires; i++)
    {
        printf("Aire %d\n------\n", i + 1);
        printf("Estado: %s\n",aires[i].estado ? "Prendido" : "Apagado");
        printf("Modo: %s\n",aires[i].modo);
        printf("Temperatura: %d\n",aires[i].temperatura);
    }
    do{
        while(getchar() != '\n');  // limpia buffer
        printf("Seleccione un aire por su numero: 1 - %d:", cant_aires);
        scanf("%d",&opc);
        if(opc <= 0 || opc > cant_aires)
            printf("\nAire no valido.");
    }while(opc <= 0 || opc > cant_aires);

    do
    {
        printf("\n%s",MENU_AIRES); ///Menu de atributos a modificar
        do ///Validacion de opcion.
        {
            while(getchar() != '\n');  // limpia buffer
            scanf("%c",&atributo);
            if(!strchr(OPC_MENU_AIRES,atributo))
                printf("Opcion no valida. Ingrese (%s):",OPC_MENU_AIRES);
        } while (!strchr(OPC_MENU_AIRES,atributo));

        switch(atributo)
        {
            case 'E':
               //// &aires[opc - 1];
                break;
            case 'M':
                break;
            case 'T':
                break;
        }
    }   while(atributo != 'S');
}
