# 🎮 Como Ejecutar Space Invaders

Este documento explica como compilar y ejecutar el juego en **macOS**, **Linux** y **Windows**.

---

## 🍎 macOS

### Primera Vez (Instalacion)

```bash
# 1. Instalar dependencias automaticamente
./scripts/install-deps.sh

# 2. Compilar
make -f Makefile.unix

# 3. Ejecutar
./SpaceInvaders
```

### Ejecuciones Siguientes

```bash
# Compilar y ejecutar en un solo comando
./scripts/build.sh run

# O separado:
make -f Makefile.unix
./SpaceInvaders
```

### Cambiar Tamano de Ventana

Edita `include/config.h` lineas ~50:
```c
#define DISPLAY_HEIGHT 900   // Cambia este numero
#define DISPLAY_WIDTH 900    // Cambia este numero
```

Luego recompila:
```bash
make -f Makefile.unix clean
make -f Makefile.unix
```

---

## 🐧 Linux (Ubuntu/Debian)

### Primera Vez

```bash
sudo apt update
sudo apt install build-essential gcc liballegro5-dev liballegro-image-5.0-dev liballegro-audio-5.0-dev liballegro-acodec-5.0-dev pkg-config

# Compilar y ejecutar (desde la carpeta del proyecto)
make -f Makefile.unix
make -f Makefile.unix run
```

### Otras Distribuciones

**Fedora:**
```bash
sudo dnf install gcc make allegro5-devel pkg-config
make -f Makefile.unix
```

**Arch:**
```bash
sudo pacman -S base-devel allegro pkg-config
make -f Makefile.unix
```

---

## 🪟 Windows

### Opcion A: MSYS2/MinGW (Recomendado)

#### Primera Vez - Instalacion
```cmd
:: Desde MSYS2 MinGW-w64
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro mingw-w64-x86_64-pkg-config
```

#### Ejecucion
```cmd
mingw32-make -f Makefile.unix
SpaceInvaders.exe
```

### Opcion B: Script con MinGW Manual

Asegurate de que `C:\mingw64\bin` esté en tu PATH.

```cmd
scripts\build.bat run
```

### Cambiar Tamano de Ventana

Edita `include\config.h` y aumenta `DISPLAY_HEIGHT` / `DISPLAY_WIDTH`.

Luego recompila:
```cmd
mingw32-make -f Makefile.unix clean
mingw32-make -f Makefile.unix
```

---

## 🎯 Verificacion Rapida

En **todos los sistemas**, puedes verificar que los recursos son accesibles:

```bash
./scripts/test_resources.sh
```

Tambien puedes verificar dependencias con el Makefile:
```bash
make -f Makefile.unix check-deps
```

---

## ⚙️ Configuracion Actual

- **Resolucion de ventana:** 600x600 pixeles
- **Vidas iniciales:** 3
- **Enemigos:** 55 marcianos (11x5)
- **Velocidad de nave:** 6
- **Velocidad de proyectiles:** 15

Para cambiar estos valores, edita `include/config.h` y recompila.

---

## 🎮 Controles

| Tecla | Accion |
| ----- | ------ |
| **←** | Mover izquierda |
| **→** | Mover derecha |
| **ESPACIO** | Disparar |
| **ESC** | Salir |
| **P** | Pausar/Reanudar |
| **ENTER** | Reiniciar (tras Game Over) |

---

## ⚠️ Importante

- **SIEMPRE ejecuta el juego desde el directorio raiz del proyecto**
- El ejecutable debe estar al mismo nivel que la carpeta `resources/`
- Si mueves el ejecutable a otra ubicacion, mueve tambien la carpeta `resources/`

---

## 🐛 Problemas Comunes

### "Error initializing game"
- Estas ejecutando desde el directorio incorrecto
- Ejecuta desde el directorio raiz: `./SpaceInvaders`

### "Cannot find resources"
- Verifica que la carpeta `resources` esté al mismo nivel que el ejecutable
- Usa `./scripts/test_resources.sh` para diagnostico

### Ventana muy pequena
- Edita `include/config.h` y aumenta `DISPLAY_HEIGHT` y `DISPLAY_WIDTH`
- Recompila el proyecto

### No compila: "undefined reference"
- Te faltan las librerias de audio: `allegro_audio-5` y `allegro_acodec-5`
- Usa `./scripts/build.sh` o `make -f Makefile.unix` que incluyen automaticamente todas

### Permission denied (macOS)
```bash
chmod +x SpaceInvaders
chmod +x scripts/build.sh
chmod +x scripts/install-deps.sh
chmod +x scripts/test_resources.sh
./SpaceInvaders
```

---

## 📁 Estructura Correcta del Proyecto

```
space-invaders-c/
├── SpaceInvaders           (macOS/Linux)
├── resources/              ← DEBE estar aqui
│   ├── images/
│   ├── sounds/
│   └── fonts/
├── src/
├── include/
├── scripts/
├── Makefile.unix
└── Makefile
```

---

**El juego esta configurado para verse igual en todos los sistemas (600x600 pixeles por defecto).**
