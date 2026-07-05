#include <stdio.h>
#include <string.h>
#include <ctype.h> // <- Librería necesaria para usar isdigit()
#include "ordenes.h"

// Función auxiliar para validar que el texto no tenga números
int tieneNumeros(char cadena[]) 
{
    int i;
    for(i = 0; cadena[i] != '\0'; i++) 
    {
        if(isdigit(cadena[i])) 
        {
            return 1; // Encontró un número
        }
    }
    return 0; // Texto limpio de números
}

int codigoExiste(Orden ordenes[], int cantidad, char codigo[])
{
    int i;
    for(i = 0; i < cantidad; i++)
    {
        if(strcmp(ordenes[i].codigo_orden, codigo) == 0)
            return 1;
    }
    return 0;
}

float calcularCostoTotal(Orden orden)
{
    return orden.costo_base + (orden.horas_trabajo * TARIFA_HORA);
}

void registrarOrden(Orden ordenes[], int *cantidad)
{
    if(*cantidad >= MAX_ORDENES)
    {
        printf("\nNo hay espacio disponible.\n");
        return;
    }

    Orden nueva;

    do
    {
        printf("Codigo de la orden: ");
        scanf("%15s", nueva.codigo_orden);

        if(codigoExiste(ordenes, *cantidad, nueva.codigo_orden))
            printf("El codigo ya existe.\n");

    }while(codigoExiste(ordenes, *cantidad, nueva.codigo_orden));

    // --- NOMBRE DEL CLIENTE (No permite números) ---
    do
    {
        while(getchar() != '\n'); // Limpia el buffer residual
        printf("Nombre del cliente: ");
        fgets(nueva.nombre_cliente, 50, stdin);
        nueva.nombre_cliente[strcspn(nueva.nombre_cliente, "\n")] = '\0';

        if(tieneNumeros(nueva.nombre_cliente))
            printf("Error: El nombre del cliente no puede contener numeros.\n");

    }while(tieneNumeros(nueva.nombre_cliente));

    // --- EQUIPO (Permite números) ---
    printf("Equipo: ");
    fgets(nueva.equipo, 50, stdin);
    nueva.equipo[strcspn(nueva.equipo, "\n")] = '\0';

    // --- TIPO DE TRABAJO (No permite números) ---
    do
    {
        printf("Tipo de trabajo: ");
        fgets(nueva.tipo_trabajo, 50, stdin);
        nueva.tipo_trabajo[strcspn(nueva.tipo_trabajo, "\n")] = '\0';

        if(tieneNumeros(nueva.tipo_trabajo))
            printf("Error: El tipo de trabajo no puede contener numeros.\n");

    }while(tieneNumeros(nueva.tipo_trabajo));

    // --- COSTO BASE ---
    do
    {
        printf("Costo base: ");
        scanf("%f", &nueva.costo_base);

        if(nueva.costo_base <= 0)
            printf("Debe ser mayor que 0.\n");

    }while(nueva.costo_base <= 0);

    // --- HORAS DE TRABAJO ---
    do
    {
        printf("Horas de trabajo: ");
        scanf("%d", &nueva.horas_trabajo);

        if(nueva.horas_trabajo < 0)
            printf("Debe ser mayor o igual a 0.\n");

    }while(nueva.horas_trabajo < 0);

    ordenes[*cantidad] = nueva;
    (*cantidad)++;

    printf("\nOrden registrada correctamente.\n");
}

