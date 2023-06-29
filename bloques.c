#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
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

    i->matrizBloque = (int**)malloc(4 * sizeof(int*));
    for (int k = 0; k < 4; k++) {
        i->matrizBloque[k] = (int*)malloc(1 * sizeof(int));
    }
    
    i->matrizBloque[0][0] = 1;   
    i->matrizBloque[1][0] = 1;   
    i->matrizBloque[2][0] = 1;
    i->matrizBloque[3][0] = 1;

    i->listaRotaciones = createList();
    BloqueRotado*BloqueRotado0 = malloc(sizeof(BloqueRotado));
    //BloqueRotado0->matrizBloque = i->matrizBloque;

    BloqueRotado0->matrizBloque = (int**)malloc(4 * sizeof(int*));
    for (int j = 0; j< 4; j++) {
        BloqueRotado0->matrizBloque[j] = (int*)malloc(1 * sizeof(int));
        memcpy(BloqueRotado0->matrizBloque[j], i->matrizBloque[j], 1 * sizeof(int));
    }

    BloqueRotado0->alto = 4;
    BloqueRotado0->ancho = 1;
    pushBack(i->listaRotaciones, BloqueRotado0);

    i->ancho = 1;
    i->alto = 4;
    crearRotacionesI(i->listaRotaciones);
    pushBack(listaBloques, i);
}

void crearRotacionesI(List*listaRotaciones) {
  BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));
  
    bloqueRotado1->matrizBloque = (int**)malloc(1* sizeof(int*));
    for (int i = 0; i < 1; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(4* sizeof(int));
    }
    
    bloqueRotado1->matrizBloque[0][0] = 1;   
    bloqueRotado1->matrizBloque[0][1] = 1;   
    bloqueRotado1->matrizBloque[0][2] = 1;
    bloqueRotado1->matrizBloque[0][3] = 1;

    bloqueRotado1->alto = 1;
    bloqueRotado1->ancho = 4;
    
    pushBack(listaRotaciones, bloqueRotado1);

}

void inicializarL1(List*listaBloques) {
    Bloque*l1 = (Bloque*)malloc(sizeof(Bloque));

    l1->tipo = L1;
    
    l1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        l1->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    l1->matrizBloque[0][0] = 1;
    l1->matrizBloque[0][1] = 0;
    l1->matrizBloque[1][0] = 1;
    l1->matrizBloque[1][1] = 0;   
    l1->matrizBloque[2][0] = 1;
    l1->matrizBloque[2][1] = 1;
    
    l1->listaRotaciones = createList();

    BloqueRotado*BloqueRotado0 = malloc(sizeof(BloqueRotado));
    //BloqueRotado0->matrizBloque = l1->matrizBloque;

    BloqueRotado0->matrizBloque = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        BloqueRotado0->matrizBloque[i] = (int*)malloc(2 * sizeof(int));
        memcpy(BloqueRotado0->matrizBloque[i], l1->matrizBloque[i], 2 * sizeof(int));
    }

    BloqueRotado0->alto = 3;
    BloqueRotado0->ancho = 2;
    pushBack(l1->listaRotaciones, BloqueRotado0);
    
    l1->ancho = 2;
    l1->alto = 3;

    crearRotacionesL1(l1->listaRotaciones);
    pushBack(listaBloques, l1);
}

