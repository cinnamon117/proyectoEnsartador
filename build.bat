@echo off
setlocal EnableDelayedExpansion

:: 
Movernos SIEMPRE a la carpeta donde está el .bat
cd /d "%~dp0"

:: nombre exe
for %%I in (.) do set "CARPETA=%%~nxI"

echo.
echo    COMPILANDO PROYECTO
echo.

:: COMPILAR ASM
set "OBJS="

for %%F in (*.asm) do (
    echo [NASM] %%F
    nasm -f win64 "%%F" -o "%%~nF.obj"
    if errorlevel 1 (
        echo Error en NASM
        pause
        exit /b 1
    )
    set "OBJS=!OBJS! %%~nF.obj"
)

:: COMPILAR C (FORZADO)
echo.
echo [C] Archivos detectados:

set "CSRC="

for %%F in (*.c) do (
    echo   %%F
    set "CSRC=!CSRC! %%~nF.c"
)

:: Validación
if "!CSRC!"=="" (
    echo ERROR: no se detectaron .c
    echo Carpeta actual: %CD%
    pause
    exit /b 1
)

echo.
echo [GCC] Enlazando...
gcc !CSRC! !OBJS! -o "%CARPETA%.exe"

if errorlevel 1 (
    echo Error en GCC
    pause
    exit /b 1
)

echo.
echo Compilacion exitosa
echo Ejecutando...

"%CARPETA%.exe"

pause
endlocal