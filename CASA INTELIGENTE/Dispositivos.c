#include "Dispositivos.h"
#include "Menu.h"

int aire_encendido(t_aire *aire)
{
    return aire->estado?false:true;
}
int aire_modo(t_aire *aire)
{
    int res;
    char modo;
    do
    {
        while(getchar() != '\n');  // LIMPIA EL BUFFER
        puts(MENU_AIRES_MODO);
        scanf("%c", &modo);
        modo = toupper(modo);
        if(strchr(OPC_MODO_AIRE, modo)==NULL)
        {
            system("CLS");
            puts("MODO INCORRECTO. INGRESE NUEVAMENTE:\n");
            system("PAUSE");
        }
        system("CLS");
        switch(modo)
        {
        case 'C':
            res = memcpy(aire->modo, "CALOR", TAM_MODO-1);
            break;
        case 'F':
            res = memcpy(aire->modo, "FRIO", TAM_MODO-1);
            break;
        case 'V':
            res = memcpy(aire->modo, "VENTILACION", TAM_MODO-1);
            break;
        }
    }while(modo!='S');
    return res;
}
