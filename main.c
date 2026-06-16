#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "juego.h"
#include "mapas.h"

extern int calcular_puntaje(int monedas, int pasos, int niveles);

int main(){

    system("chcp 437 > nul");

    int nivel = 1;
    int monedas_totales = 0;
    int pasos_totales = 0;
    int niveles_completados = 0;
    int puntaje_final = 0;

    printf("INICIANDO JUEGO...\n");
    system("pause");

    while(nivel <= 3){

        if(nivel == 1)
            iniciar_nivel(&mapa_facil[0][0]);
        else if(nivel == 2)
            iniciar_nivel(&mapa_intermedio[0][0]);
        else
            iniciar_nivel(&mapa_dificil[0][0]);

        while(1){
            system("cls");

            mostrar_ventana();

            //verificar si terminó nivel
            if(nivel_completado()){
                int monedas_nivel = obtener_monedas();
                int pasos_nivel = obtener_pasos();
                int puntaje_nivel = calcular_puntaje(monedas_nivel, pasos_nivel, 1);
                printf("\n");
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
                printf("       Nivel %d completado!      \n", nivel);
                printf("                              \n");
                printf("  Monedas recolectadas: %2d/%2d     \n", monedas_nivel, obtener_total_monedas());
                printf("  Pasos realizados:     %d   \n", pasos_nivel);
                printf("  Puntaje del nivel:   %d   \n", puntaje_nivel);
                printf("                              \n");
                printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");

                monedas_totales += monedas_nivel;
                pasos_totales += pasos_nivel;
                niveles_completados++;
                system("pause");
                break;
            }

            char tecla = _getch();

            if(tecla=='q' || tecla=='Q'){
                printf("\nSeguro que quieres salir? (S/N): ");
                char c = _getch();

                if(c=='s' || c=='S') return 0;
            }

            mover_jugador(tecla);
        }

        nivel++;
    }
    puntaje_final = calcular_puntaje(monedas_totales, pasos_totales, niveles_completados);
    system("cls");
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    printf("       Juego completado!      \n");
    printf("                              \n");
    printf("  Monedas totales: ... %d     \n", monedas_totales);
    printf("  Pasos totales: ..... %d     \n", pasos_totales);
    printf("  Niveles completados: %d     \n\n", niveles_completados);
    printf("  Puntaje final: ..... %d     \n", puntaje_final);
    printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    system("pause");
    return 0;
}
