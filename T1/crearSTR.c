#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "arboles.h"

MBR* STR(MBR *elementos, int n, int *nPadres, Nodo *arbolRAM, int *indiceActual) {
    qsort(elementos, n, sizeof(MBR), compararX);
    int numNodos = (int)ceil((double)n / B);
    int S = (int)ceil(sqrt(numNodos));
    int tamFranja = S * B;
    
    MBR *padres = malloc(sizeof(MBR) * numNodos);
    int contador = 0;

    for (int i = 0; i < n; i += tamFranja) {
        int finFranja = (i + tamFranja > n) ? n : (i + tamFranja);
        qsort(&elementos[i], finFranja - i, sizeof(MBR), compararY);
        for (int j = i; j < finFranja; j += B) {
            int finNodo = (j + B > finFranja) ? finFranja : (j + B);
            padres[contador++] = guardarNodoEnRAM(&elementos[j], finNodo - j, arbolRAM, *indiceActual);
            (*indiceActual)++;
        }
    }
    *nPadres = contador;
    return padres;
}