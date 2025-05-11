#include "Habitaciones.h"

void inicializar_habitaciones(t_habitacion * habitaciones, const char *archivo){
    FILE *pf = fopen(archivo, "w+t");
    if(!pf)
        printf("Error al abrir el archivo: %s\n", archivo);
    fclose(pf);

}
