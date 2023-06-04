#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#define ENTER 10

void menu(int*);
void ejecutarSeleccion(int, List*);
void funcionJugar();
void mostrarPuntajes();
void mostrarBloques();
void inicializarBloques(List*);

int main() { 
    List*listaBloques = createList();
    inicializarBloques(listaBloques);

    int seleccion = 1;
    menu(&seleccion);

    ejecutarSeleccion(seleccion, listaBloques);


    return 0;
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