void listarOrdenes(Orden ordenes[], int cantidad)
{
    int i;

    if(cantidad == 0)
    {
        printf("\nNo existen registros.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-20s %-10s\n",
           "Codigo", "Cliente", "Equipo", "Trabajo", "Total");
    printf("-------------------------------------------------------------------------------\n");

    for(i = 0; i < cantidad; i++)
    {
        printf("%-10s %-20s %-10s %-20s %.2f\n",
               ordenes[i].codigo_orden,
               ordenes[i].nombre_cliente,
               ordenes[i].equipo,
               ordenes[i].tipo_trabajo,
               calcularCostoTotal(ordenes[i]));
    }
}
void buscarOrden(Orden ordenes[], int cantidad)
{
    char codigo[16];
    int i, encontrado = 0;

    printf("Ingrese codigo: ");
    scanf("%15s", codigo);

    for(i = 0; i < cantidad; i++)
    {
        if(strcmp(codigo, ordenes[i].codigo_orden) == 0)
        {
            printf("\nCodigo: %s\n", ordenes[i].codigo_orden);
            printf("Cliente: %s\n", ordenes[i].nombre_cliente);
            printf("Equipo: %s\n", ordenes[i].equipo);
            printf("Trabajo: %s\n", ordenes[i].tipo_trabajo);
            printf("Costo base: %.2f\n", ordenes[i].costo_base);
            printf("Horas: %d\n", ordenes[i].horas_trabajo);
            printf("Costo total: %.2f\n", calcularCostoTotal(ordenes[i]));
            encontrado = 1;
            break;
        }
    }

    if(!encontrado)
        printf("Orden no encontrada.\n");
}

void actualizarOrden(Orden ordenes[], int cantidad)
{
    char codigo[16];
    int i;

    printf("Codigo de la orden: ");
    scanf("%15s", codigo);

    for(i = 0; i < cantidad; i++)
    {
        if(strcmp(codigo, ordenes[i].codigo_orden) == 0)
        {
            // --- NUEVO CLIENTE (No permite números) ---
            do
            {
                while(getchar() != '\n'); // Limpia el buffer
                printf("Nuevo cliente: ");
                fgets(ordenes[i].nombre_cliente, 50, stdin);
                ordenes[i].nombre_cliente[strcspn(ordenes[i].nombre_cliente, "\n")] = '\0';

                if(tieneNumeros(ordenes[i].nombre_cliente))
                    printf("Error: El nombre no puede contener numeros.\n");

            }while(tieneNumeros(ordenes[i].nombre_cliente));

            // --- NUEVO EQUIPO (Permite números) ---
            printf("Nuevo equipo: ");
            fgets(ordenes[i].equipo, 50, stdin);
            ordenes[i].equipo[strcspn(ordenes[i].equipo, "\n")] = '\0';

            // --- NUEVO TRABAJO (No permite números) ---
            do
            {
                printf("Nuevo tipo de trabajo: ");
                fgets(ordenes[i].tipo_trabajo, 50, stdin);
                ordenes[i].tipo_trabajo[strcspn(ordenes[i].tipo_trabajo, "\n")] = '\0';

                if(tieneNumeros(ordenes[i].tipo_trabajo))
                    printf("Error: El tipo de trabajo no puede contener numeros.\n");

            }while(tieneNumeros(ordenes[i].tipo_trabajo));

            // --- COSTO Y HORAS ---
            do
            {
                printf("Nuevo costo base: ");
                scanf("%f", &ordenes[i].costo_base);
            }while(ordenes[i].costo_base <= 0);

            do
            {
                printf("Nuevas horas: ");
                scanf("%d", &ordenes[i].horas_trabajo);
            }while(ordenes[i].horas_trabajo < 0);

            printf("Orden actualizada.\n");
            return;
        }
    }

    printf("Orden no encontrada.\n");
}

void eliminarOrden(Orden ordenes[], int *cantidad)
{
    char codigo[16];
    char op;
    int i, j;

    printf("Codigo de la orden: ");
    scanf("%15s", codigo);

    for(i = 0; i < *cantidad; i++)
    {
        if(strcmp(codigo, ordenes[i].codigo_orden) == 0)
        {
            printf("Seguro que desea eliminar? (S/N): ");
            scanf(" %c", &op);

            if(op == 'S' || op == 's')
            {
                for(j = i; j < *cantidad - 1; j++)
                {
                    ordenes[j] = ordenes[j + 1];
                }

                (*cantidad)--;

                printf("Orden eliminada.\n");
            }

            return;
        }
    }

    printf("Orden no encontrada.\n");
}