void crearRotacionesL1(List*listaRotaciones) {
    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));

    bloqueRotado1->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 1;
    bloqueRotado1->matrizBloque[0][1] = 1;
    bloqueRotado1->matrizBloque[0][2] = 1;
    bloqueRotado1->matrizBloque[1][0] = 1;   
    bloqueRotado1->matrizBloque[1][1] = 0;
    bloqueRotado1->matrizBloque[1][2] = 0;

    bloqueRotado1->alto = 2;
    bloqueRotado1->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado1);

    BloqueRotado*bloqueRotado2 = malloc(sizeof(BloqueRotado));
    bloqueRotado2->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado2->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado2->matrizBloque[0][0] = 1;
    bloqueRotado2->matrizBloque[0][1] = 1;
    bloqueRotado2->matrizBloque[1][0] = 0;
    bloqueRotado2->matrizBloque[1][1] = 1;   
    bloqueRotado2->matrizBloque[2][0] = 0;
    bloqueRotado2->matrizBloque[2][1] = 1;

    bloqueRotado2->alto = 3;
    bloqueRotado2->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado2);

    BloqueRotado*bloqueRotado3 = malloc(sizeof(BloqueRotado));

    bloqueRotado3->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado3->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    bloqueRotado3->matrizBloque[0][0] = 0;
    bloqueRotado3->matrizBloque[0][1] = 0;
    bloqueRotado3->matrizBloque[0][2] = 1;
    bloqueRotado3->matrizBloque[1][0] = 1;
    bloqueRotado3->matrizBloque[1][1] = 1;
    bloqueRotado3->matrizBloque[1][2] = 1;

    bloqueRotado3->alto = 2;
    bloqueRotado3->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado3);
}

void inicializarL2(List*listaBloques) {
    Bloque*l2 = (Bloque*)malloc(sizeof(Bloque));

    l2->tipo = L2;
    
    l2->matrizBloque = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        l2->matrizBloque[i] = (int*)malloc(2 * sizeof(int));
    }

    l2->matrizBloque[0][0] = 0;
    l2->matrizBloque[0][1] = 1;
    l2->matrizBloque[1][0] = 0;
    l2->matrizBloque[1][1] = 1;
    l2->matrizBloque[2][0] = 1;   
    l2->matrizBloque[2][1] = 1;

    l2->listaRotaciones = createList();
    BloqueRotado*BloqueRotado0 = malloc(sizeof(BloqueRotado));
    //BloqueRotado0->matrizBloque = l2->matrizBloque;

    BloqueRotado0->matrizBloque = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        BloqueRotado0->matrizBloque[i] = (int*)malloc(2 * sizeof(int));
        memcpy(BloqueRotado0->matrizBloque[i], l2->matrizBloque[i], 2 * sizeof(int));
    }

    BloqueRotado0->alto = 3;
    BloqueRotado0->ancho = 2;
    pushBack(l2->listaRotaciones, BloqueRotado0);
    
    l2->ancho = 2;
    l2->alto = 3;
    crearRotacionesL2(l2->listaRotaciones);

    pushBack(listaBloques, l2);

}

void crearRotacionesL2(List*listaRotaciones) {
    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));

    bloqueRotado1->matrizBloque = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(3 * sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 1;
    bloqueRotado1->matrizBloque[0][1] = 0;
    bloqueRotado1->matrizBloque[0][2] = 0;
    bloqueRotado1->matrizBloque[1][0] = 1;
    bloqueRotado1->matrizBloque[1][1] = 1;   
    bloqueRotado1->matrizBloque[1][2] = 1;

    bloqueRotado1->alto = 2;
    bloqueRotado1->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado1);

    BloqueRotado*bloqueRotado2 = malloc(sizeof(BloqueRotado));

    bloqueRotado2->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado2->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado2->matrizBloque[0][0] = 1;
    bloqueRotado2->matrizBloque[0][1] = 1;
    bloqueRotado2->matrizBloque[1][0] = 1;
    bloqueRotado2->matrizBloque[1][1] = 0;   
    bloqueRotado2->matrizBloque[2][0] = 1;
    bloqueRotado2->matrizBloque[2][1] = 0;

    bloqueRotado2->alto = 3;
    bloqueRotado2->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado2);

    BloqueRotado*bloqueRotado3 = malloc(sizeof(BloqueRotado));

    bloqueRotado3->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado3->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    bloqueRotado3->matrizBloque [0][0] = 1;
    bloqueRotado3->matrizBloque [0][1] = 1;
    bloqueRotado3->matrizBloque [0][2] = 1;
    bloqueRotado3->matrizBloque [1][0] = 0;
    bloqueRotado3->matrizBloque [1][1] = 0;
    bloqueRotado3->matrizBloque [1][2] = 1;

    bloqueRotado3->alto = 2;
    bloqueRotado3->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado3);
}

