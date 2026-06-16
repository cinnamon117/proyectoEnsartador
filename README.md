## Descripcion general

BitQuest es un juego tipo laberinto en consola. El jugador debe recorrer tres niveles, recolectar objetos y avanzar hasta completar el juego.

Cada mapa se almacena como una matriz de enteros. La logica general del juego esta programada en C, mientras que varias operaciones importantes se realizan en NASM, como validar movimientos, contar elementos, detectar objetos y calcular el puntaje.

El proyecto fue desarrollado para reforzar conceptos como:

- Uso de matrices.
- Recorrido de memoria.
- Paso de parametros entre C y NASM.
- Validacion de movimientos.
- Uso de funciones externas.
- Programacion modular.
- Compilacion hibrida con NASM y GCC.


## Caracteristicas principales

- Juego funcional en consola.
- Programacion hibrida usando C y NASM de 64 bits.
- Tres niveles jugables.
- Mapas de 60 x 60.
- Ventana visible dinamica de 20 x 20.
- Movimiento con teclas WASD.
- Sistema de monedas.
- Sistema de llave y puerta.
- Salida para completar cada nivel.
- Resumen al terminar cada nivel.
- Resumen final al completar el juego.
- Puntaje calculado mediante una funcion.

## Representacion del mapa

Internamente los mapas se representan con matrices de enteros:

int mapa[60][60];

Cada valor numerico representa un elemento dentro del juego:

| Valor | Elemento |
|-------|----------|
|   0   |  Pared   |
|   1   |  Camino  |
|   2   |  Jugador |
|   3   |  Moneda  |
|   4   |  Llave   |
|   5   |  Puerta  |
|   6   |  Salida  |

Durante la impresion del mapa, estos valores son convertidos a caracteres visibles en consola mediante una funcion escrita en NASM.


## Controles

| Tecla |          Accion          |
|-------|--------------------------|
|   W   | Mover hacia arriba       |
|   A   | Mover hacia la izquierda |
|   S   | Mover hacia abajo        |
|   D   | Mover hacia la derecha   |
|   Q   | Salir del juego          |

No es necesario presionar Enter despues de cada movimiento.

Al presionar `Q`, el programa solicita confirmacion antes de cerrar el juego.


### Objetivo del juego

El objetivo de BitQuest es completar los tres niveles disponibles.

En cada nivel, el jugador debe:

1. Explorar el mapa.
2. Recolectar monedas.
3. Encontrar la llave.
4. Abrir la puerta.
5. Llegar a la salida.

No es obligatorio recolectar todas las monedas para terminar un nivel, pero recolectarlas ayuda a obtener un mejor puntaje.

### Como iniciar el juego

1. Compilar el proyecto usando `build.bat` o los comandos manuales.
2. Ejecutar el archivo `.exe` generado.
3. El juego iniciara automaticamente en el nivel 1.


### Como jugar

El jugador aparece representado con el caracter: `P`

El mapa completo mide 60 x 60, pero en pantalla solo se muestra una seccion de 20 x 20. Esta ventana visible se mueve conforme el jugador avanza.

Durante el recorrido pueden aparecer los siguientes elementos:

P = Jugador
M = Moneda
K = Llave
D = Puerta
E = Salida

Las paredes y caminos se muestran con caracteres ASCII para mejorar la visualizacion del laberinto.

### Reglas del juego

- El jugador no puede atravesar paredes.
- El jugador puede caminar sobre caminos libres.
- Al tocar una moneda, la moneda se recolecta automaticamente.
- Al tocar una llave, la llave queda disponible para abrir una puerta.
- Las puertas solo pueden cruzarse si el jugador tiene una llave.
- Al cruzar una puerta, se consume una llave.
- Al llegar a la salida, el nivel termina.
- Al completar un nivel, se muestra un resumen.
- Al completar los tres niveles, se muestra el resumen final.

---

### Informacion durante la partida

Durante el juego se muestra informacion del nivel actual:

Monedas: 3 / 8
Llaves:  1 / 1
Puertas: 0 / 1
Pasos:   45

WASD = mover | Q = salir

Esta informacion permite conocer el progreso del jugador dentro del nivel.

## Estructura del proyecto

BitQuest/
|
|-- main.c
|-- juego.c
|-- juego.h
|-- mapas.c
|-- mapas.h
|-- procesos.asm
|-- build.bat
|-- README.md

## Descripcion de archivos

### `main.c`

Contiene el flujo principal del programa.

