#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "bloques.h"

#define ENTER 10
#define ALTO_JUEGO 20
#define ANCHO_JUEGO 10

const char* nombresDePieza[7] = {"Cuadrado", "I", "L1", "L2", "Z", "S", "T"};

void menu(int*);
void ejecutarSeleccion(int, List*);
void funcionJugar(List*);
void inicializarBloques(List*)
void mostrarPuntajes();
void mostrarBloques(List*);
void inicializarBloques(List*);
Bloque* obtenerBloqueAleatorio(List*);
void dibujarMatrizJuego(int**);
void dibujarBloqueActual(Bloque* , int, int );
Bloque* rotarBloqueHorario(Bloque*);

int main() { 
    List*listaBloques = createList();
    inicializarBloques(listaBloques);

    int seleccion = 1;
    menu(&seleccion);

    ejecutarSeleccion(seleccion, listaBloques);


    return 0;
}

void inicializarBloques(List*listaBloques) {

    inicializarCuadrado(listaBloques);

    inicializarL1(listaBloques);

    inicializarL2(listaBloques);

    inicializarI(listaBloques);

    inicializarT(listaBloques);

    inicializarZ(listaBloques);

    inicializarS(listaBloques);

    //dou();
}


void menu(int*seleccionPtr) {
    initscr(); // Inicializar ncurses
    keypad(stdscr, TRUE); // Habilitar el uso de teclas especiales

    int opcion = 0;
    int seleccion = *seleccionPtr;

    while (opcion != ENTER) {
        clear(); // Limpiar la pantalla

        printw("MENU\n");
        printw("----------------\n");
        printw("%s Jugar\n", (seleccion == 1) ? "->" : "  ");
        printw("%s Mostrar puntajes\n", (seleccion == 2) ? "->" : "  ");
        printw("%s Mostrar bloques\n", (seleccion == 3) ? "->" : "  ");
        printw("%s Salir\n", (seleccion == 4) ? "->" : "  ");

        refresh(); // Actualizar la pantalla

        int tecla = getch(); // Leer la tecla sin esperar a Enter

        switch (tecla) {
            case KEY_UP:
                if (seleccion > 1)
                    seleccion--;
                break;
            case KEY_DOWN:
                if (seleccion < 4)
                    seleccion++;
                break;
            case ENTER:
                opcion = tecla;
                *seleccionPtr = seleccion;
                break;
            default:
                printw("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    endwin(); // Finalizar ncurses
    refresh(); // Actualizar la pantalla
}


void ejecutarSeleccion(int seleccion, List*listaBloques) {
    
    switch (seleccion) {
        case 1:
            funcionJugar();
        break;

        case 2:
            mostrarPuntajes();
        break;

        case 3:
            mostrarBloques();
        break;

        case 4:
            return;
        break;
        
        default:
        break;
    }
}

void mostrarBloques(List*listaBloques) {
    initscr();
        move(0,0);
    endwin();

    Bloque*nodoBloque = firstList(listaBloques);
    int sizeLista = sizeList(listaBloques);

    for(int i=0; i<sizeLista; i++) {
        printf("\n%s\n", nodoBloque->nombre);

        for(int j=0; j<nodoBloque->ancho; j++) {
            for(int k=0; k<nodoBloque->ancho; k++) {
                printf("%d ", nodoBloque->matrizBloque[j][k]);  
            }

            
            printf("\n");
        }

        int **matrizRotacion = firstList(nodoBloque->listaRotaciones);
        int sizeListaRotaciones = sizeList(nodoBloque->listaRotaciones);

        if(sizeListaRotaciones != 0) {
            printf("\nRotaciones:\n");
        }

        for(int l=0; l<sizeListaRotaciones; l++) {
            if(l!=0) {
                printf("\n");
                for(int m=0; m<nodoBloque->ancho; m++) {
                    for(int n=0; n<nodoBloque->ancho; n++) {
                        printf("%d ", matrizRotacion[m][n]);
                    }
                    printf("\n");
                }    
            }
            matrizRotacion = nextList(nodoBloque->listaRotaciones);
        }

        nodoBloque = nextList(listaBloques);
        printf("\n\n");
    }
    
}

Bloque* obtenerBloqueAleatorio(List* listaBloques) {
    // Obtener el tamaño de la lista de bloques
    int sizeLista = sizeList(listaBloques);

    // Generar un número aleatorio entre 0 y sizeLista-1
    int indiceAleatorio = rand() % sizeLista;

    // Obtener el bloque en el índice aleatorio de la lista
    Bloque* bloqueAleatorio = obtenerElementoPorPosicion(listaBloques, indiceAleatorio);
    
    return bloqueAleatorio;
}

void dibujarMatrizJuego(int **matrizJuego) {
    initscr();  
    int i, j;

    // Dibujar la matriz de juego en la pantalla
    for (i = 0; i < ALTO_JUEGO; i++) {
        for (j = 0; j < ANCHO_JUEGO; j++) {
            int x = j;  // Coordenada horizontal en la pantalla
            int y = i;  // Coordenada vertical en la pantalla

            // Mueve el cursor a la posición (x, y) y dibuja el carácter correspondiente
            move(y, x);

            if (matrizJuego[i][j] == 0) {
                addch('.');  // Carácter para celda vacía
            } else {
                addch('#');  // Carácter para celda ocupada por un bloque
            }
        }
    }
    endwin();
}

void dibujarBloqueActual(Bloque* bloqueActual, int posX, int posY) {
    initscr();
    int i, j;

    // Dibujar el bloque en la posición actual
    for (i = 0; i < bloqueActual->ancho; i++) {
        for (j = 0; j < bloqueActual->ancho; j++) {
            if (bloqueActual->matrizBloque[i][j] != 0) {
                int x = posX + j;
                int y = posY + i;

                // Mueve el cursor a la posición (x, y) y dibuja el bloque
                move(y, x);
                addch('#'); // Puedes usar otro carácter para representar el bloque
            }
        }
    }
    endwin();
}

Bloque*rotarBloqueHorario(Bloque*bloqueActual) {
    Bloque*bloqueNodo = nextList(bloqueActual->listaRotaciones);

    if(bloqueNodo == NULL) {
        bloqueNodo = firstList(bloqueActual->listaRotaciones);
    }

    return bloqueNodo;
}