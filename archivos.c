#include <stdio.h>
#include <string.h>
#include "archivos.h"

void cargarArchivo(Orden ordenes[], int *cantidad)
{
    FILE *archivo;

    archivo = fopen("ordenes.csv", "r");

    if(archivo == NULL)
        return;

    char linea[256];

    // Saltar la cabecera
    fgets(linea, sizeof(linea), archivo);

    *cantidad = 0;

    while(fscanf(archivo,
                 "%15[^,],%49[^,],%49[^,],%49[^,],%f,%d\n",
                 ordenes[*cantidad].codigo_orden,
                 ordenes[*cantidad].nombre_cliente,
                 ordenes[*cantidad].equipo,
                 ordenes[*cantidad].tipo_trabajo,
                 &ordenes[*cantidad].costo_base,
                 &ordenes[*cantidad].horas_trabajo) == 6)
    {
        (*cantidad)++;

        if(*cantidad >= MAX_ORDENES)
            break;
    }

    fclose(archivo);
}

void guardarArchivo(Orden ordenes[], int cantidad)
{
    FILE *archivo;
    int i;

    archivo = fopen("ordenes.csv", "w");

    if(archivo == NULL)
    {
        printf("Error al crear el archivo.\n");
        return;
    }

    fprintf(archivo,
            "codigo_orden,nombre_cliente,equipo,tipo_trabajo,costo_base,horas_trabajo\n");

    for(i = 0; i < cantidad; i++)
    {
        fprintf(archivo,
                "%s,%s,%s,%s,%.2f,%d\n",
                ordenes[i].codigo_orden,
                ordenes[i].nombre_cliente,
                ordenes[i].equipo,
                ordenes[i].tipo_trabajo,
                ordenes[i].costo_base,
                ordenes[i].horas_trabajo);
    }

    fclose(archivo);

    printf("\nDatos guardados correctamente.\n");
}
