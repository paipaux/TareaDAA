#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "arboles.h"

MBR* NearestX(MBR *elementos, int n, int *nPadres, Nodo *arbolRAM, int *indiceActual) {
    qsort(elementos, n, sizeof(MBR), compararX);
    int numNodos = (int)ceil((double)n / B);
    MBR *padres = malloc(sizeof(MBR) * numNodos);
    
    int contador = 0;
    for (int i = 0; i < n; i += B) {
        int finNodo = (i + B > n) ? n : (i + B);
        
        padres[contador++] = guardarNodoEnRAM(&elementos[i], finNodo - i, arbolRAM, *indiceActual);
        
        (*indiceActual)++; 
    }
    *nPadres = contador;
    return padres; 
}