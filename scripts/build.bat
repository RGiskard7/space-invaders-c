@echo off
REM Script de compilación para Space Invaders en Windows
REM Autor: RGiskard7
REM Uso: build.bat [clean|run]

setlocal enabledelayedexpansion

REM Cambiar al directorio raíz del proyecto
cd /d "%~dp0\.."

echo ===================================================
echo        Space Invaders - Build Script (Windows)
echo ===================================================
echo.

REM Verificar si existe make o mingw32-make
where mingw32-make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set MAKE_CMD=mingw32-make
    goto :found_make
)

where make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set MAKE_CMD=make
    goto :found_make
)

echo [ERROR] No se encontro make ni mingw32-make
echo.
echo Instala MinGW desde: https://www.mingw-w64.org/
echo O usa MSYS2: https://www.msys2.org/
pause
exit /b 1

:found_make
echo [OK] Comando make encontrado: %MAKE_CMD%

REM Verificar GCC
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] GCC no esta instalado
    echo.
    echo Instala MinGW o MSYS2 para obtener GCC
    pause
    exit /b 1
)
echo [OK] GCC encontrado

REM Manejar argumentos
if "%1"=="clean" (
    echo.
    echo Limpiando archivos...
    del /Q *.o >nul 2>&1
    del /Q SpaceInvaders.exe >nul 2>&1
    echo [OK] Limpieza completada
    exit /b 0
)

REM Determinar qué Makefile usar
set "MAKEFILE_TO_USE=Makefile"

REM Verificar si estamos en entorno MSYS2 (usar Makefile.windows)
if defined MSYSTEM (
    set "MAKEFILE_TO_USE=Makefile.windows"
) else (
    REM Verificar si existe Makefile.windows y usarlo en MSYS2 si está disponible
    if exist Makefile.windows (
        REM Verificar si mingw32-make está disponible (MSYS2/MinGW)
        where mingw32-make >nul 2>&1
        if %ERRORLEVEL% EQU 0 (
            set "MAKEFILE_TO_USE=Makefile.windows"
        )
    )
)

REM Compilar
echo.
echo Compilando Space Invaders...
echo [INFO] Usando: %MAKE_CMD% -f %MAKEFILE_TO_USE%
%MAKE_CMD% -f %MAKEFILE_TO_USE%

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion fallo
    pause
    exit /b 1
)

echo.
echo [OK] Compilacion exitosa: SpaceInvaders.exe
echo.

REM Ejecutar si se especificó
if "%1"=="run" (
    echo Iniciando Space Invaders...
    echo.
    SpaceInvaders.exe
) else (
    echo Para ejecutar el juego, usa:
    echo   SpaceInvaders.exe
    echo.
    echo O ejecuta:
    echo   build.bat run
)

pause

