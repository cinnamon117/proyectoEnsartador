#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "juego.h"
#include "mapas.h"

int main(){

    system("chcp 437 > nul");

    iniciar_nivel(&mapa_facil[0][0]);

    while(1){
        system("cls");

        mostrar_ventana();

        char tecla = _getch();

        if(tecla=='q' || tecla=='Q'){
            printf("\nSeguro que quieres salir? (S/N): ");
            char c = _getch();

            if(c=='s' || c=='S') break;
        }

        mover_jugador(tecla);
    }

    return 0;
}