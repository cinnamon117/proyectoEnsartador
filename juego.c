#include <stdio.h>
#include "juego.h"

//ASM
extern char convertir_a_ascii(int valor);
extern int validar_movimiento(int *mapa, int columnas, int fila, int columna);
extern int contar_elemento(int *mapa, int total, int valor);

//variables globales
static int *mapa_actual;

static int jugador_fila;
static int jugador_columna;

//HUD
static int monedas_actuales = 0;
static int total_monedas = 0;

static int llaves_actuales = 0;
static int total_llaves = 0;

static int puertas_abiertas = 0;
static int puertas_totales = 0;

//----------------------------------

void iniciar_nivel(int *mapa){
    mapa_actual = mapa;

    for(int i=0; i<FILAS; i++){
        for(int j=0; j<COLUMNAS; j++){

            int valor = mapa_actual[i * COLUMNAS + j];

            if(valor == 2){
                jugador_fila = i;
                jugador_columna = j;
            }
        }
    }

    //contar con NASM
    total_monedas = contar_elemento(mapa_actual, FILAS * COLUMNAS, 3);
    total_llaves = contar_elemento(mapa_actual, FILAS * COLUMNAS, 4);
    puertas_totales = contar_elemento(mapa_actual, FILAS * COLUMNAS, 5);

    monedas_actuales = 0;
    llaves_actuales = 0;
    puertas_abiertas = 0;
}

//----------------------------------

void mostrar_ventana(){

    int inicio_fila = jugador_fila - VENTANA/2;
    int inicio_col  = jugador_columna - VENTANA/2;

    if(inicio_fila < 0) inicio_fila = 0;
    if(inicio_col < 0) inicio_col = 0;

    if(inicio_fila > FILAS - VENTANA)
        inicio_fila = FILAS - VENTANA;

    if(inicio_col > COLUMNAS - VENTANA)
        inicio_col = COLUMNAS - VENTANA;

    for(int i = inicio_fila; i < inicio_fila + VENTANA; i++){
        for(int j = inicio_col; j < inicio_col + VENTANA; j++){

            int valor = mapa_actual[i * COLUMNAS + j];
            char c = convertir_a_ascii(valor);

            putchar(c);
        }
        putchar('\n');
    }

    printf("\nMonedas: %d / %d", monedas_actuales, total_monedas);
    printf("\nLlaves: %d / %d", llaves_actuales, total_llaves);
    printf("\nPuertas: %d / %d", puertas_abiertas, puertas_totales);

    printf("\n\nWASD = mover | Q = salir\n");
}

//----------------------------------

void mover_jugador(char tecla){

    int nueva_fila = jugador_fila;
    int nueva_col  = jugador_columna;

    if(tecla=='w' || tecla=='W') nueva_fila--;
    else if(tecla=='s' || tecla=='S') nueva_fila++;
    else if(tecla=='a' || tecla=='A') nueva_col--;
    else if(tecla=='d' || tecla=='D') nueva_col++;
    else return;

    int valido = validar_movimiento(mapa_actual, COLUMNAS, nueva_fila, nueva_col);

    if(valido == 0) return;

    int valor_destino = mapa_actual[nueva_fila * COLUMNAS + nueva_col];

    //moneda
    if(valor_destino == 3){
        monedas_actuales++;
    }

    //llave
    if(valor_destino == 4){
        llaves_actuales++;
    }

    //puerta
    if(valor_destino == 5){
        if(llaves_actuales > 0){
            llaves_actuales--;
            puertas_abiertas++;
        } else {
            return;
        }
    }

    mapa_actual[jugador_fila * COLUMNAS + jugador_columna] = 1;
    mapa_actual[nueva_fila * COLUMNAS + nueva_col] = 2;

    jugador_fila = nueva_fila;
    jugador_columna = nueva_col;
}