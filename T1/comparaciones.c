#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "arboles.h"

int compararX(const void *a, const void *b) {
    MBR *mbrA = (MBR *)a;
    MBR *mbrB = (MBR *)b;
    float centroA = (mbrA->x1 + mbrA->x2) / 2.0;
    float centroB = (mbrB->x1 + mbrB->x2) / 2.0;

    if (centroA < centroB) return -1;
    if (centroA > centroB) return 1;
    return 0;
}

int compararY(const void *a, const void *b) {
    MBR *mA = (MBR*)a; 
    MBR *mB = (MBR*)b;
    float centroA = (mA->y1 + mA->y2) / 2.0; 
    float centroB = (mB->y1 + mB->y2) / 2.0;
    
    if (centroA < centroB) return -1;
    if (centroA > centroB) return 1;
    return 0;
}