void inicializarT(List*listaBloques){
   Bloque*t = (Bloque*)malloc(sizeof(Bloque));

    t->tipo = T;
    
    t->matrizBloque = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        t->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    t->matrizBloque[0][0] = 0;
    t->matrizBloque[0][1] = 1;
    t->matrizBloque[0][2] = 0;
    t->matrizBloque[1][0] = 1;
    t->matrizBloque[1][1] = 1;   
    t->matrizBloque[1][2] = 1;

    t->listaRotaciones = createList();
    BloqueRotado*BloqueRotado0 = malloc(sizeof(BloqueRotado));
    //BloqueRotado0->matrizBloque = t->matrizBloque;

    BloqueRotado0->matrizBloque = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        BloqueRotado0->matrizBloque[i] = (int*)malloc(3 * sizeof(int));
        memcpy(BloqueRotado0->matrizBloque[i], t->matrizBloque[i], 3 * sizeof(int));
    }

    BloqueRotado0->alto = 2;
    BloqueRotado0->ancho = 3;
    pushBack(t->listaRotaciones, BloqueRotado0);
    
    t->ancho = 3;
    t->alto = 2;
    crearRotacionesT(t->listaRotaciones);

    pushBack(listaBloques, t);    
}

void crearRotacionesT(List* listaRotaciones){

    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));
    bloqueRotado1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 1;
    bloqueRotado1->matrizBloque[0][1] = 0;
    bloqueRotado1->matrizBloque[1][0] = 1;
    bloqueRotado1->matrizBloque[1][1] = 1;
    bloqueRotado1->matrizBloque[2][0] = 1;   
    bloqueRotado1->matrizBloque[2][1] = 0;

    bloqueRotado1->alto = 3;
    bloqueRotado1->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado1);

    BloqueRotado*bloqueRotado2 = malloc(sizeof(BloqueRotado));

    bloqueRotado2->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado2->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    bloqueRotado2->matrizBloque[0][0] = 1;
    bloqueRotado2->matrizBloque[0][1] = 1;
    bloqueRotado2->matrizBloque[0][2] = 1;
    bloqueRotado2->matrizBloque[1][0] = 0;
    bloqueRotado2->matrizBloque[1][1] = 1;   
    bloqueRotado2->matrizBloque[1][2] = 0;

    bloqueRotado2->alto = 2;
    bloqueRotado2->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado2);

    BloqueRotado*bloqueRotado3 = malloc(sizeof(BloqueRotado));
    bloqueRotado3->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado3->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado3->matrizBloque[0][0] = 0;
    bloqueRotado3->matrizBloque[0][1] = 1;
    bloqueRotado3->matrizBloque[1][0] = 1;
    bloqueRotado3->matrizBloque[1][1] = 1;
    bloqueRotado3->matrizBloque[2][0] = 0;
    bloqueRotado3->matrizBloque[2][1] = 1;

    bloqueRotado3->alto = 3;
    bloqueRotado3->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado3);
}

