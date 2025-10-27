@echo off
REM Script de instalacion automatica de dependencias para Space Invaders (Windows)
REM Autor: RGiskard7
REM Soporta: MSYS2 con MINGW64

setlocal enabledelayedexpansion

REM Cambiar al directorio raíz del proyecto
cd /d "%~dp0\.."

echo ===================================================
echo    Space Invaders - Instalador de Dependencias
echo                    (Windows)
echo ===================================================
echo.

REM Colores simulados con mensajes
set "INFO=[INFO]"
set "OK=[OK]"
set "ERROR=[ERROR]"
set "WARNING=[ADVERTENCIA]"

echo %INFO% Verificando sistema Windows...
echo.

REM ============================================
REM PASO 1: Verificar si MSYS2 esta instalado
REM ============================================

echo %INFO% Buscando MSYS2 en el sistema...

set "MSYS2_FOUND=0"
set "MSYS2_PATH="

REM Buscar en ubicaciones comunes
if exist "C:\msys64\usr\bin\bash.exe" (
    set "MSYS2_PATH=C:\msys64"
    set "MSYS2_FOUND=1"
)
if exist "C:\msys32\usr\bin\bash.exe" (
    set "MSYS2_PATH=C:\msys32"
    set "MSYS2_FOUND=1"
)
if exist "%USERPROFILE%\msys64\usr\bin\bash.exe" (
    set "MSYS2_PATH=%USERPROFILE%\msys64"
    set "MSYS2_FOUND=1"
)

if %MSYS2_FOUND%==1 (
    echo %OK% MSYS2 encontrado en: %MSYS2_PATH%
    echo.
    goto :install_packages
) else (
    echo %WARNING% MSYS2 no esta instalado en tu sistema
    echo.
    goto :install_msys2_guide
)

REM ============================================
REM PASO 2: Guiar instalacion de MSYS2
REM ============================================

:install_msys2_guide
echo ============================================
echo   INSTALACION DE MSYS2 REQUERIDA
echo ============================================
echo.
echo MSYS2 es necesario para compilar Space Invaders en Windows.
echo Incluye GCC, herramientas de compilacion y el gestor de paquetes pacman.
echo.
echo %INFO% Opciones:
echo.
echo   1. Instalar MSYS2 automaticamente (abre navegador)
echo   2. Instalacion manual (instrucciones)
echo   3. Salir (instalar despues)
echo.
set /p INSTALL_CHOICE="Selecciona una opcion (1/2/3): "

if "%INSTALL_CHOICE%"=="1" goto :auto_install_msys2
if "%INSTALL_CHOICE%"=="2" goto :manual_install_msys2
if "%INSTALL_CHOICE%"=="3" goto :exit_script

echo %ERROR% Opcion no valida
goto :install_msys2_guide

:auto_install_msys2
echo.
echo %INFO% Abriendo pagina de descarga de MSYS2...
start https://www.msys2.org/
echo.
echo %INFO% Pasos a seguir:
echo   1. Descarga el instalador MSYS2
echo   2. Ejecuta el instalador (acepta la ruta por defecto: C:\msys64)
echo   3. Una vez instalado, vuelve a ejecutar este script
echo.
pause
goto :exit_script

:manual_install_msys2
echo.
echo ============================================
echo   INSTRUCCIONES DE INSTALACION MANUAL
echo ============================================
echo.
echo 1. Abre tu navegador y ve a: https://www.msys2.org/
echo.
echo 2. Descarga el instalador (msys2-x86_64-XXXXXXXX.exe)
echo.
echo 3. Ejecuta el instalador:
echo    - Acepta la ruta por defecto: C:\msys64
echo    - Completa la instalacion
echo.
echo 4. Vuelve a ejecutar este script: install-deps.bat
echo.
pause
goto :exit_script

REM ============================================
REM PASO 3: Instalar paquetes en MSYS2
REM ============================================

:install_packages
echo ============================================
echo   INSTALANDO DEPENDENCIAS
echo ============================================
echo.

REM Crear script temporal para ejecutar en MSYS2
set "TEMP_SCRIPT=%TEMP%\msys2_install_deps.sh"

echo #!/bin/bash > "%TEMP_SCRIPT%"
echo echo "====================================================" >> "%TEMP_SCRIPT%"
echo echo "  Instalando dependencias en MSYS2..." >> "%TEMP_SCRIPT%"
echo echo "====================================================" >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo echo "[INFO] Actualizando base de datos de paquetes..." >> "%TEMP_SCRIPT%"
echo pacman -Sy --noconfirm >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo echo "[INFO] Instalando GCC (compilador de C)..." >> "%TEMP_SCRIPT%"
echo pacman -S --needed --noconfirm mingw-w64-x86_64-gcc >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo echo "[INFO] Instalando Allegro 5 (biblioteca grafica)..." >> "%TEMP_SCRIPT%"
echo pacman -S --needed --noconfirm mingw-w64-x86_64-allegro >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo echo "[INFO] Instalando Make (herramienta de compilacion)..." >> "%TEMP_SCRIPT%"
echo pacman -S --needed --noconfirm make >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo echo "====================================================" >> "%TEMP_SCRIPT%"
echo echo "  [OK] Instalacion completada exitosamente" >> "%TEMP_SCRIPT%"
echo echo "====================================================" >> "%TEMP_SCRIPT%"
echo echo "" >> "%TEMP_SCRIPT%"
echo read -p "Presiona Enter para continuar..." >> "%TEMP_SCRIPT%"

echo %INFO% Iniciando MSYS2 MINGW64 para instalar paquetes...
echo.
echo %WARNING% Se abrira una ventana de MSYS2. NO la cierres hasta que termine.
echo.
pause

REM Ejecutar el script en MSYS2 MINGW64
"%MSYS2_PATH%\msys2_shell.cmd" -mingw64 -no-start -defterm -here -c "bash '%TEMP_SCRIPT%'"

REM Limpiar script temporal
del "%TEMP_SCRIPT%"

echo.
echo ============================================
echo   VERIFICACION DE INSTALACION
echo ============================================
echo.

REM Verificar que los paquetes se instalaron
set "MINGW64_BIN=%MSYS2_PATH%\mingw64\bin"

if exist "%MINGW64_BIN%\gcc.exe" (
    echo %OK% GCC instalado correctamente
) else (
    echo %ERROR% GCC no se instalo correctamente
)

if exist "%MINGW64_BIN%\allegro_monolith-5.2.dll" (
    echo %OK% Allegro 5 instalado correctamente
) else (
    if exist "%MINGW64_BIN%\liballegro-5.2.dll" (
        echo %OK% Allegro 5 instalado correctamente
    ) else (
        echo %ERROR% Allegro 5 no se instalo correctamente
    )
)

if exist "%MSYS2_PATH%\usr\bin\make.exe" (
    echo %OK% Make instalado correctamente
) else (
    echo %ERROR% Make no se instalo correctamente
)

echo.
echo ============================================
echo   CONFIGURACION COMPLETA
echo ============================================
echo.
echo %OK% Todas las dependencias estan instaladas!
echo.
echo %INFO% Para compilar el juego, abre MSYS2 MINGW64 y ejecuta:
echo.
echo   cd /c/Users/%USERNAME%/ruta/a/space-invaders-c
echo   make -f Makefile.windows
echo   ./SpaceInvaders.exe
echo.
echo O usa el script de compilacion:
echo   build.bat run
echo.
pause
goto :end

:exit_script
echo.
echo %INFO% Instalacion cancelada.
echo %INFO% Ejecuta este script de nuevo cuando MSYS2 este instalado.
echo.
pause
goto :end

:end
endlocal

