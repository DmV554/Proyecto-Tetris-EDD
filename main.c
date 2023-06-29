#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "bloques.h"
#include "treemap.h"
#include <unistd.h>
#include <stdbool.h>

#define ENTER 10
#define ALTO_JUEGO 20
int ANCHO_JUEGO = 10;

const char* nombresDePieza[7] = {"Cuadrado", "L1", "L2", "I", "T", "Z", "S"};

typedef struct{
    char nombre[21];
    size_t puntaje;
    char dificultad[10];
}Jugador;

void menu(int*);
void ejecutarSeleccion(int, List*, TreeMap*);
void funcionJugar(List*, TreeMap*);
void inicializarBloques(List*);
void mostrarPuntajes(TreeMap*);
void mostrarBloques(List*);
void inicializarBloques(List*);
Bloque* obtenerBloqueAleatorio(List*);
void dibujarMatrizJuego(int**,int,int);
void dibujarBloqueActual(Bloque* , int, int );
void rotarBloqueHorario(Bloque*);
int verificarColisiones(Bloque*, int, int, int **);
void fijarBloqueEnMatriz(Bloque*, int, int , int **);
int verificarFinJuego(int**);
void imprimirTetris(int);
void eliminarLineasCompletas(int**,size_t*,int*);
void asignarJugador(size_t, TreeMap*, char*);
void selectorDificultad(int*, char*);
void imprimirPuntajes(char*, TreeMap*);


int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 > *(int*)key2) return 1;
    return 0;
}


