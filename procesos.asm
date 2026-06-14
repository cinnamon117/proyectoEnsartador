bits 64
default rel

global convertir_a_ascii

section .text

;ecx = valor
;al = resultado

convertir_a_ascii:

    cmp ecx, 0
    je .pared

    cmp ecx, 1
    je .camino

    cmp ecx, 2
    je .jugador

    cmp ecx, 3
    je .moneda

    cmp ecx, 4
    je .llave

    cmp ecx, 5
    je .puerta

    cmp ecx, 6
    je .salida

    mov al, '?'
    ret

.pared:
    mov al, 219
    ret

.camino:
    mov al, 176
    ret

.jugador:
    mov al, 'P'
    ret

.moneda:
    mov al, 'M'
    ret

.llave:
    mov al, 'K'
    ret

.puerta:
    mov al, 'D'
    ret

.salida:
    mov al, 'E'
    ret