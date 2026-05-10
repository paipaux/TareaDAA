#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arboles.h"

MBR* leerDataset(const char *nombreArchivo, int N) {
    FILE *f = fopen(nombreArchivo, "rb");
    if (f == NULL) {
        return NULL;
    }

    MBR *puntos = malloc(sizeof(MBR) * N);
    if (puntos == NULL) {
        fclose(f);
        return NULL;
    }

    float par_xy[2]; 

    for (int i = 0; i < N; i++) {
        if (fread(par_xy, sizeof(float), 2, f) != 2) {
            break;
        }

        puntos[i].x1 = par_xy[0]; // Coordenada X
        puntos[i].x2 = par_xy[0]; // Coordenada X
        puntos[i].y1 = par_xy[1]; // Coordenada Y
        puntos[i].y2 = par_xy[1]; // Coordenada Y
        
        puntos[i].pos = -1; 
    }

    fclose(f);
    return puntos;
}

int main() {
    int n_inicial = 32768;      // 2^15
    int n_final = 16777216;     // 2^24

    printf("Inicio\n");

    for (int N = n_inicial; N <= n_final; N *= 2) {
        printf("\n--- Evaluando N = %d ---\n", N);

        // 1. Cargar datos en memoria
        MBR *datosAleatorios = leerDataset("datasets/random.bin", N);
        MBR *datosEuropa = leerDataset("datasets/europa.bin", N);

        if (datosAleatorios == NULL || datosEuropa == NULL) {
            printf("Error fatal: No se pudieron cargar los datasets.\n");
            return 1;
        }

        // Variables para medición de tiempo
        clock_t inicio, fin;
        double tiempo_usado;

        // Aleatorio Nearest-X 
        inicio = clock();
        construirArbol(datosAleatorios, N, 1, "rtree_rand_nx.bin");
        fin = clock();
        tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
        printf("Aleatorio Nearest-X: %f segundos\n", tiempo_usado);

        // Aleatorio STR 
        inicio = clock();
        construirArbol(datosAleatorios, N, 2, "rtree_rand_str.bin");
        fin = clock();
        tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
        printf("Aleatorio STR: %f segundos\n", tiempo_usado);

        // Europa Nearest-X 
        inicio = clock();
        construirArbol(datosEuropa, N, 1, "rtree_euro_nx.bin");
        fin = clock();
        tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
        printf("Europa Nearest-X: %f segundos\n", tiempo_usado);

        // Europa STR
        inicio = clock();
        construirArbol(datosEuropa, N, 2, "rtree_euro_str.bin");
        fin = clock();
        tiempo_usado = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
        printf("Europa STR: %f segundos\n", tiempo_usado);

        // Liberar memoria de los arreglos base antes de la siguiente iteración
        free(datosAleatorios);
        free(datosEuropa);
    }

    printf("\nFin Construcción\n");
    
    // Consultaas
    float escalas_s[] = {0.0025, 0.005, 0.01, 0.025, 0.05};
    const char *archivos[] = {
        "rtree_rand_nx.bin", 
        "rtree_rand_str.bin", 
        "rtree_euro_nx.bin", 
        "rtree_euro_str.bin"
    };

    printf("\nFase de Consultas\n");
    
    //Seed
    srand(time(NULL));

    for (int j = 0; j < 4; j++) {
        printf("RESULTADOS PARA EL ARBOL: %s\n", archivos[j]);

        for (int k = 0; k < 5; k++) {
            realizarExperimentoConsultas(archivos[j], escalas_s[k]);
        }
    }

    printf("\nFin de Consultas\n");
    return 0;
}