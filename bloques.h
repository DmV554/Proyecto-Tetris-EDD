#ifndef BLOQUES_H
#define BLOQUES_H
#include "list.h"

typedef enum {
    Cuadrado, I, L1, L2, Z, S, T
} Pieza;

typedef struct Bloque {
    Pieza tipo;
    List*listaRotaciones;
    int **matrizBloque;
    int ancho;
} Bloque;

void inicializarCuadrado(List*);
void inicializarL1(List*);
void crearRotacionesL1(List*);
void inicializarL2(List*);
void crearRotacionesL2(List*);
void inicializarI(List*);
void crearRotacionesI(List*);
void inicializarT(List*);
void crearRotacionesT(List*);
void inicializarZ(List*);
void crearRotacionesZ(List*);
void inicializarS(List*);
void crearRotacionesS(List*);

#endif