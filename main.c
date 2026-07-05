#include <stdio.h>
#include "ordenes.h"
#include "archivos.h"

int main()
{
    Orden ordenes[MAX_ORDENES];
    int cantidad = 0;
    int opcion;

    cargarArchivo(ordenes, &cantidad);

    do
    {
        printf("\n=========================================\n");
        printf(" SISTEMA DE ORDENES DE TRABAJO\n");
        printf("=========================================\n");
        printf("1. Registrar orden\n");
        printf("2. Listar ordenes\n");
        printf("3. Buscar orden\n");
        printf("4. Actualizar orden\n");
        printf("5. Eliminar orden\n");
        printf("6. Guardar cambios en archivo\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarOrden(ordenes, &cantidad);
                break;

            case 2:
                listarOrdenes(ordenes, cantidad);
                break;

            case 3:
                buscarOrden(ordenes, cantidad);
                break;

            case 4:
                actualizarOrden(ordenes, cantidad);
                break;

            case 5:
                eliminarOrden(ordenes, &cantidad);
                break;

            case 6:
                guardarArchivo(ordenes, cantidad);
                break;

            case 7:
                guardarArchivo(ordenes, cantidad);
                printf("\nDatos guardados.\n");
                printf("Hasta luego.\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
        }

    } while(opcion != 7);

    return 0;
}
