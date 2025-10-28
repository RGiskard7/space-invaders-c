@echo off
REM Script de compilacion para Space Invaders en Windows
REM Versión corregida y simplificada

cd /d "%~dp0\.."

echo ===================================================
echo        Compilando Space Invaders
echo ===================================================
echo.

REM Intentar compilar con los Makefiles disponibles
if exist Makefile.windows (
    echo [INFO] Usando Makefile.windows
    make -f Makefile.windows
) else if exist Makefile (
    echo [INFO] Usando Makefile
    where mingw32-make >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        mingw32-make -f Makefile
    ) else (
        make -f Makefile
    )
) else (
    echo [ERROR] No se encontro Makefile
    echo.
    echo Instala MSYS2 desde: https://www.msys2.org/
    echo O ejecuta primero: scripts\install-deps.bat
    echo.
    pause
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] La compilacion fallo
    echo.
    echo Posibles soluciones:
    echo   1. Ejecuta scripts\install-deps.bat
    echo   2. Lee EMPEZAR_AQUI.md para mas ayuda
    echo.
    pause
    exit /b 1
)

echo.
echo ===================================================
echo   [OK] Compilacion exitosa
echo ===================================================
echo.

if "%1"=="run" (
    echo Iniciando juego...
    echo.
    if exist SpaceInvaders.exe (
        SpaceInvaders.exe
    ) else if exist SpaceInvaders (
        ./SpaceInvaders
    ) else (
        echo [ERROR] No se encontro el ejecutable
    )
) else (
    echo Para ejecutar: SpaceInvaders.exe
    echo O: scripts\build.bat run
    echo.
)

pause
