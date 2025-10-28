@echo off
REM Instalador de dependencias para Space Invaders en Windows
REM Versión simplificada y funcional

setlocal enabledelayedexpansion

cd /d "%~dp0\.."

echo ===================================================
echo    Space Invaders - Instalador de Dependencias
echo ===================================================
echo.

REM Verificar si MSYS2 está instalado
if exist "C:\msys64\mingw64\bin\gcc.exe" (
    set "MSYS2_PATH=C:\msys64"
    set "MSYS2_FOUND=1"
) else if exist "C:\msys32\mingw64\bin\gcc.exe" (
    set "MSYS2_PATH=C:\msys32"
    set "MSYS2_FOUND=1"
) else (
    set "MSYS2_FOUND=0"
)

if %MSYS2_FOUND%==1 (
    echo [OK] MSYS2 encontrado en: %MSYS2_PATH%
    echo.
    goto :install_packages
)

REM MSYS2 no encontrado
echo [ADVERTENCIA] MSYS2 no esta instalado
echo.
echo Para instalar MSYS2:
echo   1. Ve a: https://www.msys2.org/
echo   2. Descarga e instala el MSYS2
echo   3. Ejecuta este script nuevamente
echo.
echo Abriendo pagina de MSYS2...
start https://www.msys2.org/
pause
exit /b 1

:install_packages
echo [INFO] Instalando paquetes necesarios...
echo.

REM Crear script temporal
set "TEMP_SCRIPT=%TEMP%\install_deps_temp.sh"
echo #!/bin/bash > "%TEMP_SCRIPT%"
echo pacman -Sy --noconfirm >> "%TEMP_SCRIPT%"
echo pacman -S --needed --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro make >> "%TEMP_SCRIPT%"

echo Ejecutando instalacion en MSYS2...
echo.
echo IMPORTANTE: Se abrira MSYS2 y deberas ejecutar manualmente:
echo.
echo   bash '%TEMP_SCRIPT%'
echo.
echo Presiona Enter para continuar...
pause

"%MSYS2_PATH%\msys2_shell.cmd" -mingw64

REM Limpiar después de que el usuario presione Enter
echo.
echo Presiona Enter para continuar...
pause

del "%TEMP_SCRIPT%"

echo.
echo ===================================================
echo   SIGUIENTE PASO
echo ===================================================
echo.
echo Si instalaste correctamente los paquetes en MSYS2,
echo ahora puedes compilar con:
echo   scripts\build.bat run
echo.
echo Si necesitas ayuda, lee EMPEZAR_AQUI.md
echo.

pause
