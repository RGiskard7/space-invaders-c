@echo off
REM Script de instalación automática de Allegro para MinGW (Opción B)
REM Descarga e instala Allegro en C:\allegro-5.2.9.1-mingw-14.1.0
REM Autor: RGiskard7

setlocal enabledelayedexpansion

REM Cambiar al directorio raíz del proyecto
cd /d "%~dp0\.."

echo ===================================================
echo    Instalador de Allegro 5 para MinGW (Opción B)
echo ===================================================
echo.

set "ALLEGRO_VERSION=5.2.9.1"
set "MINGW_VERSION=14.1.0"
set "ALLEGRO_DIR=C:\allegro-%ALLEGRO_VERSION%-mingw-%MINGW_VERSION%"
set "DOWNLOAD_URL=https://github.com/liballeg/allegro5/releases/download/%ALLEGRO_VERSION%/allegro-%ALLEGRO_VERSION%-mingw-%MINGW_VERSION%.zip"
set "TEMP_ZIP=%TEMP%\allegro-mingw.zip"

REM Verificar si MinGW/GCC está instalado
echo [INFO] Verificando si MinGW/GCC está instalado...
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [WARNING] MinGW/GCC no está instalado en tu sistema
    echo.
    echo ============================================
    echo   INSTALACION DE MINGW REQUERIDA
    echo ============================================
    echo.
    echo MinGW-w64 es necesario para compilar el proyecto en Windows.
    echo.
    echo Opciones:
    echo   1. Abrir TDM-GCC (fácil para principiantes)
    echo   2. Abrir MinGW-w64
    echo   3. Abrir MSYS2 (recomendado - opción A)
    echo   4. Salir
    echo.
    set /p MINGW_CHOICE="Selecciona una opción (1-4): "

    if "%MINGW_CHOICE%"=="1" (
        echo.
        echo [INFO] Abriendo TDM-GCC...
        echo Descarga e instala la versión 64-bit
        echo.
        start https://jmeubank.github.io/tdm-gcc/
        pause
        exit /b 1
    ) else if "%MINGW_CHOICE%"=="2" (
        echo.
        echo [INFO] Abriendo MinGW-w64...
        start https://www.mingw-w64.org/downloads/
        pause
        exit /b 1
    ) else if "%MINGW_CHOICE%"=="3" (
        echo.
        echo [INFO] Redirigiendo al instalador de MSYS2...
        call "%~dp0install-deps.bat"
        exit /b 0
    ) else if "%MINGW_CHOICE%"=="4" (
        exit /b 0
    ) else (
        echo [ERROR] Opción no válida
        pause
        exit /b 1
    )
)

echo [OK] MinGW/GCC encontrado
gcc --version | findstr /C:"gcc"
echo.

echo [INFO] Este instalador descargará e instalará Allegro 5 para MinGW
echo [INFO] Destino: %ALLEGRO_DIR%
echo.

REM Verificar si Allegro ya está instalado
if exist "%ALLEGRO_DIR%\lib" (
    echo [OK] Allegro ya está instalado en: %ALLEGRO_DIR%
    echo [INFO] Si quieres reinstalarlo, elimina manualmente la carpeta y ejecuta este script de nuevo.
    echo.
    pause
    exit /b 0
)

REM Verificar conexión a internet
echo [INFO] Verificando conexión a internet...
ping -n 1 8.8.8.8 >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] No se pudo conectar a internet. Verifica tu conexión.
    echo.
    pause
    exit /b 1
)
echo [OK] Conexión a internet disponible
echo.

REM Descargar Allegro
echo [INFO] Descargando Allegro %ALLEGRO_VERSION% desde GitHub...
echo [INFO] URL: %DOWNLOAD_URL%
echo [INFO] Esto puede tardar varios minutos dependiendo de tu conexión...
echo.

REM Verificar si curl está disponible
where curl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    curl -L -o "%TEMP_ZIP%" "%DOWNLOAD_URL%"
) else (
    echo [ERROR] curl no está disponible. Instalando manualmente...
    echo.
    echo Por favor:
    echo 1. Abre tu navegador
    echo 2. Ve a: %DOWNLOAD_URL%
    echo 3. Descarga el archivo .zip
    echo 4. Extráelo en: %ALLEGRO_DIR%
    echo.
    start %DOWNLOAD_URL%
    pause
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Error al descargar Allegro
    echo.
    echo Por favor, descarga manualmente:
    echo 1. Abre tu navegador
    echo 2. Ve a: https://github.com/liballeg/allegro5/releases
    echo 3. Busca la versión: allegro-%ALLEGRO_VERSION%-mingw-%MINGW_VERSION%.zip
    echo 4. Descarga y extrae en: %ALLEGRO_DIR%
    echo.
    pause
    exit /b 1
)

if not exist "%TEMP_ZIP%" (
    echo [ERROR] El archivo descargado no existe
    pause
    exit /b 1
)

echo [OK] Descarga completada
echo.

REM Verificar si PowerShell está disponible para extraer
where powershell >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] PowerShell no está disponible
    pause
    exit /b 1
)

REM Extraer Allegro
echo [INFO] Extrayendo Allegro a %ALLEGRO_DIR%...
powershell -command "Expand-Archive -Path '%TEMP_ZIP%' -DestinationPath 'C:\' -Force"

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Error al extraer el archivo ZIP
    echo.
    echo Por favor, extrae manualmente %TEMP_ZIP% a C:\
    echo.
    pause
    exit /b 1
)

REM Verificar que se extrajo correctamente
if not exist "%ALLEGRO_DIR%\lib" (
    echo [ERROR] Allegro no se instaló correctamente
    echo [ERROR] No se encuentra la carpeta lib en: %ALLEGRO_DIR%
    pause
    exit /b 1
)

REM Limpiar archivo temporal
del "%TEMP_ZIP%"

echo.
echo ===================================================
echo   [OK] Allegro instalado correctamente
echo ===================================================
echo.
echo Ubicación: %ALLEGRO_DIR%
echo.
echo Ahora puedes compilar el proyecto con:
echo   scripts\build.bat
echo.
echo O ejecutar directamente:
echo   scripts\build.bat run
echo.

pause

