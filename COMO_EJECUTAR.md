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

### Opción A: Script Automático (Recomendado)

#### Primera Vez - Instalación
```cmd
:: Ejecutar como Administrador
scripts\install-deps.bat
```

El script descargará e instalará:
- **MinGW 14.1.0** en `C:\mingw64`
- **Allegro 5.2.9** en `C:\allegro-5.2.9.1-mingw-14.1.0`

#### Ejecución
```cmd
scripts\build.bat run
```

### Opción B: Manual

#### Primera Vez - Instalación Manual
1. Descarga **MinGW 14.1.0** (WinLibs) y extráelo en `C:\mingw64`.
2. Descarga **Allegro 5.2.9** y extráelo en `C:\allegro-5.2.9.1-mingw-14.1.0`.

#### Compilación y Ejecución
Asegúrate de que `C:\mingw64\bin` esté en tu PATH.

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

