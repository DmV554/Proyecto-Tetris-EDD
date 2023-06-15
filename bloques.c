#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "bloques.h"

void inicializarCuadrado(List*listaBloques) {
    Bloque*cuadrado = (Bloque*)malloc(sizeof(Bloque));
    cuadrado->tipo = Cuadrado;
    cuadrado->listaRotaciones = createList();

    cuadrado->matrizBloque = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        cuadrado->matrizBloque[i] = (int*)malloc(2 * sizeof(int));
    }

    cuadrado->matrizBloque[0][0] = 1;   
    cuadrado->matrizBloque[0][1] = 1;   
    cuadrado->matrizBloque[1][0] = 1;
    cuadrado->matrizBloque[1][1] = 1;
    cuadrado->ancho = 2;
    pushBack(listaBloques, cuadrado);
}

void inicializarI(List*listaBloques) {
    Bloque*i = (Bloque*)malloc(sizeof(Bloque));
    i->tipo = I;

    i->matrizBloque = (int**)malloc(4* sizeof(int*));
    for (int k = 0; k < 4; k++) {
        i->matrizBloque[k] = (int*)malloc(4* sizeof(int));
    }
    
    i->matrizBloque[0][0] = 0;   
    i->matrizBloque[0][1] = 1;   
    i->matrizBloque[0][2] = 0;
    i->matrizBloque[0][3] = 0;
    i->matrizBloque[1][0] = 0;   
    i->matrizBloque[1][1] = 1;   
    i->matrizBloque[1][2] = 0;
    i->matrizBloque[1][3] = 0;
    i->matrizBloque[2][0] = 0;   
    i->matrizBloque[2][1] = 1;   
    i->matrizBloque[2][2] = 0;
    i->matrizBloque[2][3] = 0;
    i->matrizBloque[3][0] = 0;   
    i->matrizBloque[3][1] = 1;   
    i->matrizBloque[3][2] = 0;
    i->matrizBloque[3][3] = 0;

    i->listaRotaciones = createList();
    pushBack(i->listaRotaciones, i->matrizBloque);
    i->ancho = 4;
    crearRotacionesI(i->listaRotaciones);
    pushBack(listaBloques, i);
}

void crearRotacionesI(List*listaRotaciones) {
   int**matrizRotacion1 = (int**)malloc(4* sizeof(int*));
    for (int i = 0; i < 4; i++) {
        matrizRotacion1[i] = (int*)malloc(4* sizeof(int));
    }
    
    matrizRotacion1[0][0] = 0;   
    matrizRotacion1[0][1] = 0;   
    matrizRotacion1[0][2] = 0;
    matrizRotacion1[0][3] = 0;
    matrizRotacion1[1][0] = 0;   
    matrizRotacion1[1][1] = 0;   
    matrizRotacion1[1][2] = 0;
    matrizRotacion1[1][3] = 0;
    matrizRotacion1[2][0] = 0;   
    matrizRotacion1[2][1] = 0;   
    matrizRotacion1[2][2] = 0;
    matrizRotacion1[2][3] = 0;
    matrizRotacion1[3][0] = 1;   
    matrizRotacion1[3][1] = 1;   
    matrizRotacion1[3][2] = 1;
    matrizRotacion1[3][3] = 1;
    
    pushBack(listaRotaciones, matrizRotacion1);

}

void inicializarL1(List*listaBloques) {
    Bloque*l1 = (Bloque*)malloc(sizeof(Bloque));

    l1->tipo = L1;
    
    l1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        l1->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    l1->matrizBloque[0][0] = 1;
    l1->matrizBloque[0][1] = 0;
    l1->matrizBloque[0][2] = 0;
    l1->matrizBloque[1][0] = 1;
    l1->matrizBloque[1][1] = 0;   
    l1->matrizBloque[1][2] = 0;
    l1->matrizBloque[2][0] = 1;
    l1->matrizBloque[2][1] = 1;
    l1->matrizBloque[2][2] = 0;

    l1->listaRotaciones = createList();
    pushBack(l1->listaRotaciones, l1->matrizBloque);
    l1->ancho = 3;
    crearRotacionesL1(l1->listaRotaciones);

    pushBack(listaBloques, l1);
}

