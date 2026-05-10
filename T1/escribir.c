#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "arboles.h"

MBR guardarNodoEnRAM(MBR *grupo, int n, Nodo *arbolRAM, int indice) {
    Nodo nodo;
    nodo.k = n;
    float minX1 = FLT_MAX, maxX2 = -FLT_MAX, minY1 = FLT_MAX, maxY2 = -FLT_MAX;

    for (int i = 0; i < n; i++) {
        nodo.hijos[i] = (Hijo){grupo[i].x1, grupo[i].x2, grupo[i].y1, grupo[i].y2, grupo[i].pos};
        
        if (grupo[i].x1 < minX1) minX1 = grupo[i].x1;
        if (grupo[i].x2 > maxX2) maxX2 = grupo[i].x2;
        if (grupo[i].y1 < minY1) minY1 = grupo[i].y1;
        if (grupo[i].y2 > maxY2) maxY2 = grupo[i].y2;
    }

    for (int i = n; i < B; i++) {
        nodo.hijos[i] = (Hijo){0,0,0,0,-1};
    }

    // Guardamos directo en la memoria RAM
    arbolRAM[indice] = nodo;

    return (MBR){minX1, maxX2, minY1, maxY2, indice};
}