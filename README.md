# Space Invaders en C

<div align="center">
  <img src="https://github.com/user-attachments/assets/48a46d8a-0180-436b-8c95-7769712331ff" alt="Space Invaders" width="600"/>
</div>

> **⚡ Inicio Rápido:**
> Si quieres empezar inmediatamente, ejecuta:
> ```bash
> scripts/install-deps.sh  # Instala Allegro y dependencias automáticamente
> scripts/build.sh run     # Compila y ejecuta el juego
> ```
>
> O consulta [`QUICK_START.md`](QUICK_START.md) para instrucciones detalladas.

---

## 📑 Tabla de Contenidos

- [Space Invaders en C](#space-invaders-en-c)
  - [📑 Tabla de Contenidos](#-tabla-de-contenidos)
  - [📋 Descripción del Proyecto](#-descripción-del-proyecto)
    - [Características Principales](#características-principales)
  - [🏗️ Arquitectura del Proyecto](#️-arquitectura-del-proyecto)
  - [🔧 Requisitos del Sistema](#-requisitos-del-sistema)
    - [Software Necesario](#software-necesario)
    - [Sistemas Operativos Soportados](#sistemas-operativos-soportados)
  - [📦 Instalación de Dependencias](#-instalación-de-dependencias)
    - [En macOS](#en-macos)
    - [En Windows](#en-windows)
      - [Opción 1: Instalación Automática (Recomendado)](#opción-1-instalación-automática-recomendado)
      - [Opción 2: Instalación Manual](#opción-2-instalación-manual)
      - [Opción 2: Instalación manual de Allegro](#opción-2-instalación-manual-de-allegro)
    - [En Linux (Ubuntu/Debian)](#en-linux-ubuntudebian)
    - [En Linux (Fedora)](#en-linux-fedora)
  - [🚀 Compilación y Ejecución](#-compilación-y-ejecución)
    - [1. Clonar el Repositorio](#1-clonar-el-repositorio)
    - [2. Compilar el Proyecto](#2-compilar-el-proyecto)
      - [En macOS/Linux](#en-macoslinux)
      - [En Windows](#en-windows-1)
    - [3. Ejecutar el Juego](#3-ejecutar-el-juego)
      - [En macOS/Linux](#en-macoslinux-1)
      - [En Windows](#en-windows-2)
  - [🎮 Controles del Juego](#-controles-del-juego)
  - [⚙️ Configuración del Juego](#️-configuración-del-juego)
  - [🐛 Solución de Problemas](#-solución-de-problemas)
    - [Error: "Allegro not found" (macOS/Linux)](#error-allegro-not-found-macoslinux)
    - [Error: "Cannot find -lallegro\_monolith" (Windows)](#error-cannot-find--lallegro_monolith-windows)
    - [El juego se ejecuta pero no muestra gráficos o dice "Error initializing game"](#el-juego-se-ejecuta-pero-no-muestra-gráficos-o-dice-error-initializing-game)
    - [Error de compilación: "undefined reference to..."](#error-de-compilación-undefined-reference-to)
    - [En macOS: "permission denied" al ejecutar](#en-macos-permission-denied-al-ejecutar)
  - [📝 Desarrollo y Contribución](#-desarrollo-y-contribución)
    - [Compilar en Modo Debug](#compilar-en-modo-debug)
    - [Ejecutar con Valgrind (detección de memory leaks)](#ejecutar-con-valgrind-detección-de-memory-leaks)
    - [Estructura de Commits](#estructura-de-commits)
    - [Roadmap del Proyecto](#roadmap-del-proyecto)
  - [📜 Licencia](#-licencia)
  - [🤝 Contribuciones](#-contribuciones)
    - [Áreas de Mejora](#áreas-de-mejora)
  - [📞 Contacto](#-contacto)
  - [📚 Referencias y Recursos](#-referencias-y-recursos)
  - [🙏 Agradecimientos](#-agradecimientos)

---

## 📋 Descripción del Proyecto

**Space Invaders en C** es una implementación del clásico juego arcade desarrollada en C utilizando la biblioteca gráfica **Allegro 5**. El proyecto demuestra programación estructurada, gestión de memoria dinámica, detección de colisiones, y renderizado de gráficos 2D.

### Características Principales

- **Nave espacial controlable** con movimiento lateral y disparo
- **55 invasores alienígenas** organizados en formación (11x5)
- **Sistema de colisiones** entre proyectiles y entidades
- **Sistema de puntuación** por tipo de enemigo (10/20/30 puntos)
- **Sistema de vidas** (3 vidas iniciales)
- **Sprites y animaciones** personalizadas
- **Efectos de sonido** integrados
- **Configuración modular** en `config.h`

---

## 🏗️ Arquitectura del Proyecto

```
space-invaders-c/
├── scripts/             # Scripts de automatización
│   ├── install-deps.sh  # Instalador de dependencias (macOS/Linux)
│   ├── install-deps.bat # Instalador de dependencias (Windows)
│   ├── build.sh         # Script de compilación (macOS/Linux)
│   ├── build.bat        # Script de compilación (Windows)
│   └── test_resources.sh # Verificador de recursos
├── include/             # Archivos de cabecera (.h)
│   ├── bullet.h         # Gestión de proyectiles
│   ├── config.h         # Configuración centralizada
│   ├── game.h           # Lógica principal del juego
│   ├── martian.h        # Lógica de enemigos
│   ├── object.h         # Objetos genéricos (explosiones, etc.)
│   ├── ship.h           # Lógica de la nave del jugador
│   └── types.h          # Tipos y enumeraciones
├── src/                 # Código fuente (.c)
│   ├── main.c           # Punto de entrada
│   ├── game.c           # Bucle principal y gestión del juego
│   ├── bullet.c         # Implementación de proyectiles
│   ├── ship.c           # Implementación de la nave
│   ├── martian.c        # Implementación de enemigos
│   └── object.c         # Implementación de objetos
├── resources/           # Recursos del juego
│   ├── images/          # Sprites y gráficos (.bmp, .png)
│   ├── sounds/          # Efectos de sonido (.wav)
│   └── fonts/           # Fuentes (.ttf)
├── lib/                 # Bibliotecas de Allegro (Windows)
├── Makefile             # Makefile para Windows
├── Makefile.unix        # Makefile para macOS/Linux
└── README.md            # Este archivo
```

---

## 🔧 Requisitos del Sistema

### Software Necesario

- **Compilador C**: GCC (recomendado: MinGW-w64 para Windows, GCC/Clang para macOS)
- **Biblioteca Allegro 5**: Versión 5.2 o superior
- **Make**: Para usar el Makefile (opcional en Windows, usar mingw32-make)
- **Git**: Para clonar el repositorio

### Sistemas Operativos Soportados

- **Windows** 10/11 (x64)
- **macOS** 10.15+ (Catalina o superior)
- **Linux** (Ubuntu, Debian, Fedora, Arch)

---

## 📦 Instalación de Dependencias

### En macOS

1. **Instalar Homebrew** (si no lo tienes):
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. **Instalar Allegro 5**:
```bash
brew install allegro
```

3. **Verificar instalación**:
```bash
pkg-config --modversion allegro-5
```

### En Windows

#### Opción 1: Instalación Automática (Legacy/Manual)

Ejecuta el instalador desde CMD o PowerShell **como Administrador**:

```cmd
scripts\install-deps.bat
```

Este script descargará e instalará automáticamente:
- **MinGW 14.1.0** en `C:\mingw64`
- **Allegro 5.2.9** en `C:\allegro-5.2.9.1-mingw-14.1.0`

#### Opción 2: Instalación Manual

Si prefieres hacerlo tú mismo:
1. Descarga **MinGW 14.1.0** (WinLibs) y extráelo en `C:\mingw64`.
2. Descarga **Allegro 5.2.9** (MinGW 13.2.0 compatible) y extráelo en `C:\allegro-5.2.9.1-mingw-14.1.0`.

#### Opción 2: Instalación manual de Allegro

1. Descarga Allegro 5.2 precompilado desde: https://github.com/liballeg/allegro5/releases
2. Extrae en `C:\allegro-5.2.9.1-mingw-14.1.0\` (o actualiza las rutas en el Makefile)

### En Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential
sudo apt install liballegro5-dev liballegro5.2
```

### En Linux (Fedora)

```bash
sudo dnf install gcc make
sudo dnf install allegro5-devel allegro5
```

---

## 🚀 Compilación y Ejecución

### 1. Clonar el Repositorio

```bash
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c
```

### 2. Compilar el Proyecto

#### En macOS/Linux

**Opción A: Crear un Makefile nuevo para Unix**

Dado que el Makefile actual está configurado para Windows, crea un archivo `Makefile.unix`:

```makefile
# Makefile.unix para macOS/Linux

CC=gcc
CFLAGS=-g -Wall -pedantic
EXECUTABLE=SpaceInvaders

# Detección automática de pkg-config
ALLEGRO_LIBS=$(shell pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)
ALLEGRO_CFLAGS=$(shell pkg-config --cflags allegro-5)

# Archivos fuente y objetos
SRCS=src/main.c src/game.c src/bullet.c src/ship.c src/martian.c src/object.c
OBJS=main.o game.o bullet.o ship.o martian.o object.o

# Regla por defecto
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(OBJS)
	@echo "Compilando Space Invaders..."
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(ALLEGRO_LIBS)
	@echo "Compilacion exitosa: ./$(EXECUTABLE)"

# Reglas para compilar objetos
%.o: src/%.c
	$(CC) $(ALLEGRO_CFLAGS) -I include $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f *.o $(EXECUTABLE)

# Ejecutar el juego
run: all
	./$(EXECUTABLE)

# Empaquetar
dist: clean
	tar -czf space-invaders.tar.gz src/ include/ resources/ Makefile.unix README.md

.PHONY: all clean run dist
```

Luego compila con:

```bash
make -f Makefile.unix
```

**Opción B: Compilación manual**

```bash
# Compilar archivos objeto
gcc -c src/main.c -I include $(pkg-config --cflags allegro-5) -o main.o
gcc -c src/game.c -I include $(pkg-config --cflags allegro-5) -o game.o
gcc -c src/bullet.c -I include $(pkg-config --cflags allegro-5) -o bullet.o
gcc -c src/ship.c -I include $(pkg-config --cflags allegro-5) -o ship.o
gcc -c src/martian.c -I include $(pkg-config --cflags allegro-5) -o martian.o
gcc -c src/object.c -I include $(pkg-config --cflags allegro-5) -o object.o

# Enlazar
gcc -o SpaceInvaders main.o game.o bullet.o ship.o martian.o object.o \
    $(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)
```

#### En Windows

**Opción A: Script Automático (Recomendado)**

```cmd
scripts\build.bat run
```

**Opción B: Manual (MinGW)**

Asegúrate de que `C:\mingw64\bin` esté en tu PATH y ejecuta:

```cmd
mingw32-make
SpaceInvaders.exe
```

### 3. Ejecutar el Juego

#### En macOS/Linux

```bash
./SpaceInvaders
```

#### En Windows

```bash
SpaceInvaders.exe
```

### 4. Ejecutar desde Visual Studio Code (Recomendado)

Si usas VS Code, el proyecto ya está configurado para compilar y ejecutar fácilmente:

1.  **Compilar y Jugar**: Pulsa `F5`.
    *   Esto recompilará automáticamente cualquier cambio y lanzará el juego con el depurador.
2.  **Solo Compilar**: Pulsa `Ctrl+Shift+B`.
    *   Útil para verificar errores sin abrir el juego.

---

## 🎮 Controles del Juego

| Tecla | Acción |
|-------|--------|
| `←` (Flecha Izquierda) | Mover nave a la izquierda |
| `→` (Flecha Derecha) | Mover nave a la derecha |
| `ESPACIO` | Disparar proyectil |
| `ESC` | Salir del juego |

---

## ⚙️ Configuración del Juego

Puedes modificar parámetros del juego editando `include/config.h`:

```c
// Resolución de pantalla
#define DISPLAY_HEIGHT 600
#define DISPLAY_WIDTH 600

// Configuración de la nave
#define SHIP_SPEED 6           // Velocidad de movimiento
#define SHIP_BULLET_SPEED 15   // Velocidad de proyectiles
#define SHIP_LIFE 3            // Vidas iniciales

// Configuración de marcianos
#define MAX_ENEMIES 55         // Número de enemigos
#define MART_SPEED 5           // Velocidad de enemigos
#define MART_BULLET_SPEED 5    // Velocidad de disparos

// Modo Dios (invencibilidad)
#define GOD_MODE 0             // 0 = desactivado, 1 = activado

// Puntuación por tipo de enemigo
#define POINTS_01 30           // Fila superior
#define POINTS_02 20           // Fila media
#define POINTS_03 10           // Fila inferior
```

Después de modificar `config.h`, **recompila** el proyecto.

---

## 🐛 Solución de Problemas

### Error: "Allegro not found" (macOS/Linux)

```bash
# Verifica que pkg-config encuentra Allegro
pkg-config --modversion allegro-5

# Si no aparece, reinstala Allegro
brew reinstall allegro  # macOS
sudo apt reinstall liballegro5-dev  # Linux
```

### Error: "Cannot find -lallegro_monolith" (Windows)

El Makefile busca la biblioteca en rutas específicas. Soluciones:

1. **Usa las DLLs incluidas**: Copia `allegro_monolith-5.2.dll` a la misma carpeta que el `.exe`
2. **Ajusta las rutas en el Makefile** (líneas 8-16)
3. **Instala Allegro con MSYS2**:
```bash
pacman -S mingw-w64-x86_64-allegro
```

### El juego se ejecuta pero no muestra gráficos o dice "Error initializing game"

**Problema**: Las rutas de recursos no son correctas o el juego no se ejecuta desde el directorio correcto.

**Solución**:

1. **Ejecuta el juego SIEMPRE desde el directorio raíz del proyecto:**
```bash
# ✅ Correcto
cd space-invaders-c
./SpaceInvaders

# ❌ Incorrecto
cd space-invaders-c/src
../SpaceInvaders  # No encontrará los recursos
```

2. **Verifica que las rutas en `config.h` sean correctas:**
```c
// ✅ Correcto (ejecutable en directorio raíz)
#define BACKGROUND_IMG_RSC "resources/images/background.bmp"

// ❌ Incorrecto
#define BACKGROUND_IMG_RSC "../resources/images/background.bmp"
```

3. **Usa el script de verificación:**
```bash
scripts/test_resources.sh
```

Este script te dirá si todos los recursos son accesibles desde la ubicación actual.

### Error de compilación: "undefined reference to..."

Falta enlazar alguna biblioteca de Allegro. Asegúrate de incluir:

- `allegro_monolith` (Windows) o todas las individuales (Unix):
  - `allegro-5`
  - `allegro_main-5`
  - `allegro_image-5`
  - `allegro_font-5`
  - `allegro_ttf-5`
  - `allegro_primitives-5`

### En macOS: "permission denied" al ejecutar

```bash
chmod +x SpaceInvaders
./SpaceInvaders
```

---

## 📝 Desarrollo y Contribución

### Compilar en Modo Debug

```bash
# macOS/Linux
make -f Makefile.unix
# Ya incluye -g para debug

# Windows
mingw32-make
# Ya incluye -g en CFLAGS
```

### Ejecutar con Valgrind (detección de memory leaks)

```bash
valgrind --leak-check=full ./SpaceInvaders
```

### Estructura de Commits

Al contribuir, sigue este formato:

```
tipo(alcance): descripción breve

- Detalle 1
- Detalle 2
```

Ejemplos:
- `feat(ship): añadir escudo temporal`
- `fix(collision): corregir detección con bordes`
- `docs(readme): actualizar instrucciones de macOS`

### Roadmap del Proyecto

- [x] **Fase 1**: Mecánicas básicas (movimiento, disparos, colisiones)
- [x] **Fase 2**: Sistema de puntuación y vidas
- [ ] **Fase 3**: Menú principal y pantalla de Game Over
- [ ] **Fase 4**: Niveles progresivos con dificultad creciente
- [ ] **Fase 5**: Power-ups y mejoras de nave
- [ ] **Fase 6**: Tabla de puntuaciones (high scores)

---

## 📜 Licencia

Este proyecto está bajo la licencia **MIT**. Consulta el archivo [LICENSE](LICENSE) para más información.

```
MIT License

Copyright (c) 2024 RGiskard7

Se concede permiso para usar, copiar, modificar y distribuir este software
con o sin fines comerciales, siempre que se incluya este aviso de copyright.
```

---

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Para contribuir:

1. Haz un **fork** del repositorio
2. Crea una **rama** para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. **Commit** tus cambios (`git commit -m 'feat: añadir nueva funcionalidad'`)
4. **Push** a la rama (`git push origin feature/nueva-funcionalidad`)
5. Abre un **Pull Request**

### Áreas de Mejora

- Mejorar sprites y animaciones
- Añadir más efectos de sonido
- Implementar música de fondo
- Sistema de puntuaciones persistente
- Soporte para múltiples idiomas
- Soporte para gamepad/joystick

---

## 📞 Contacto

- **Autor**: RGiskard7
- **GitHub**: [@RGiskard7](https://github.com/RGiskard7)
- **Repositorio**: [space-invaders-c](https://github.com/RGiskard7/space-invaders-c)
- **Issues**: [Reportar un bug](https://github.com/RGiskard7/space-invaders-c/issues)

---

## 📚 Referencias y Recursos

- **Allegro 5 Documentation**: https://liballeg.org/a5docs/trunk/
- **Space Invaders Original**: https://en.wikipedia.org/wiki/Space_Invaders
- **C Programming**: https://www.learn-c.org/
- **Game Development Patterns**: https://gameprogrammingpatterns.com/

---

## 🙏 Agradecimientos

- Comunidad de **Allegro 5** por la excelente biblioteca
- Taito Corporation por el juego original **Space Invaders** (1978)
- Todos los contribuidores y testers del proyecto

---

<div align="center">

**¿Te gustó el proyecto? ¡Dale una ⭐ en GitHub!**

[🐛 Reportar Bug](https://github.com/RGiskard7/space-invaders-c/issues) ·
[💡 Sugerir Feature](https://github.com/RGiskard7/space-invaders-c/issues) ·
[📖 Ver Documentación](https://github.com/RGiskard7/space-invaders-c/wiki)

</div>

-----

<p align="center">
  <small>Desarrollado por <b>Edu Díaz</b> (<b>RGiskard7</b>) ❤️</small>
</p>
