bits 64
default rel 

global.....

;recibimos en la matriz los numeros 0,1,2,3,4,5,6
; # = 0 Pared.
; . = 1 Camino libre.
; P = 2 Jugador.
; M = 3 Moneda.
; K = 4 Llave.
; D = 5 Puerta.
; E = 6 Salida.
section .text
;El mapa se genera como el programa de pixel art
generar_mapa:
    ;verificamos que no este vacía
    cmp r8d, 0
    jle .salida_vacia
    cmp r9d, 0
    jle .salida_vacia

    ;contador de filas
    mov r10d, r8d
    .fila_loop:
    ;contador para las columnas
    mov r11d, r9d

    .columnas_loop:
    mov eax, [rcx]  ;valor actual de la matriz

    cmp eax, 0
    je .valor_0
    cmp eax, 1
    je .valor_1
    cmp eax, 2
    je .valor_2
    cmp eax, 3
    je .valor_3
    cmp eax, 4
    je .valor_4
    cmp eax, 5
    je .valor_5

    mov al, 219
    jmp .escribir_bloque

    .valor_0:
    mov al, 32
    jmp .escribir_bloque
    .valor_1:
    mov al, 176
    jmp .escribir_bloque
    .valor_2:
    mov al, 177
    jmp .escribir_bloque
    .valor_3:
    mov al, 178
    jmp .escribir_bloque 

    .escribir_bloque:
    mov [rdx], al 
    mov [rdx + 1], al 

    ;avanzar salida y matriz
    add rcx, 4 ;matriz
    add rdx, 2 ;vector de salida

    ;siguiente columna
    dec r11d
    jnz .columnas_loop

    mov byte [rdx], 10
    inc rdx

    dec r10d
    jnz .fila_loop

    mov byte [rdx], 0
    ret 

    .salida_vacia:
    mov byte [rdx], 0
    ret 