int main() { 
    TreeMap* Jugadores = createTreeMap(lower_than_int);
    List*listaBloques = createList();
    inicializarBloques(listaBloques);
    
    while(true) {
        int seleccion = 1;
        menu(&seleccion);
        ejecutarSeleccion(seleccion, listaBloques, Jugadores);
    } 
    
    free(listaBloques);
    free(Jugadores);
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

void imprimirPuntajes(char * nivel, TreeMap * Jugadores){
    clear();
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    char mensajeTS[20];
    strcpy(mensajeTS, "TOP SCORES");

    int posX = (maxCols - strlen(mensajeTS)) / 2;


    mvprintw(0,posX,"%s %s\n", mensajeTS, nivel);
    refresh();
    int cont = 1;
    
    Pair* pairJugador = firstTreeMap(Jugadores);
    Jugador * jugador = pairJugador->value;
    int i = 5;
    
    while(jugador != NULL || cont == 10){
        if(strcmp(jugador->dificultad, nivel) == 0){
            move(i,65);
            printw("%2d. %-20s %d\n", cont, jugador->nombre, jugador->puntaje);
            cont++;
            i++;
            refresh();
        }     
        pairJugador = nextTreeMap(Jugadores);
        if(pairJugador == NULL) break;
        jugador = pairJugador->value;
    }
}

void mostrarPuntajes(TreeMap* Jugadores) {

    initscr(); 
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE); // Habilitar el uso de teclas especiales
    curs_set(0);

    clear();
    
    Pair* pairJugador = firstTreeMap(Jugadores);
    
    if(pairJugador==NULL){
        move(0,0);
        move(0,65);
        printw("No hay jugadores registrados\n");
        refresh();
        getch();
        endwin();
        return;
    }
    
    int opcion = 0;
    int seleccion = 1;
    char nivel[10];

    while (opcion != ENTER) {
        clear();

        printw("Elige que puntajes deseas ver segun la dificultad:\n");
        printw("---------------------------------------------------\n");
        printw("            %s Facil \n", (seleccion == 1) ? "->" : "  ");
        printw("            %s Normal \n", (seleccion == 2) ? "->" : "  ");
        printw("            %s Dificil \n", (seleccion == 3) ? "->" : "  ");

        refresh();

        int tecla = getch(); 

        switch (tecla) {
            case KEY_UP:
                if (seleccion > 1)
                    seleccion--;
                break;
            case KEY_DOWN:
                if (seleccion < 3)
                    seleccion++;
                break;
            case ENTER:
                opcion = tecla;
                break;
            default:
                printw("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    clear(); 

    switch (seleccion) {
        case 1:
            strcpy(nivel, "FACIL");
            imprimirPuntajes(nivel, Jugadores);
            break;
        case 2:
            strcpy(nivel, "NORMAL");
            imprimirPuntajes(nivel, Jugadores);
            break;
        case 3:
            strcpy(nivel, "DIFICIL");
            imprimirPuntajes(nivel, Jugadores);
            break;
        default:
            printw("Opcion invalida. Intente de nuevo.\n");
            break;
    }

    
    getch();

    endwin();
}


void menu(int*seleccionPtr) {
    initscr(); // Inicializar ncurses
    curs_set(0);
    keypad(stdscr, TRUE); // Habilitar el uso de teclas especiales

    int opcion = 0;
    int seleccion = *seleccionPtr;

    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    int posY = maxRows / 2;
    int posX = maxCols / 2;

    while (opcion != ENTER) {
        clear(); // Limpiar la pantalla

        imprimirTetris(posX-20);
        mvprintw(posY+5,posX-10,"%s Jugar\n", (seleccion == 1) ? "->" : "  ");
        mvprintw(posY+6,posX-10,"%s Mostrar puntajes\n", (seleccion == 2) ? "->" : "  ");
        mvprintw(posY+7,posX-10,"%s Mostrar bloques\n", (seleccion == 3) ? "->" : "  ");
        mvprintw(posY+8,posX-10,"%s Instrucciones\n", (seleccion == 4) ? "->" : "  ");
        mvprintw(posY+9,posX-10,"%s Salir\n", (seleccion == 5) ? "->" : "  ");

        refresh(); // Actualizar la pantalla

        int tecla = getch(); // Leer la tecla sin esperar a Enter

        switch (tecla) {
            case KEY_UP:
                if (seleccion > 1)
                    seleccion--;
                break;
            case KEY_DOWN:
                if (seleccion < 5)
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

    refresh(); // Actualizar la pantalla
    endwin(); // Finalizar ncurses
}

void imprimirTetris(int posX) {           
    start_color();            
    init_pair(1, COLOR_RED, COLOR_BLACK); 
    attron(COLOR_PAIR(1));     // Activar el par de colores definido

    FILE* archivo = fopen("titulo_tetris.txt", "r");
    
    char linea[250];
    int i = 4;
    while (fgets(linea, 250, archivo) != NULL) {
        mvprintw(i, posX, "%s", linea);
        i++;
    }

    attroff(COLOR_PAIR(1));    // Desactivar el par de colores
    refresh();                 // Actualizar la pantalla

    fclose(archivo);         

}


void ejecutarSeleccion(int seleccion, List*listaBloques, TreeMap * Jugadores) { 
    switch (seleccion) {
        case 1:
            funcionJugar(listaBloques, Jugadores);
        break;

        case 2:
            mostrarPuntajes(Jugadores);
        break;

        case 3:
            mostrarBloques(listaBloques);
        break;

        case 4:
            //mostrarInstrucciones();
        break;

        case 5:
            exit(0);
        break;

        default:
        break;
    }
}

void mostrarBloques(List*listaBloques) {
    Bloque*nodoBloque = firstList(listaBloques);
    int sizeLista = sizeList(listaBloques);

    for(int i=0; i<sizeLista; i++) {
        printf("\n%s\n", nombresDePieza[i]);

        for(int j=0; j<nodoBloque->alto; j++) {
            for(int k=0; k<nodoBloque->ancho; k++) {
                printf("%d ", nodoBloque->matrizBloque[j][k]);  
            }
            printf("\n");
        }

        BloqueRotado* bloqueR = firstList(nodoBloque->listaRotaciones);
        int sizeListaRotaciones = sizeList(nodoBloque->listaRotaciones);

        if(bloqueR != NULL) {
            if(sizeListaRotaciones != 0) {
                printf("\nRotaciones:\n");
            }

             for(int l=0; l<sizeListaRotaciones; l++) {
                if(l!=0) {
                    printf("\n");
                    for(int m=0; m<bloqueR->alto; m++) {
                        for(int n=0; n<bloqueR->ancho; n++) {
                            printf("%d ", bloqueR->matrizBloque[m][n]);
                        }
                        printf("\n");
                    }    
                }
                bloqueR = nextList(nodoBloque->listaRotaciones);
            }
        }
        nodoBloque = nextList(listaBloques);
        printf("\n\n");
    }

    printf("\nPresione cualquier tecla para continuar...");
    getchar();
}

Bloque* obtenerBloqueAleatorio(List* listaBloques) {
    // Obtener el tamaño de la lista de bloques
    int sizeLista = sizeList(listaBloques);

    // Generar un número aleatorio entre 0 y sizeLista-1
    srand(time(NULL));
    int indiceAleatorio = rand() % sizeLista;

    // Obtener el bloque en el índice aleatorio de la lista
    Bloque* bloqueAleatorio = obtenerElementoPorPosicion(listaBloques, indiceAleatorio);
    
    return bloqueAleatorio;
}

void dibujarMatrizJuego(int **matrizJuego, int puntaje,int nivel) { 
    int i, j, x, y;

    int posX, posY;
    
    // Dibujar la matriz de juego en la pantalla
    for (i = 0; i < ALTO_JUEGO; i++) {
        for (j = 0; j < ANCHO_JUEGO; j++) {
             x = j;  // Coordenada horizontal en la pantalla
             y = i;  // Coordenada vertical en la pantalla

            // Mueve el cursor a la posición (x, y) y dibuja el carácter correspondiente
            move(y, x);

            if (matrizJuego[i][j] == 0) {
                addch('.');  // Carácter para celda vacía
            } else {
                addch('*');  // Carácter para celda ocupada por un bloque
            }
        }
    }


    posX = ANCHO_JUEGO +50;
    posY = 0;

    move(posY, posX);

    printw("Puntaje %d", puntaje);

    move(posY+1, posX);

    printw("Nivel %d", nivel);

}

void dibujarBloqueActual(Bloque* bloqueActual, int posX, int posY) {
    int i, j;

    // Dibujar el bloque en la posición actual
    for (i = 0; i < bloqueActual->alto; i++) {
        for (j = 0; j < bloqueActual->ancho; j++) {
            if (bloqueActual->matrizBloque[i][j] != 0) {
                int x = posX + j;
                int y = posY + i;

                // Mueve el cursor a la posición (x, y) y dibuja el bloque
                move(y, x);
                addch('*'); // Puedes usar otro carácter para representar el bloque
            }
        }
    }
    
}

void rotarBloqueHorario(Bloque*bloqueActual) {
    BloqueRotado*BloqueRotado = nextList(bloqueActual->listaRotaciones);

    if(BloqueRotado == NULL) {
        BloqueRotado = firstList(bloqueActual->listaRotaciones);
    }

    if(BloqueRotado == NULL) {
        return;
    }

    bloqueActual->matrizBloque = BloqueRotado->matrizBloque;
    bloqueActual->alto = BloqueRotado->alto;
    bloqueActual->ancho = BloqueRotado->ancho;
}

int verificarColisiones(Bloque* bloqueActual, int posX, int posY, int **matrizJuego) {
    int i, j;

    // Verificar colisión con los límites del tablero
    for (i = 0; i < bloqueActual->alto; i++) {
        for (j = 0; j < bloqueActual->ancho; j++) {
            if (bloqueActual->matrizBloque[i][j] != 0) {
                int x = posX + j;
                int y = posY + i;

                if (x < 0 || x >= ANCHO_JUEGO || y >= ALTO_JUEGO) {
                    return 1;  // Colisión con los límites del tablero
                }

                if (y >= 0 && matrizJuego[y][x] != 0) {
                    return 1;  // Colisión con otro bloque fijo en el tablero
                }
            }
        }
    }

    return 0;  // No hay colisión
}

void fijarBloqueEnMatriz(Bloque* bloqueActual, int posX, int posY, int **matrizJuego) {
    int i, j;

    // Colocar el bloque en la matriz de juego en la posición indicada
    for (i = 0; i < bloqueActual->alto; i++) {
        for (j = 0; j < bloqueActual->ancho; j++) {
            if (bloqueActual->matrizBloque[i][j] != 0) {
                int x = posX + j;
                int y = posY + i;

                // Verificar si la posición está dentro de los límites de la matriz de juego
                if (x >= 0 && x < ANCHO_JUEGO && y >= 0 && y < ALTO_JUEGO) {
                    matrizJuego[y][x] = 1;  // Marcar la celda como ocupada por el bloque
                }
            }
        }
    }
}

int verificarFinJuego(int** matrizJuego) { 
    // Verificar si alguna celda de la primera fila está ocupada
    for (int j = 0; j < ALTO_JUEGO; j++) {
        if (matrizJuego[0][j] != 0) {
            return 1; // Fin de juego alcanzado
        }
    }

    return 0; // El juego continúa
}

void funcionJugar(List* listaBloques, TreeMap* Jugadores) {  // Inicializar ncurses
    initscr(); 
    curs_set(0);
    keypad(stdscr, TRUE);  
    nodelay(stdscr, TRUE);

    char *dificultad = (char*) malloc(sizeof(char) * 10);
    
    selectorDificultad(&ANCHO_JUEGO, dificultad);

    int gameover = 0;
    size_t puntaje = 0;
    int nivel = 1;
    Bloque* bloqueActual = obtenerBloqueAleatorio(listaBloques);
    Bloque* bloqueAnterior = NULL;

    int**matrizJuego = (int**)calloc(ALTO_JUEGO, sizeof(int*));
    for (int i = 0; i < ALTO_JUEGO; i++) {
        matrizJuego[i] = (int*)calloc(ANCHO_JUEGO, sizeof(int));
    }

    // Posición inicial del bloque actual
    int posX = ANCHO_JUEGO / 2;
    int posY = 0;
 
    unsigned long long numBajada = 0;
    unsigned long long limiteBajada = 100;
    struct timespec tiempoPausa = {0, 10000000};
    bool espacio = false;

    while (!gameover) {
        clear(); 

        dibujarMatrizJuego(matrizJuego,puntaje,nivel);
        dibujarBloqueActual(bloqueActual, posX, posY);
           
        refresh();  // Actualizar pantalla

        nanosleep(&tiempoPausa, NULL);
        int tecla = getch();  
        
        switch (tecla) {
            case KEY_LEFT:
                // Mover el bloque actual hacia la izquierda
                posX--;

                break;
            case KEY_RIGHT:
                // Mover el bloque actual hacia la derecha
                posX++;

                break;
            case KEY_UP:
                // Rotar el bloque actual en sentido horario
                rotarBloqueHorario(bloqueActual);
                break;
            case KEY_DOWN:
                posY++;
                break;
            
            case ' ':
                tiempoPausa.tv_nsec = 0;
                tiempoPausa.tv_sec = 0;
                espacio = true;

                break;
                
            case 'q':
                gameover = 1;
                break;
            default:
                break;
        }

        if(espacio) {
            posY++;
        } else {
            if(numBajada == limiteBajada - (nivel*2) ) {
                posY++;
                numBajada = 0;
            } else {
                numBajada++;
            }
        }
        
        if (verificarColisiones(bloqueActual, posX, posY, matrizJuego)) {
            if (posX < 0) {
                posX++;
            } else if (posX + bloqueActual->ancho > ANCHO_JUEGO) {
                posX--;
            } else if(tecla == KEY_LEFT){
                posX++;
            } else if(tecla == KEY_RIGHT) {
                posX--;
            } else {
                tiempoPausa.tv_nsec = 10000000;
                tiempoPausa.tv_sec = 0;
                posY--;
                fijarBloqueEnMatriz(bloqueActual, posX, posY, matrizJuego);
                eliminarLineasCompletas(matrizJuego,&puntaje,&nivel);

                Bloque* nuevoBloqueActual = obtenerBloqueAleatorio(listaBloques);

                // Verificar si el bloque actual es igual al bloque anterior
                while (bloqueAnterior != NULL && bloqueAnterior == nuevoBloqueActual) {
                    nuevoBloqueActual = obtenerBloqueAleatorio(listaBloques);
                }

                // Asignar el nuevo bloque actual
                bloqueActual = nuevoBloqueActual;
                
                // Actualizar el bloque anterior
                bloqueAnterior = bloqueActual;

                posX = ANCHO_JUEGO / 2;
                posY = 0;

                espacio = false;
            }
        }


        if (verificarFinJuego(matrizJuego)) {
                gameover = 1;
            }
    }

    asignarJugador(puntaje, Jugadores, dificultad);
    
    endwin();

    for (int i = 0; i < ALTO_JUEGO; i++) {
        free(matrizJuego[i]);
    }
    
    free(matrizJuego);
    free(dificultad);
    
}



void eliminarLineasCompletas(int**matrizJuego,size_t*ptrPuntaje,int *ptrNivel) {
    int i, j, k;
    int lineaCompleta = 1;

    size_t puntaje = *ptrPuntaje;
    int nivel = *ptrNivel;

    // Recorrer la matriz de juego desde abajo hacia arriba
    for (i = ALTO_JUEGO - 1; i >= 0; i--) {
        lineaCompleta = 1;

        // Verificar si la línea actual está completa
        for (j = 0; j < ANCHO_JUEGO; j++) {
            if (matrizJuego[i][j] == 0) {
                lineaCompleta = 0;
                break;
            }
        }

        // Si la línea está completa, eliminarla
        if (lineaCompleta) {

            // Aumentar el puntaje
            puntaje += 100;

            if(puntaje%300==0){
                nivel++;
            }

            // Mover todas las líneas superiores una posición hacia abajo
            for (k = i; k > 0; k--) {
                for (j = 0; j < ANCHO_JUEGO; j++) {
                    matrizJuego[k][j] = matrizJuego[k - 1][j];
                }
            }

            // Limpiar la primera línea
            for (j = 0; j < ANCHO_JUEGO; j++) {
                matrizJuego[0][j] = 0;
            }

            i++;  // Revisar la misma línea nuevamente
        }
    }

    *ptrPuntaje = puntaje;
    *ptrNivel = nivel;
}

void asignarJugador(size_t puntaje, TreeMap * Jugadores, char * dificultad){
    noecho();
    nodelay(stdscr, FALSE); 
    Jugador *jugador = (Jugador*) malloc(sizeof(Jugador));
 
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
 
    clear();
    move(0,0);
    move(15,65);

    char mensajeGO[12] = "GAME OVER\n\n";

    int posY = maxRows / 2;
    int posX = (maxCols - strlen(mensajeGO)) / 2;
    mvprintw(posY, posX, "%s", mensajeGO);

    printw("SU PUNTAJE ES DE : %zd\n\n\n", puntaje);

    printw("Presione enter para continuar...");
    refresh();
    
    while(true) {
        if(getch() == ENTER) break;
    }

    echo();

    clear();
    char mensajeNU[39] = "INGRESE SU NOMBRE DE USUARIO:\n\n\n";

    posX = (maxCols - strlen(mensajeNU)) / 2;
    mvprintw(posY, posX, "%s", mensajeNU);
    refresh();

    getstr(jugador->nombre);
    if(strcmp(jugador->nombre, "") == 0){
        strcpy(jugador->nombre, "Desconocido");
    }

    jugador->puntaje = puntaje;
    strcpy(jugador->dificultad, dificultad);

    insertTreeMap(Jugadores, &jugador->puntaje, jugador);
    clear();
}

void selectorDificultad(int* ancho, char *dificultad){
    curs_set(0);
    keypad(stdscr, TRUE); // Habilitar el uso de teclas especiales

    int opcion = 0;
    int seleccion = 1;

    while (opcion != ENTER) {
        clear(); // Limpiar la pantalla

        printw("Elige la dificultad con la que deseas jugar:\n");
        printw("--------------------------------------\n");
        printw("            %s Facil (15x20)\n", (seleccion == 1) ? "->" : "  ");
        printw("            %s Normal (10x20)\n", (seleccion == 2) ? "->" : "  ");
        printw("            %s Dificil (8x20)\n", (seleccion == 3) ? "->" : "  ");

        refresh(); // Actualizar la pantalla

        int tecla = getch(); // Leer la tecla sin esperar a Enter

        switch (tecla) {
            case KEY_UP:
                if (seleccion > 1)
                    seleccion--;
                break;
            case KEY_DOWN:
                if (seleccion < 3)
                    seleccion++;
                break;
            case ENTER:
                opcion = tecla;
                break;
            default:
                printw("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    switch (seleccion) {
        case 1:
            *ancho = 15;
            strcpy(dificultad, "FACIL");
            break;
        case 2:
            *ancho = 10;
            strcpy(dificultad, "NORMAL");
            break;
        case 3:
            *ancho = 8;
            strcpy(dificultad, "DIFICIL");
            break;
        default:
            printw("Opcion invalida. Intente de nuevo.\n");
            break;
    }

    refresh(); // Actualizar la pantalla

}