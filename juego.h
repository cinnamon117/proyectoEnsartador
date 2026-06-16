#ifndef JUEGO_H
#define JUEGO_H

#define FILAS 60
#define COLUMNAS 60
#define VENTANA 20

void iniciar_nivel(int *mapa);
void mostrar_ventana();
void mover_jugador(char tecla);
int nivel_completado();
int obtener_monedas();
int obtener_pasos();
int obtener_total_monedas();

#endif
