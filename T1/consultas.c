#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "arboles.h"



float generarCoordenadaAleatoria(float s) {
    float max_val = 1.0f - s;
    return ((float)rand() / (float)RAND_MAX) * max_val;
}

void realizarExperimentoConsultas(const char *nombreArchivo, float s) {
    FILE *f = fopen(nombreArchivo, "rb");
    if (f == NULL) {
        printf("Error: No se pudo abrir %s\n", nombreArchivo);
        return;
    }

    int totalLecturas = 0;
    int totalPuntos = 0;
    
    // Arreglo para guardar los puntos encontrados 
    int puntosPorConsulta[100]; 

    printf("\n--- Evaluando %s con s = %f ---\n", nombreArchivo, s);

    for (int i = 0; i < 100; i++) {
        // Generar cuadrado aleatorio de tamaño s
        float Rx1 = generarCoordenadaAleatoria(s);
        float Ry1 = generarCoordenadaAleatoria(s);
        float Rx2 = Rx1 + s;
        float Ry2 = Ry1 + s;


        contadorLecturas = 0;
        contadorPuntosEncontrados = 0;

        // Iniciar busqueda
        buscar(f, 0, Rx1, Rx2, Ry1, Ry2);


        totalLecturas += contadorLecturas;
        totalPuntos += contadorPuntosEncontrados;
        puntosPorConsulta[i] = contadorPuntosEncontrados;
    }

    // Calcular promedios
    double promedioLecturas = (double)totalLecturas / 100.0;
    double promedioPuntos = (double)totalPuntos / 100.0;

    // Calcular d estandar
    double sumaVarianza = 0.0;
    for (int i = 0; i < 100; i++) {
        sumaVarianza += pow(puntosPorConsulta[i] - promedioPuntos, 2);
    }
    double desviacionEstandar = sqrt(sumaVarianza / 100.0);

    printf("Promedio de lecturas %.2f\n", promedioLecturas);
    printf("Promedio de puntos  %.2f\n", promedioPuntos);
    printf("Desviacion estandar de puntos %.2f\n", desviacionEstandar);

    fclose(f);
}