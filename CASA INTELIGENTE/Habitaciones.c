#include "Habitaciones.h"

void inicializar_habitaciones(t_habitacion * habitaciones, const char *archivo)
{
    FILE *pf = fopen("Archivos/Habitaciones.txt", "rt");
    char buffer[TAM_BUFFER];
    char * pipe, * punt = buffer;
    int i = 0;
    if(!pf)
        printf("Error al abrir el archivo: %s\n", archivo);
    while(fgets(buffer,TAM_BUFFER,pf) && (*buffer!='\r'))
    {
        ///Leemos nombre de habitacion
        printf("\n");
        pipe = strchr(buffer,'|');
        if(pipe)
            *pipe = '\0';
        strcpy(habitaciones[i].nombre_habitacion,buffer);
        printf("%s|",habitaciones[i].nombre_habitacion);
        pipe ++;
        /// Nos posicionamos en cantidad de luces
        punt = pipe;
        pipe = strchr(pipe,'|');///
        if(pipe)
            *pipe = '\0';
        habitaciones[i].cant_luces = atoi(punt);
        ///Movemos pipe a el campo de las luces
        pipe ++;
        punt = pipe;///cadena luces
        pipe = strchr(pipe,'|');
        ///Pisamos el | final de campo de luces
        if(pipe)
            *pipe = '\0';
        ///
        pipe ++; ///cantidad de aires
        trozar_luz(punt,&habitaciones[i]);
        punt = pipe;///cantidad de aires
        printf("cant_luces : %d|",habitaciones[i].cant_luces);
        pipe = strchr(pipe,'|');///fin de cant de aires
        if(pipe)
            *pipe = '\0';
        habitaciones[i].cant_aires = atoi(punt);
        if(habitaciones[i].cant_aires > 0){
            pipe ++;///ERROR o campo aires o hay_teles
            punt = pipe;
            ///Pisamos el | final de campo de aires
            pipe = strchr(pipe,'|');
            if(pipe)
                *pipe = '\0';
            trozar_aire(punt,&habitaciones[i]);
        }
        pipe ++;//hay_tele
        punt = pipe;
        //
        pipe = strchr(pipe,'|');
        if(pipe)
            *pipe = '\0';
        else{
            pipe = strchr(punt,'\n');
            *pipe = '\0';
        }
        habitaciones[i].hay_tele = atoi(punt);
        if(habitaciones[i].hay_tele){
            pipe ++;
            punt = pipe;
            trozar_tele(punt,&habitaciones[i]);
        }

        i++;
    }
    fclose(pf);

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
    salto = strchr(punt,'\r'); /// Cambiar a '\r' para linux
    *salto = '\0';
    sscanf(punt,"%d;%d;%s",
           &estado,
           &h->tele->volumen,
           h->tele->fuente);
    h->tele->estado = (estado != 0);
    printf("%s;%s;%d|", h->tele->estado ? "true" : "false", h->tele->fuente, h->tele->volumen);
}
