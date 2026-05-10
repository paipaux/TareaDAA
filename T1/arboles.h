#ifndef ARBOLES_H
#define ARBOLES_H

#include <stdio.h>

#define B 204

// Estructuras

typedef struct {
    float x1, x2, y1, y2;
    int posicion;
} Hijo;

typedef struct {
    int k;
    Hijo hijos[B];
    char pad[12];
} Nodo;

typedef struct {
    float x1, x2, y1, y2;
    int pos;
} MBR;

// Variables globales 
extern int contadorLecturas;
extern int contadorPuntosEncontrados;

// Funciones
int compararX(const void *a, const void *b);
int compararY(const void *a, const void *b);
MBR guardarNodoEnRAM(MBR *grupo, int n, Nodo *arbolRAM, int indiceDondeGuardar);
MBR* NearestX(MBR *elementos, int n, int *nPadres, Nodo *arbolRAM, int *indiceActual);
MBR* STR(MBR *elementos, int n, int *nPadres, Nodo *arbolRAM, int *indiceActual);
void construirArbol(MBR *puntosOriginales, int N, int tipoAlgoritmo, const char *nombreArchivoSalida);
int intersecta(float x1_h, float x2_h, float y1_h, float y2_h, float R_x1, float R_x2, float R_y1, float R_y2);
void buscar(FILE *f, int posArchivo, float Rx1, float Rx2, float Ry1, float Ry2);
void realizarExperimentoConsultas(const char *nombreArchivo, float s);

#endif