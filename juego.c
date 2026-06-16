#include <stdio.h>
#include "juego.h"

//ASM
extern char convertir_a_ascii(int valor);

extern int validar_movimiento(int *mapa, int columnas, int fila, int columna);
extern int contar_elemento(int *mapa, int total, int valor);
extern int calcular_puntaje(int monedas, int pasos, int niveles);
extern int detectar_objeto(int *mapa, int columnas, int fila, int columna);
extern int contar_celdas_libres(int *mapa, int total);

//variables globales
static int *mapa_actual;

static int jugador_fila;
static int jugador_columna;
static int pasos = 0;

static int nivel_terminado = 0;

//Resumen del nivel
static int monedas_actuales = 0;
static int total_monedas = 0;

static int llaves_actuales = 0;
static int total_llaves = 0;

static int puertas_abiertas = 0;
static int puertas_totales = 0;

static int celdas_libres = 0;

//Totales del juego
int monedas_totales = 0;
int pasos_totales = 0;
int niveles_completados = 0;

void iniciar_nivel(int *mapa){

    mapa_actual = mapa;
    nivel_terminado = 0;

    pasos = 0; //RESET PASOS

    for(int i=0; i<FILAS; i++){
        for(int j=0; j<COLUMNAS; j++){

            //USO DE ASM
            int valor = detectar_objeto(mapa_actual, COLUMNAS, i, j);

            if(valor == 2){
                jugador_fila = i;
                jugador_columna = j;
            }
        }
    }

    //contadores con NASM
    total_monedas = contar_elemento(mapa_actual, FILAS * COLUMNAS, 3);
    total_llaves = contar_elemento(mapa_actual, FILAS * COLUMNAS, 4);
    puertas_totales = contar_elemento(mapa_actual, FILAS * COLUMNAS, 5);

    //contar celdas libres
    celdas_libres = contar_celdas_libres(mapa_actual, FILAS * COLUMNAS);

    monedas_actuales = 0;
    llaves_actuales = 0;
    puertas_abiertas = 0;
}

int nivel_completado(){
    return nivel_terminado;
}

//GETTERS
int obtener_monedas(){
    return monedas_actuales;
}

int obtener_pasos(){
    return pasos;
}

int obtener_total_monedas(){
    return total_monedas;
}

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

            //USO DE ASM
            int valor = detectar_objeto(mapa_actual, COLUMNAS, i, j);

            char c = convertir_a_ascii(valor);
            putchar(c);
        }
        putchar('\n');
    }

    printf("\nMonedas: %d / %d", monedas_actuales, total_monedas);
    printf("\nLlaves: %d / %d", llaves_actuales, total_llaves);
    printf("\nPuertas: %d / %d", puertas_abiertas, puertas_totales);

    printf("\nPasos: %d", pasos);
    printf("\nCeldas libres: %d", celdas_libres);

    printf("\n\nWASD = mover | Q = salir\n");
}

void mover_jugador(char tecla){

    int nueva_fila = jugador_fila;
    int nueva_col  = jugador_columna;

    if(tecla=='w' || tecla=='W') nueva_fila--;
    else if(tecla=='s' || tecla=='S') nueva_fila++;
    else if(tecla=='a' || tecla=='A') nueva_col--;
    else if(tecla=='d' || tecla=='D') nueva_col++;
    else return;

    int valido = validar_movimiento(mapa_actual, COLUMNAS, nueva_fila, nueva_col);

    if(valido == 0){
        pasos++; //cuenta intento fallido
        return;
    }

    //USO DE ASM
    int valor_destino = detectar_objeto(mapa_actual, COLUMNAS, nueva_fila, nueva_col);

    pasos++; //movimiento válido también cuenta

    //salida
    if(valor_destino == 6){
        nivel_terminado = 1;
    }

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
