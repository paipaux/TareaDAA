#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "arboles.h"

// Variables globales 
int contadorLecturas = 0;
int contadorPuntosEncontrados = 0;


int intersecta(float x1_h, float x2_h, float y1_h, float y2_h, float R_x1, float R_x2, float R_y1, float R_y2) {
    if (x2_h < R_x1 || x1_h > R_x2 || y2_h < R_y1 || y1_h > R_y2) {
        return 0; 
    }
    return 1; // se intersectan
}


Nodo leerNodo(FILE *f, int indiceNodo) {
    Nodo nodoLeido;
    fseek(f, (long)indiceNodo * sizeof(Nodo), SEEK_SET);
    fread(&nodoLeido, sizeof(Nodo), 1, f);
    
    contadorLecturas++;
    
    return nodoLeido;
}

void buscar(FILE *f, int posArchivo, float Rx1, float Rx2, float Ry1, float Ry2) {
    Nodo nodo = leerNodo(f, posArchivo);

    // se recoren hijos
    for (int i = 0; i < nodo.k; i++) {
        Hijo *h = &nodo.hijos[i];


        if (intersecta(h->x1, h->x2, h->y1, h->y2, Rx1, Rx2, Ry1, Ry2)) {
            

            if (h->posicion == -1) {
                contadorPuntosEncontrados++;
            } 
            else {
                buscar(f, h->posicion, Rx1, Rx2, Ry1, Ry2);
            }
        }
    }
}