Se encarga de:
- Iniciar la configuracion del juego.
- Cargar los niveles.
- Leer las teclas del jugador.
- Administrar el cambio entre niveles.
- Mostrar el resumen por nivel.
- Mostrar el resumen final.

### `juego.c`

Contiene la logica principal del juego.

Incluye:
- Inicializacion de niveles.
- Busqueda de la posicion del jugador.
- Movimiento del jugador.
- Manejo de monedas.
- Manejo de llaves.
- Manejo de puertas.
- Deteccion de salida.
- Impresion de la ventana visible 20 x 20.
- Contadores de avance del jugador.

### `juego.h`

Contiene constantes, prototipos y declaraciones necesarias para comunicar `main.c` con `juego.c`.

### `mapas.c`

Contiene los tres mapas del juego:
mapa_facil
mapa_intermedio
mapa_dificil

Cada mapa esta declarado como una matriz de 60 x 60.

### `mapas.h`

Declara los mapas como variables externas para que puedan utilizarse desde otros archivos.

### `procesos.asm`

Contiene las rutinas implementadas en NASM.

Estas funciones realizan operaciones importantes del programa como:
- Conversion visual de valores.
- Validacion de movimiento.
- Conteo de elementos.
- Deteccion de objetos.
- Conteo de celdas libres.
- Calculo del puntaje.

### `build.bat`

Archivo por lotes utilizado para compilar automaticamente el proyecto en Windows.

El archivo compila primero los `.asm` con NASM y despues enlaza los `.c` con los `.obj` usando GCC.


## Sistema de puntaje

El puntaje se calcula con la siguiente formula:
puntaje = (monedas * 100) + (niveles * 500) - pasos

El sistema recompensa la recoleccion de monedas y la finalizacion de niveles, pero tambien toma en cuenta la cantidad de pasos realizados.


## Resumen por nivel

Al completar un nivel, el programa muestra:

- Numero del nivel completado.
- Monedas recolectadas.
- Total de monedas del nivel.
- Pasos realizados.
- Puntaje del nivel.

Ejemplo:
============================
|    Nivel 1 completado!   |
|                          |
| Monedas recolectadas: 6/8|
| Pasos realizados: 120    |
| Puntaje del nivel: 980   |
============================

## Resumen final

Al completar los tres niveles, el programa muestra:

- Monedas totales recolectadas.
- Pasos totales.
- Niveles completados.
- Puntaje final.

Ejemplo:
=============================
|      Juego completado!    |
|                           |
| Monedas totales: 26       |
| Pasos totales: 410        |
| Niveles completados: 3    |
| Puntaje final: 3690       |
=============================

## Compilacion

### Requisitos

Para compilar el proyecto se necesita:

- NASM.
- GCC de 64 bits.
- Windows.
- MinGW-w64 o entorno equivalente.

---

### Compilacion manual

Desde la carpeta del proyecto, ejecutar:

```bash
nasm -f win64 procesos.asm -o procesos.obj
gcc main.c juego.c mapas.c procesos.obj -o BitQuest.exe
```
### Compilacion con `build.bat`

El proyecto incluye un archivo `build.bat` para compilar automaticamente.

Para usarlo:

1. Colocar todos los archivos fuente en la misma carpeta.
2. Ejecutar `build.bat`.
3. El script compilara los archivos `.asm`.
4. Despues compilara los archivos `.c`.
5. Finalmente generara el ejecutable.

## Ejecucion

Despues de compilar, ejecutar:

```bash
BitQuest.exe
```

Si se usa `build.bat`, el archivo puede ejecutar el programa automaticamente despues de compilar.


## Ejemplo de salida

Durante el juego:

Monedas: 3 / 8
Llaves: 1 / 1
Puertas: 0 / 1
Pasos: 45

WASD = mover | Q = salir


Al completar un nivel:
============================
|    Nivel 1 completado!   |
|                          |
| Monedas recolectadas: 6/8|
| Pasos realizados: 120    |
| Puntaje del nivel: 980   |
============================

Al completar el juego:
=============================
|      Juego completado!    |
|                           |
| Monedas totales: 26       |
| Pasos totales: 410        |
| Niveles completados: 3    |
| Puntaje final: 3690       |
=============================

## Estado del proyecto

Proyecto funcional y completo.

El programa implementa:

- Juego en consola.
- Tres niveles.
- Matrices de 60 x 60.
- Ventana visible de 20 x 20.
- Movimiento del jugador.
- Colisiones con paredes.
- Llave, puerta y salida.
- Sistema de monedas.
- Funciones en NASM.
- Puntaje calculado en NASM.
- Resumen por nivel.
- Resumen final.
