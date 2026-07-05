#ifndef ORDENES_H
#define ORDENES_H

#define MAX_ORDENES 100
#define TARIFA_HORA 10.0

typedef struct
{
    char codigo_orden[16];
    char nombre_cliente[50];
    char equipo[50];
    char tipo_trabajo[50];
    float costo_base;
    int horas_trabajo;
} Orden;

// Gestión de órdenes
void registrarOrden(Orden ordenes[], int *cantidad);
void listarOrdenes(Orden ordenes[], int cantidad);
void buscarOrden(Orden ordenes[], int cantidad);
void actualizarOrden(Orden ordenes[], int cantidad);
void eliminarOrden(Orden ordenes[], int *cantidad);

// Validaciones
int codigoExiste(Orden ordenes[], int cantidad, char codigo[]);
float calcularCostoTotal(Orden orden);

#endif 
