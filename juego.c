#include <stdio.h>
#include "juego.h"

//funcion ASM
extern char convertir_a_ascii(int valor);

//variables globales (para no complicar paso de parametros)

static int jugador_fila;
static int jugador_columna;

//--------------------------------------------

void iniciar_nivel(int *mapa){
    mapa_actual = mapa;

    //buscar jugador (igual a tus recorridos)
    for(int i=0; i<FILAS; i++){
        for(int j=0; j<COLUMNAS; j++){

            int valor = mapa_actual[i * COLUMNAS + j];

            if(valor == 2){ //jugador
                jugador_fila = i;
                jugador_columna = j;
                return;
            }
        }
    }
}

//--------------------------------------------

void mostrar_ventana(){

    int inicio_fila = jugador_fila - VENTANA/2;
    int inicio_col = jugador_columna - VENTANA/2;

    //ajustar bordes
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
}

//--------------------------------------------

void mover_jugador(char tecla){

    int nueva_fila = jugador_fila;
    int nueva_col = jugador_columna;

    if(tecla == 'w' || tecla == 'W'){
        nueva_fila--;
    }
    else if(tecla == 's' || tecla == 'S'){
        nueva_fila++;
    }
    else if(tecla == 'a' || tecla == 'A'){
        nueva_col--;
    }
    else if(tecla == 'd' || tecla == 'D'){
        nueva_col++;
    }
    else{
        return;
    }

    //indices tipo tu práctica 6
    int valor_destino = mapa_actual[nueva_fila * COLUMNAS + nueva_col];

    if(valor_destino == 0){
        //pared
        return;
    }

    //mover jugador
    mapa_actual[jugador_fila * COLUMNAS + jugador_columna] = 1;
    mapa_actual[nueva_fila * COLUMNAS + nueva_col] = 2;

    jugador_fila = nueva_fila;
    jugador_columna = nueva_col;
}