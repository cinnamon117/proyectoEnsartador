bits 64
default rel

global convertir_a_ascii, validar_movimiento, contar_elemento, calcular_puntaje, detectar_objeto, contar_celdas_libres

; ecx = monedas
; edx = pasos
; r8d = niveles
; eax = resultado

section .text
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

.pared:    mov al, 219   ;█
           ret
.camino:   mov al, 176   ;░
           ret
.jugador:  mov al, 'P'
           ret
.moneda:   mov al, 'M'
           ret
.llave:    mov al, 'K'
           ret
.puerta:   mov al, 'D'
           ret
.salida:   mov al, 'E'
           ret

; validar movimiento
validar_movimiento:
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    mov r10d, [rcx + rax*4]

    cmp r10d, 0
    je .bloqueado

    mov eax, 1
    ret

.bloqueado:
    xor eax, eax
    ret

; contar elementos
contar_elemento:
    xor eax, eax
    xor r9d, r9d

.loop:
    cmp r9d, edx
    jge .fin

    mov r10d, [rcx + r9*4]

    cmp r10d, r8d
    jne .sig

    inc eax

.sig:
    inc r9d
    jmp .loop

.fin:
    ret



; calcular puntaje
;puntaje = (monedas * 100) + (niveles * 500) - pasos
calcular_puntaje:

    ; eax = monedas * 100
    mov eax, ecx
    imul eax, 100

    ; r9d = niveles * 500
    mov r9d, r8d
    imul r9d, 500

    add eax, r9d

    ; restar pasos
    sub eax, edx

    ret



; rcx = mapa
; edx = columnas
; r8d = fila
; r9d = columna
; eax = valor encontrado

detectar_objeto:

    mov eax, r8d
    imul eax, edx
    add eax, r9d

    mov eax, [rcx + rax*4]

    ret



; rcx = mapa
; edx = total elementos
; eax = contador
contar_celdas_libres:

    xor eax, eax
    xor r9d, r9d

.loop:
    cmp r9d, edx
    jge .fin

    mov r10d, [rcx + r9*4]

    cmp r10d, 1
    jne .sig

    inc eax

.sig:
    inc r9d
    jmp .loop

.fin:
    ret
