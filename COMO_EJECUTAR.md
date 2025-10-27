# 🎮 Cómo Ejecutar Space Invaders

Este documento explica cómo compilar y ejecutar el juego en **macOS** y **Windows**.

---

## 🍎 macOS

### Primera Vez (Instalación)

```bash
# 1. Instalar Allegro (solo una vez)
scripts/install-deps.sh

# 2. Compilar
make -f Makefile.unix

# 3. Ejecutar
./SpaceInvaders
```

### Ejecuciones Siguientes

```bash
# Compilar y ejecutar en un solo comando
scripts/build.sh run

# O separado:
make -f Makefile.unix
./SpaceInvaders
```

### Cambiar Tamaño de Ventana

Edita `include/config.h` líneas 30-31:
```c
#define DISPLAY_HEIGHT 900  // Cambia este número
#define DISPLAY_WIDTH 900   // Cambia este número
```

Luego recompila:
```bash
make -f Makefile.unix clean
make -f Makefile.unix
```

---

## 🪟 Windows

### Opción A: Con MSYS2 (Recomendado)

#### Primera Vez - Instalación Automática
```cmd
:: Ejecutar el instalador automático (detecta e instala MSYS2 + dependencias)
scripts\install-deps.bat
```

El script automáticamente:
- Detecta si MSYS2 está instalado
- Si no lo está, te guía para instalarlo
- Instala GCC, Allegro 5 y Make automáticamente

#### Primera Vez - Instalación Manual
```bash
# 1. Instalar MSYS2 desde: https://www.msys2.org/

# 2. Abrir "MSYS2 MINGW64" y ejecutar:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro make

# 3. Navegar al proyecto (varias opciones):
# Opción A: Si está en tu home
cd ~

# Opción B: Si está en OneDrive
cd /c/Users/TuUsuario/OneDrive/

# Opción C: Si está en Escritorio
cd /c/Users/TuUsuario/Desktop/

# Opción D: Buscar el proyecto
find /c -name "space-invaders-c" -type d 2>/dev/null
# Luego cd a la ruta encontrada

cd espacio-invaders-c  # O como se llame tu carpeta

# 4. Compilar (usa Makefile.windows, NO Makefile.unix)
make -f Makefile.windows

# 5. Ejecutar
./SpaceInvaders.exe
```

#### Ejecuciones Siguientes
```bash
# En la terminal MSYS2 MINGW64:
make -f Makefile.windows
./SpaceInvaders.exe
```

### Opción B: Con MinGW + CMD (Si tienes Allegro instalado en C:\)

#### Primera Vez
```cmd
:: Asegúrate de que MinGW esté en el PATH

:: Compilar
mingw32-make

:: Ejecutar
SpaceInvaders.exe
```

#### Ejecuciones Siguientes
```cmd
mingw32-make
SpaceInvaders.exe
```

### Cambiar Tamaño de Ventana

Edita `include\config.h` líneas 30-31:
```c
#define DISPLAY_HEIGHT 900  // Cambia este número
#define DISPLAY_WIDTH 900   // Cambia este número
```

Luego recompila:
```cmd
mingw32-make clean
mingw32-make
```

---

## 🎯 Verificación Rápida

En **ambos sistemas**, puedes verificar que los recursos son accesibles:

### macOS/Linux:
```bash
scripts/test_resources.sh
```

### Windows (MSYS2):
```bash
scripts/test_resources.sh
```

### Windows (CMD):
Verifica manualmente que exista la carpeta `resources` al mismo nivel que el ejecutable.

---

## ⚙️ Configuración Actual

- **Resolución de ventana:** 600x600 píxeles (igual en Windows y macOS)
- **Vidas iniciales:** 3
- **Enemigos:** 55 marcianos (11x5)
- **Velocidad de nave:** 6
- **Velocidad de proyectiles:** 15

Para cambiar estos valores, edita `include/config.h` y recompila.

---

## 🎮 Controles

| Tecla | Acción |
|-------|--------|
| **←** | Mover izquierda |
| **→** | Mover derecha |
| **ESPACIO** | Disparar |
| **ESC** | Salir |

---

## ⚠️ Importante

- **SIEMPRE ejecuta el juego desde el directorio raíz del proyecto**
- El ejecutable debe estar al mismo nivel que la carpeta `resources/`
- Si mueve el ejecutable a otra ubicación, mueve también la carpeta `resources/`

---

## 🐛 Problemas Comunes

### "Error initializing game"
- Estás ejecutando desde el directorio incorrecto
- Ejecuta desde el directorio raíz: `./SpaceInvaders` (macOS) o `SpaceInvaders.exe` (Windows)

### "Cannot find resources"
- Verifica que la carpeta `resources` esté al mismo nivel que el ejecutable
- Usa `./test_resources.sh` para diagnóstico

### Ventana muy pequeña
- Edita `include/config.h` y aumenta `DISPLAY_HEIGHT` y `DISPLAY_WIDTH`
- Recompila el proyecto

### No compila en Windows
- Asegúrate de tener MinGW o MSYS2 instalado
- Verifica que GCC esté en el PATH: `gcc --version`

---

## 📁 Estructura Correcta del Proyecto

```
space-invaders-c/
├── SpaceInvaders           (macOS/Linux)
├── SpaceInvaders.exe       (Windows)
├── resources/              ← DEBE estar aquí
│   ├── images/
│   ├── sounds/
│   └── fonts/
├── src/
├── include/
└── ...
```

---

**El juego está configurado para verse IGUAL en macOS y Windows (900x900 píxeles).**

