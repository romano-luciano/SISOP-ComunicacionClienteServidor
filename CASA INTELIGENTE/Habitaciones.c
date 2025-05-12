#include "Habitaciones.h"

void inicializar_habitaciones(t_habitacion * habitaciones, const char *archivo)
{
    FILE *pf = fopen("Archivos/Habitaciones.txt", "rt");
    char buffer[TAM_BUFFER];
    char * pipe, * punt = buffer;
    int i = 0, nDisp, cant_disp;
    if(!pf)
        printf("Error al abrir el archivo: %s\n", archivo);
    while(fgets(buffer,TAM_BUFFER,pf) && (*buffer!='\n'))
    {
        printf("\n");
        ///BUSCAMOS PIPE Y LEEMOS NOMBRE
        pipe = strchr(buffer,'|');
        if(pipe)
            *pipe = '\0';
        strcpy(habitaciones[i].nombre_habitacion,buffer);
        printf("%s|",habitaciones[i].nombre_habitacion);///PRINT
        for(nDisp = 0;nDisp < 3;nDisp++){
            ///BUSCAMOS PIPE Y LEEMOS CANTIDAD
            punt = pipe + 1;
            pipe = strchr(punt,'|');
            if(pipe)
                *pipe = '\0';
            else
            {
                pipe = strchr(punt,'\n'); ///cmabiar a '\r' en linux
                *pipe = '\0';
            }
            cant_disp = atoi(punt);
            ///SI HAY CANTIDAD, BUSCAMOS PIPE Y LEEMOS DISPOSITIVOS
            if(cant_disp > 0){
                punt = pipe + 1;
                pipe = strchr(punt,'|');
                if(pipe)
                    *pipe = '\0';
            }
            ///EN 'CARGAR' PREGUNTAMOS SI EL NUMERO DE 'DISPO' ES MAYOR A 0
            cargar_dispositivos(&habitaciones[i], cant_disp, punt, nDisp);
        }
/*
        ///BUSCAMOS PIPE Y LEEMOS CANTIDAD DE LUCES
        punt = pipe + 1;
        pipe = strchr(punt,'|');
        if(pipe)
            *pipe = '\0';
        else{
            pipe = strchr(punt,'\n');
            *pipe = '\0';
        }
        habitaciones[i].cant_luces = atoi(punt);
        printf("cant: %d|",habitaciones[i].cant_luces);///PRINT
        ///BUSCAMOS PIPE Y LEEMOS LUCES, SI HAY LUCES
        if(habitaciones[i].cant_luces > 0){
            punt = pipe + 1;
            pipe = strchr(punt,'|');
            if(pipe)
                *pipe = '\0';
            trozar_luz(punt,&habitaciones[i]);
        }
        ///BUSCAMOS PIPE Y LEEMOS CANTIDAD DE AIRES
        punt = pipe + 1;
        pipe = strchr(punt,'|');
        if(pipe)
            *pipe = '\0';
        else{
            pipe = strchr(punt,'\n');
            *pipe = '\0';
        }
        habitaciones[i].cant_aires = atoi(punt);
        ///BUSCAMOS PIPE Y LEEMOS AIRES, SI HAY AIRES
        if(habitaciones[i].cant_aires > 0){
            punt = pipe + 1;
            pipe = strchr(punt,'|');
            if(pipe)
                *pipe = '\0';
            trozar_aire(punt,&habitaciones[i]);
        }
        ///BUSCAMOS PIPE Y LEEMOS CANTIDAD DE SMART TV
        punt = pipe + 1;
        pipe = strchr(punt,'|');
        if(pipe)
            *pipe = '\0';
        else{
            pipe = strchr(punt,'\n');
            *pipe = '\0';
        }
        habitaciones[i].hay_tele = atoi(punt);
        ///BUSCAMOS PIPE Y LEEMOS SMART TV, SI HAY TV
        if(habitaciones[i].hay_tele){
            punt = pipe + 1;
            pipe = strchr(punt,'|');
            if(pipe)
                *pipe = '\0';
            trozar_tele(punt,&habitaciones[i]);
        }
*/
        i++;
    }
    fclose(pf);

}
void cargar_dispositivos(t_habitacion *hab, int cant, char *cad, int disp)
{
    if(disp == LUCES){
        hab->cant_luces = cant;
        cant?trozar_luz(cad, hab):NULL;
    }
    if(disp == AIRES){
        hab->cant_aires = cant;
        cant?trozar_aire(cad, hab):NULL;
    }
    if(disp == SMART_TV){
        hab->hay_tele = cant;
        cant?trozar_tele(cad, hab):NULL;
    }
}

void trozar_luz(char * punt, t_habitacion * h)
{
    int estado;
    int cant_luces, k;
    char * dos_puntos;
    cant_luces = h->cant_luces;
    h->luces = (t_luz *)malloc(cant_luces * sizeof(t_luz));
    for(k = 0; k < cant_luces; k++)
    {
        dos_puntos = strchr(punt,':');
        if(dos_puntos)
        {
            *dos_puntos = '\0';
            dos_puntos ++;
        }
        sscanf(punt,"%d;%d;%s",
           &estado,
           &h->luces[k].intensidad,
           h->luces[k].color);
        h->luces[k].estado = (estado != 0);
        punt = dos_puntos;
        printf("%s;%d;%s|", h->luces[k].estado ? "true" : "false", h->luces[k].intensidad, h->luces[k].color);
    }
}
void trozar_aire(char * punt, t_habitacion * h)
{
    int estado;
    int cant_aires = h->cant_aires;
    int i;
    char * dos_puntos;
    h->aires = (t_aire *)malloc(cant_aires * sizeof(t_aire));
    if(!h->aires)
        return;
    for(i = 0; i < cant_aires; i++)
    {
        dos_puntos = strchr(punt,':');
        if(dos_puntos)
        {
            *dos_puntos = '\0';
            dos_puntos ++;
        }
        sscanf(punt,"%d;%d;%s",
           &estado,
           &h->aires[i].temperatura,
           h->aires[i].modo);

        h->aires[i].estado = (estado != 0);
        punt = dos_puntos;
        printf("%s;%d;%s|", h->aires[i].estado ? "true" : "false", h->aires[i].temperatura, h->aires[i].modo);

    }
}
void trozar_tele(char * punt, t_habitacion * h)
{
    int estado;
    char * salto;
    h->tele = (t_televisor *) malloc(sizeof(t_televisor));
    if(!h->tele)
        return;
    salto = strchr(punt,'\n'); /// Cambiar a '\r' para linux
    *salto = '\0';
    sscanf(punt,"%d;%d;%s",
           &estado,
           &h->tele->volumen,
           h->tele->fuente);
    h->tele->estado = (estado != 0);
    printf("%s;%s;%d|", h->tele->estado ? "true" : "false", h->tele->fuente, h->tele->volumen);
}
