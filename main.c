#include <stdio.h>
#include <stdlib.h>
#include "mapas.h"
#include "juego.h"

//pon aqui solo UN mapa para probar
extern int mapa_facil[60][60];

int main(){

    system("chcp 437 > nul");

    iniciar_nivel(&mapa_facil[0][0]);

    while(1){
        system("cls");

        mostrar_ventana();

        printf("\nWASD para mover, Q para salir\n");

        char tecla;
        scanf(" %c", &tecla);

        if(tecla == 'q' || tecla == 'Q'){
            break;
        }

        mover_jugador(tecla);
    }

    return 0;
}