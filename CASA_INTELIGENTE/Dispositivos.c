#include "Dispositivos.h"
#include "Menu.h"

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
    do
    {
        system("CLEAR"); ///observar
        puts("AIRE\n------\n");
        printf("ESTADO: %s\n", aire->estado ? "ENCENDIDO" : "APAGADO");
        printf("MODO: %s\n", aire->modo);
        printf("TEMPERATURA: %d\n", aire->temperatura);
        puts("-----------------");
        while(getchar() != '\n');  // LIMPIA EL BUFFER
        puts(MENU_AIRES_MODO);
        scanf("%c", &modo);
        modo = toupper(modo);
        if(strchr(OPC_MODO_AIRE, modo)==NULL)
        {
            system("clear");
            puts("MODO INCORRECTO. INGRESE NUEVAMENTE:\n");
            system("PAUSE");
        }
        system("clear");
        switch(modo)
        {
        case 'C':
            res = memcpy(aire->modo, "CALOR", 6)? 1 : 0;
            //modo = 'S';
            break;
        case 'F':
            res = memcpy(aire->modo, "FRIO", 5)? 1 : 0;
            //modo = 'S';
            break;
        case 'V':
            res = memcpy(aire->modo, "VENTILACION", 12)? 1 : 0;
            //modo = 'S';
            break;
        }
        system("clear");
    }while(modo!='S');
    return res;
}
int aire_temperatura(t_aire *aire)
{
    int res, opc_temp;
    do
    {
        puts("VALORES VALIDOS SON 15<TEMPERATURA<33\nINGRESE TEMPERATURA NUEVA:");
        scanf("%d", &opc_temp);
        if(opc_temp < 16 || opc_temp > 32)
        {
            system("clear");
            puts("TEMPERATURA INCORRECTA. INGRESE NUEVAMENTE:\n");
            system("PAUSE");
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
