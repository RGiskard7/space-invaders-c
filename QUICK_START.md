# Guía Rápida de Inicio - Space Invaders

Esta guía te ayudará a compilar y ejecutar el juego en **menos de 5 minutos**.

---

## El Camino MÁS Rápido (Todos los Sistemas)

```bash
# 1. Clonar el proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 2. Instalar dependencias automáticamente
scripts/install-deps.sh

# 3. Compilar y ejecutar
scripts/build.sh run
```

**¡Listo!** El script `install-deps.sh` detecta tu sistema operativo (macOS, Ubuntu, Fedora, Arch) e instala Allegro 5 automáticamente.

---

## Inicio Rápido por Sistema Operativo

### macOS

```bash
# 1. Instalar Allegro (solo una vez)
brew install allegro

# 2. Clonar y entrar al proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 3. Compilar y ejecutar
./build.sh run
```

**¡Eso es todo!** El juego debería iniciarse automáticamente.

---

### Windows

#### Método 1: Instalación Automática (Recomendado)

```cmd
# 1. Clonar el proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 2. Instalar dependencias automáticamente
scripts\install-deps.bat

# 3. Una vez instalado, compilar y ejecutar desde MSYS2 MINGW64:
make -f Makefile.unix
./SpaceInvaders
```

#### Método 2: Instalación Manual con MSYS2

```bash
# 1. Descargar e instalar MSYS2 desde: https://www.msys2.org/

# 2. Abrir "MSYS2 MINGW64" y ejecutar:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro make

# 3. Navegar al proyecto
cd /c/Users/TuUsuario/space-invaders-c

# 4. Compilar y ejecutar
./build.sh run
```

#### Método 2: Usando MinGW y CMD

```cmd
:: 1. Instalar MinGW desde: https://www.mingw-w64.org/

:: 2. Abrir CMD en la carpeta del proyecto

:: 3. Compilar y ejecutar
build.bat run
```

---

### Linux (Ubuntu/Debian)

```bash
# 1. Instalar dependencias
sudo apt update
sudo apt install build-essential liballegro5-dev

# 2. Clonar y entrar al proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 3. Compilar y ejecutar
./build.sh run
```

---

## Compilación Manual (Todos los sistemas)

Si los scripts no funcionan, puedes compilar manualmente:

### En macOS/Linux:

```bash
# Compilar
gcc -c src/main.c -I include $(pkg-config --cflags allegro-5) -o main.o
gcc -c src/game.c -I include $(pkg-config --cflags allegro-5) -o game.o
gcc -c src/bullet.c -I include $(pkg-config --cflags allegro-5) -o bullet.o
gcc -c src/ship.c -I include $(pkg-config --cflags allegro-5) -o ship.o
gcc -c src/martian.c -I include $(pkg-config --cflags allegro-5) -o martian.o
gcc -c src/object.c -I include $(pkg-config --cflags allegro-5) -o object.o

# Enlazar
gcc -o SpaceInvaders *.o $(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)

# Ejecutar
./SpaceInvaders
```

### En Windows (con MinGW):

```cmd
mingw32-make
SpaceInvaders.exe
```

---

## Controles del Juego

| Tecla | Acción |
|-------|--------|
| **←** | Mover izquierda |
| **→** | Mover derecha |
| **ESPACIO** | Disparar |
| **ESC** | Salir |

---

## Compilación desde Visual Studio Code

### 1. Abrir el proyecto en VSCode

```bash
code space-invaders-c
```

### 2. Compilar con atajos de teclado

- **macOS/Linux**: Presiona `Cmd+Shift+B` (macOS) o `Ctrl+Shift+B` (Linux)
- **Windows**: Presiona `Ctrl+Shift+B`

### 3. Ejecutar con Debug

- Presiona `F5` para compilar y ejecutar en modo debug
- Presiona `Ctrl+F5` para ejecutar sin debug

### 4. Tareas disponibles en VSCode

Presiona `Cmd+Shift+P` (macOS) o `Ctrl+Shift+P` (Windows/Linux) y escribe "Tasks: Run Task":

- **Build Space Invaders (macOS/Linux)** - Compila el proyecto
- **Build and Run (macOS/Linux)** - Compila y ejecuta
- **Clean Build Files** - Limpia archivos de compilación
- **Check Dependencies** - Verifica que Allegro esté instalado

---

## Solución de Problemas Comunes

### ❌ "allegro not found" o "pkg-config: command not found"

**macOS:**
```bash
brew install pkg-config allegro
```

**Linux:**
```bash
sudo apt install pkg-config liballegro5-dev
```

**Windows (MSYS2):**
```bash
pacman -S mingw-w64-x86_64-pkg-config mingw-w64-x86_64-allegro
```

---

### ❌ "Permission denied" al ejecutar en macOS/Linux

```bash
chmod +x build.sh
chmod +x SpaceInvaders
```

---

### ❌ El juego no muestra gráficos o dice "Error initializing game"

**Problema:** Las rutas de recursos no son correctas o estás ejecutando desde un directorio incorrecto.

**Solución:**

1. **Ejecuta siempre desde el directorio raíz:**
```bash
cd /ruta/completa/a/space-invaders-c
./SpaceInvaders
```

2. **Verifica que las rutas en `include/config.h` sean correctas:**

Las rutas deben ser relativas al directorio raíz (donde está el ejecutable):
```c
#define BACKGROUND_IMG_RSC "resources/images/background.bmp"  // ✅ Correcto
```

NO deben tener `../` al principio si el ejecutable está en el directorio raíz.

3. **Usa el script de verificación:**
```bash
scripts/test_resources.sh
```

---

### ❌ "undefined reference to..." al compilar

Falta enlazar alguna biblioteca de Allegro. Asegúrate de que el comando de enlace incluya:

```bash
-lallegro_monolith -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives
```

O en macOS/Linux con pkg-config:

```bash
$(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)
```

---

### ❌ En Windows: "mingw32-make: command not found"

**Opción 1:** Usa `make` en lugar de `mingw32-make`:
```cmd
make
```

**Opción 2:** Añade MinGW al PATH:
```cmd
set PATH=%PATH%;C:\MinGW\bin
```

**Opción 3:** Usa MSYS2 (recomendado):
- Descarga de: https://www.msys2.org/
- Instala GCC y Make:
```bash
pacman -S mingw-w64-x86_64-gcc make
```

---

## Verificar Instalación

Ejecuta estos comandos para verificar que todo está instalado correctamente:

### macOS/Linux:

```bash
# Verificar GCC
gcc --version

# Verificar Allegro
pkg-config --modversion allegro-5

# Verificar automáticamente todas las dependencias
make -f Makefile.unix check-deps
```

### Windows (MSYS2):

```bash
gcc --version
pacman -Qi mingw-w64-x86_64-allegro
```

---

## Próximos Pasos

Una vez que el juego funcione:

1. **Modifica la dificultad** editando `include/config.h`
2. **Añade nuevas funcionalidades** siguiendo la estructura modular
3. **Consulta el README.md completo** para información detallada sobre la arquitectura

---

## ¿Necesitas Ayuda?

- **Problemas técnicos**: [Abre un issue](https://github.com/RGiskard7/space-invaders-c/issues)
- **Documentación completa**: [Ver README.md](README.md)
- **Código fuente**: [GitHub Repository](https://github.com/RGiskard7/space-invaders-c)
