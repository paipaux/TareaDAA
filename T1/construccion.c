#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arboles.h"


void construirArbol(MBR *puntosOriginales, int N, int tipoAlgoritmo, const char *nombreArchivoSalida) {
    
    // Calcular tamaño máximo del arreglo en RAM.
    int maxNodos = (N / (B / 2)) + 10; 
    Nodo *arbolRAM = malloc(sizeof(Nodo) * maxNodos);
    if (arbolRAM == NULL) {
        printf("Error: No hay memoria suficiente para el arbol en RAM.\n");
        return;
    }

    int indiceActual = 1; 
    int nNodosNivel = N;
    MBR *elementosNivel = puntosOriginales; 

    while (nNodosNivel > 1) {
        int nPadres = 0;
        MBR *padresGenerados = NULL;

        if (tipoAlgoritmo == 1) {
            padresGenerados = NearestX(elementosNivel, nNodosNivel, &nPadres, arbolRAM, &indiceActual);
        } else {
            padresGenerados = STR(elementosNivel, nNodosNivel, &nPadres, arbolRAM, &indiceActual);
        }

        if (elementosNivel != puntosOriginales) {
            free(elementosNivel);
        }


        elementosNivel = padresGenerados;
        nNodosNivel = nPadres;
    }

    arbolRAM[0] = arbolRAM[indiceActual - 1];

    // meter a disco
    FILE *out = fopen(nombreArchivoSalida, "wb");
    if (out != NULL) {
        fwrite(arbolRAM, sizeof(Nodo), indiceActual - 1, out);
        fclose(out);
        printf("Arbol construido y guardado en %s con %d nodos en total.\n", nombreArchivoSalida, indiceActual - 1);
    } else {
        printf("Error al crear el archivo %s\n", nombreArchivoSalida);
    }

    free(arbolRAM);
    if (elementosNivel != puntosOriginales) {
        free(elementosNivel);
    }
}