void crearRotacionesL1(List*listaRotaciones) {

    int**matrizRotacion1 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion1[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion1[0][0] = 0;
    matrizRotacion1[0][1] = 0;
    matrizRotacion1[0][2] = 0;
    matrizRotacion1[1][0] = 0;
    matrizRotacion1[1][1] = 0;   
    matrizRotacion1[1][2] = 1;
    matrizRotacion1[2][0] = 1;
    matrizRotacion1[2][1] = 1;
    matrizRotacion1[2][2] = 1;

    pushBack(listaRotaciones, matrizRotacion1);

    int**matrizRotacion2 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion2[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion2[0][0] = 0;
    matrizRotacion2[0][1] = 1;
    matrizRotacion2[0][2] = 1;
    matrizRotacion2[1][0] = 0;
    matrizRotacion2[1][1] = 0;   
    matrizRotacion2[1][2] = 1;
    matrizRotacion2[2][0] = 0;
    matrizRotacion2[2][1] = 0;
    matrizRotacion2[2][2] = 1;

    pushBack(listaRotaciones, matrizRotacion2);

    int**matrizRotacion3 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion3[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion3[0][0] = 1;
    matrizRotacion3[0][1] = 1;
    matrizRotacion3[0][2] = 1;
    matrizRotacion3[1][0] = 1;
    matrizRotacion3[1][1] = 0;
    matrizRotacion3[1][2] = 0;
    matrizRotacion3[2][0] = 0;
    matrizRotacion3[2][1] = 0;
    matrizRotacion3[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion3);
}

void inicializarL2(List*listaBloques) {
    Bloque*l2 = (Bloque*)malloc(sizeof(Bloque));

    l2->tipo = L2;
    
    l2->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        l2->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    l2->matrizBloque[0][0] = 0;
    l2->matrizBloque[0][1] = 0;
    l2->matrizBloque[0][2] = 1;
    l2->matrizBloque[1][0] = 0;
    l2->matrizBloque[1][1] = 0;   
    l2->matrizBloque[1][2] = 1;
    l2->matrizBloque[2][0] = 0;
    l2->matrizBloque[2][1] = 1;
    l2->matrizBloque[2][2] = 1;

    l2->listaRotaciones = createList();
    pushBack(l2->listaRotaciones, l2->matrizBloque);
    l2->ancho = 3;
    crearRotacionesL2(l2->listaRotaciones);

    pushBack(listaBloques, l2);

}

void crearRotacionesL2(List*listaRotaciones) {

    int**matrizRotacion1 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion1[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion1[0][0] = 1;
    matrizRotacion1[0][1] = 1;
    matrizRotacion1[0][2] = 1;
    matrizRotacion1[1][0] = 0;
    matrizRotacion1[1][1] = 0;   
    matrizRotacion1[1][2] = 1;
    matrizRotacion1[2][0] = 0;
    matrizRotacion1[2][1] = 0;
    matrizRotacion1[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion1);

    int**matrizRotacion2 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion2[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion2[0][0] = 1;
    matrizRotacion2[0][1] = 1;
    matrizRotacion2[0][2] = 0;
    matrizRotacion2[1][0] = 1;
    matrizRotacion2[1][1] = 0;   
    matrizRotacion2[1][2] = 0;
    matrizRotacion2[2][0] = 1;
    matrizRotacion2[2][1] = 0;
    matrizRotacion2[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion2);

    int**matrizRotacion3 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion3[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion3[0][0] = 0;
    matrizRotacion3[0][1] = 0;
    matrizRotacion3[0][2] = 0;
    matrizRotacion3[1][0] = 1;
    matrizRotacion3[1][1] = 0;
    matrizRotacion3[1][2] = 0;
    matrizRotacion3[2][0] = 1;
    matrizRotacion3[2][1] = 1;
    matrizRotacion3[2][2] = 1;

    pushBack(listaRotaciones, matrizRotacion3);
}

void inicializarT(List*listaBloques){
   Bloque*t = (Bloque*)malloc(sizeof(Bloque));

    t->tipo = T;
    
    t->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        t->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    t->matrizBloque[0][0] = 0;
    t->matrizBloque[0][1] = 0;
    t->matrizBloque[0][2] = 0;
    t->matrizBloque[1][0] = 0;
    t->matrizBloque[1][1] = 1;   
    t->matrizBloque[1][2] = 0;
    t->matrizBloque[2][0] = 1;
    t->matrizBloque[2][1] = 1;
    t->matrizBloque[2][2] = 1;

    t->listaRotaciones = createList();
    pushBack(t->listaRotaciones, t->matrizBloque);
    t->ancho = 3;
    crearRotacionesT(t->listaRotaciones);

    pushBack(listaBloques, t);    
}

void crearRotacionesT(List* listaRotaciones){
   int**matrizRotacion1 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion1[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion1[0][0] = 0;
    matrizRotacion1[0][1] = 0;
    matrizRotacion1[0][2] = 1;
    matrizRotacion1[1][0] = 0;
    matrizRotacion1[1][1] = 1;   
    matrizRotacion1[1][2] = 1;
    matrizRotacion1[2][0] = 0;
    matrizRotacion1[2][1] = 0;
    matrizRotacion1[2][2] = 1;

    pushBack(listaRotaciones, matrizRotacion1);

    int**matrizRotacion2 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion2[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion2[0][0] = 1;
    matrizRotacion2[0][1] = 1;
    matrizRotacion2[0][2] = 1;
    matrizRotacion2[1][0] = 0;
    matrizRotacion2[1][1] = 1;   
    matrizRotacion2[1][2] = 0;
    matrizRotacion2[2][0] = 0;
    matrizRotacion2[2][1] = 0;
    matrizRotacion2[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion2);

    int**matrizRotacion3 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion3[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion3[0][0] = 1;
    matrizRotacion3[0][1] = 0;
    matrizRotacion3[0][2] = 0;
    matrizRotacion3[1][0] = 1;
    matrizRotacion3[1][1] = 1;
    matrizRotacion3[1][2] = 0;
    matrizRotacion3[2][0] = 1;
    matrizRotacion3[2][1] = 0;
    matrizRotacion3[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion3);
}

void inicializarZ(List*listaBloques){
   Bloque*z = (Bloque*)malloc(sizeof(Bloque));

    z->tipo = Z;
    
    z->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        z->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    z->matrizBloque[0][0] = 0;
    z->matrizBloque[0][1] = 0;
    z->matrizBloque[0][2] = 0;
    z->matrizBloque[1][0] = 0;
    z->matrizBloque[1][1] = 1;   
    z->matrizBloque[1][2] = 1;
    z->matrizBloque[2][0] = 1;
    z->matrizBloque[2][1] = 1;
    z->matrizBloque[2][2] = 0;

    z->listaRotaciones = createList();
    pushBack(z->listaRotaciones, z->matrizBloque);
    z->ancho = 3;
    crearRotacionesZ(z->listaRotaciones);

    pushBack(listaBloques, z);    
}


void crearRotacionesZ(List* listaRotaciones){
   int**matrizRotacion1 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion1[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion1[0][0] = 0;
    matrizRotacion1[0][1] = 1;
    matrizRotacion1[0][2] = 0;
    matrizRotacion1[1][0] = 0;
    matrizRotacion1[1][1] = 1;   
    matrizRotacion1[1][2] = 1;
    matrizRotacion1[2][0] = 0;
    matrizRotacion1[2][1] = 0;
    matrizRotacion1[2][2] = 1;

    pushBack(listaRotaciones, matrizRotacion1);

}

void inicializarS(List*listaBloques){
   Bloque*s = (Bloque*)malloc(sizeof(Bloque));

    s->tipo = S;
    
    s->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        s->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    s->matrizBloque[0][0] = 0;
    s->matrizBloque[0][1] = 0;
    s->matrizBloque[0][2] = 0;
    s->matrizBloque[1][0] = 1;
    s->matrizBloque[1][1] = 1;   
    s->matrizBloque[1][2] = 0;
    s->matrizBloque[2][0] = 0;
    s->matrizBloque[2][1] = 1;
    s->matrizBloque[2][2] = 1;

    s->listaRotaciones = createList();
    pushBack(s->listaRotaciones, s->matrizBloque);
    s->ancho = 3;
    crearRotacionesS(s->listaRotaciones);

    pushBack(listaBloques, s);    
}

void crearRotacionesS(List* listaRotaciones){
   int**matrizRotacion1 = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        matrizRotacion1[i] = (int*)malloc(3* sizeof(int));
    }

    matrizRotacion1[0][0] = 0;
    matrizRotacion1[0][1] = 0;
    matrizRotacion1[0][2] = 1;
    matrizRotacion1[1][0] = 0;
    matrizRotacion1[1][1] = 1;   
    matrizRotacion1[1][2] = 1;
    matrizRotacion1[2][0] = 0;
    matrizRotacion1[2][1] = 1;
    matrizRotacion1[2][2] = 0;

    pushBack(listaRotaciones, matrizRotacion1);

}

