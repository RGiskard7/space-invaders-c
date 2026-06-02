# Guia Rapida de Inicio - Space Invaders

Esta guia te ayudara a compilar y ejecutar el juego en **menos de 5 minutos**.

---

## El Camino MAS Rapido (Todos los Sistemas)

### macOS / Linux

```bash
# 1. Instalar dependencias automaticamente
./scripts/install-deps.sh

# 2. Compilar y ejecutar
./scripts/build.sh run
```

### Windows (MSYS2/MinGW)

```cmd
:: 1. Instala dependencias (una vez, en MSYS2)
:: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro mingw-w64-x86_64-pkg-config

:: 2. Clona y entra al proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

:: 3. Compila y ejecuta
mingw32-make -f Makefile.unix
SpaceInvaders.exe
```

---

## Inicio Rapido por Sistema Operativo

### macOS

```bash
# 1. Instalar Allegro (solo una vez)
./scripts/install-deps.sh

# 2. Clonar y entrar al proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 3. Compilar y ejecutar
./scripts/build.sh run
```

### Linux (Ubuntu/Debian)

```bash
# 1. Instalar dependencias
sudo apt update && sudo apt install -y build-essential gcc liballegro5-dev liballegro-image-5.0-dev liballegro-audio-5.0-dev liballegro-acodec-5.0-dev pkg-config

# 2. Clonar y entrar al proyecto
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c

# 3. Compilar y ejecutar
make -f Makefile.unix && ./SpaceInvaders
```

---

## Compilacion Manual (Todos los sistemas)

Si los scripts no funcionan, puedes compilar manualmente:

### En macOS/Linux:

```bash
# Compilar
gcc -c src/main.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o main.o
gcc -c src/game.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o game.o
gcc -c src/bullet.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o bullet.o
gcc -c src/ship.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o ship.o
gcc -c src/martian.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o martian.o
gcc -c src/object.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o object.o
gcc -c src/bunker.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o bunker.o

# Enlazar (con todas las librerias necesarias, incluyendo audio)
gcc -o SpaceInvaders main.o game.o bullet.o ship.o martian.o object.o bunker.o \
    $(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5)

# Ejecutar
./SpaceInvaders
```

### En Windows (con MinGW):

```cmd
mingw32-make -f Makefile.unix
SpaceInvaders.exe
```

---

## Controles del Juego

| Tecla | Accion |
| ----- | ------ |
| **←** | Mover izquierda |
| **→** | Mover derecha |
| **ESPACIO** | Disparar |
| **ESC** | Salir |
| **P** | Pausar |

---

## Solucion de Problemas

### "undefined reference to..." al compilar

Faltan las librerias de audio de Allegro. Asegurate de incluir:
- `allegro_audio-5`
- `allegro_acodec-5`

Con pkg-config:
```bash
$(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5)
```

### "Permission denied" al ejecutar en macOS/Linux

```bash
chmod +x scripts/*..sh SpaceInvaders
```

### El juego no muestra graficos

- Ejecuta siempre desde el directorio raiz: `cd space-invaders-c && ./SpaceInvaders`
- Verifica que exista la carpeta `resources`

---

## Verificar Instalacion

```bash
# Verificar GCC
gcc --version

# Verificar Allegro
pkg-config --modversion allegro-5

# Verificar recursos
./scripts/test_resources.sh
```

---

## Proximos Pasos

Una vez que el juego funcione:

1. **Modifica la dificultad** editando `include/config.h`
2. **Añade nuevas funcionalidades** siguiendo la estructura modular
3. **Consulta el README.md completo** para informacion detallada

---

## Necesitas Ayuda?

- **Problemas tecnicos**: [Abre un issue](https://github.com/RGiskard7/space-invaders-c/issues)
- **Documentacion completa**: [Ver README.md](README.md)
- **Codigo fuente**: [GitHub Repository](https://github.com/RGiskard7/space-invaders-c)
