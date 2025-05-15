#include "Menu.h"

void seleccion_habitaciones(t_habitacion *hab){
    char opc;
    ///MOSTAR HABITACIONES DISPONIBLES EN LA CASA
    do{
        fflush(stdin);
        printf("%s", MENU_HABITACIONES);
        scanf("%c", &opc);

        opc = toupper(opc);
        if(strchr(OPC_MENU_HAB, opc)==NULL ){ //&& val_opc(opc)
            system("CLS");
            printf("%s", MENU_HABITACIONES);
            printf(" HABITACION INCORRECTA. VUELVA A INGRESAR NUEVAMENTE.\n");
            system("pause");
            system("CLS");
        }
        system("CLS");
        switch(opc){
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
void seleccion_dispositivos(t_habitacion *hab){
    char opc_cli;
    char *opc_disp;
    vector_opc_disp(hab, opc_disp);
    do{
        fflush(stdin);
        printf(MENU_DISPOSITIVOS_2, hab->nombre_habitacion,
                                    hab->cant_aires?"A - Aires\n":" ",
                                    hab->cant_luces?"L - Luces\n":" ",
                                    hab->hay_tele?"T - Smart TV\n":" ");
        scanf("%c", &opc_cli);
        switch(opc_cli){
        case 'A':///AIRES
            break;
        case 'L':///LUCES
            break;
        case 'T':///SMART TV
            break;
        }
        system("CLS");
    }while(opc_cli!='S');
}
void vector_opc_disp(const t_habitacion *hab, char *opc_res){
    //char letra;
    //opc_res = hab->cant_aires?"A":
}
