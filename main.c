#include <ncurses.h>
#define ENTER 10

void ejecutarSeleccion(int);

int main() {
    initscr(); // Inicializar ncurses
    keypad(stdscr, TRUE); // Habilitar el uso de teclas especiales

    int opcion = 0;
    int seleccion = 1;

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
                
                ejecutarSeleccion(seleccion);

                break;
            default:
                printw("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    endwin(); // Finalizar ncurses

    printw("Seleccionaste la opcion %d\n", seleccion);
    refresh(); // Actualizar la pantalla

    return 0;
}


void ejecutarSeleccion(int) {
    return;
}