void crearRotacionesT(List* listaRotaciones){

    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));
    bloqueRotado1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 1;
    bloqueRotado1->matrizBloque[0][1] = 0;
    bloqueRotado1->matrizBloque[1][0] = 1;
    bloqueRotado1->matrizBloque[1][1] = 1;
    bloqueRotado1->matrizBloque[2][0] = 1;   
    bloqueRotado1->matrizBloque[2][1] = 0;

    bloqueRotado1->alto = 3;
    bloqueRotado1->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado1);

    BloqueRotado*bloqueRotado2 = malloc(sizeof(BloqueRotado));

    bloqueRotado2->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        bloqueRotado2->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    bloqueRotado2->matrizBloque[0][0] = 1;
    bloqueRotado2->matrizBloque[0][1] = 1;
    bloqueRotado2->matrizBloque[0][2] = 1;
    bloqueRotado2->matrizBloque[1][0] = 0;
    bloqueRotado2->matrizBloque[1][1] = 1;   
    bloqueRotado2->matrizBloque[1][2] = 0;

    bloqueRotado2->alto = 2;
    bloqueRotado2->ancho = 3;

    pushBack(listaRotaciones, bloqueRotado2);

    BloqueRotado*bloqueRotado3 = malloc(sizeof(BloqueRotado));
    bloqueRotado3->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado3->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado3->matrizBloque[0][0] = 0;
    bloqueRotado3->matrizBloque[0][1] = 1;
    bloqueRotado3->matrizBloque[1][0] = 1;
    bloqueRotado3->matrizBloque[1][1] = 1;
    bloqueRotado3->matrizBloque[2][0] = 0;
    bloqueRotado3->matrizBloque[2][1] = 1;

    bloqueRotado3->alto = 3;
    bloqueRotado3->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado3);
}


void crearRotacionesZ(List* listaRotaciones){
    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));
    
   bloqueRotado1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 0;
    bloqueRotado1->matrizBloque[0][1] = 1;
    bloqueRotado1->matrizBloque[1][0] = 1;
    bloqueRotado1->matrizBloque[1][1] = 1;   
    bloqueRotado1->matrizBloque[2][0] = 1;
    bloqueRotado1->matrizBloque[2][1] = 0;

    bloqueRotado1->alto = 3;
    bloqueRotado1->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado1);
}

void inicializarS(List*listaBloques){
    Bloque*s = (Bloque*)malloc(sizeof(Bloque));

    s->tipo = S;
    
    s->matrizBloque = (int**)malloc(2* sizeof(int*));
    for (int i = 0; i < 2; i++) {
        s->matrizBloque[i] = (int*)malloc(3* sizeof(int));
    }

    s->matrizBloque[0][0] = 0;
    s->matrizBloque[0][1] = 1;
    s->matrizBloque[0][2] = 1;
    s->matrizBloque[1][0] = 1;
    s->matrizBloque[1][1] = 1;   
    s->matrizBloque[1][2] = 0;

    s->listaRotaciones = createList();
    BloqueRotado*BloqueRotado0 = malloc(sizeof(BloqueRotado));
    //BloqueRotado0->matrizBloque = s->matrizBloque;

    BloqueRotado0->matrizBloque = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        BloqueRotado0->matrizBloque[i] = (int*)malloc(3 * sizeof(int));
        memcpy(BloqueRotado0->matrizBloque[i], s->matrizBloque[i], 3 * sizeof(int));
    }

    BloqueRotado0->alto = 2;
    BloqueRotado0->ancho = 3;
    pushBack(s->listaRotaciones, BloqueRotado0);

    s->ancho = 3;
    s->alto = 2;
    crearRotacionesS(s->listaRotaciones);
    pushBack(listaBloques, s);    
}

void crearRotacionesS(List* listaRotaciones){
    BloqueRotado*bloqueRotado1 = malloc(sizeof(BloqueRotado));
    bloqueRotado1->matrizBloque = (int**)malloc(3* sizeof(int*));
    for (int i = 0; i < 3; i++) {
        bloqueRotado1->matrizBloque[i] = (int*)malloc(2* sizeof(int));
    }

    bloqueRotado1->matrizBloque[0][0] = 1;
    bloqueRotado1->matrizBloque[0][1] = 0;
    bloqueRotado1->matrizBloque[1][0] = 1;
    bloqueRotado1->matrizBloque[1][1] = 1;   
    bloqueRotado1->matrizBloque[2][0] = 0;
    bloqueRotado1->matrizBloque[2][1] = 1;

    bloqueRotado1->alto = 3;
    bloqueRotado1->ancho = 2;

    pushBack(listaRotaciones, bloqueRotado1);
}

