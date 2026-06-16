#!/bin/bash

# Script de compilación para Space Invaders en macOS/Linux
# Autor: RGiskard7
# Uso: ./build.sh [opciones]

set -e  # Salir si hay errores

# Cambiar al directorio raíz del proyecto
cd "$(dirname "$0")/.." || exit 1

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para imprimir mensajes
print_info() {
    echo -e "${BLUE}ℹ ${NC}$1"
}

print_success() {
    echo -e "${GREEN}✅ ${NC}$1"
}

print_warning() {
    echo -e "${YELLOW}⚠️  ${NC}$1"
}

print_error() {
    echo -e "${RED}❌ ${NC}$1"
}

# Banner
echo -e "${BLUE}"
echo "═══════════════════════════════════════════════════"
echo "        Space Invaders - Build Script"
echo "═══════════════════════════════════════════════════"
echo -e "${NC}"

# Verificar dependencias
print_info "Verificando dependencias..."

if ! command -v gcc &> /dev/null; then
    print_error "GCC no está instalado"
    echo "  Instala GCC con:"
    echo "    macOS: xcode-select --install"
    echo "    Linux: sudo apt install build-essential"
    exit 1
fi
print_success "GCC encontrado: $(gcc --version | head -n1)"

if ! command -v pkg-config &> /dev/null; then
    print_error "pkg-config no está instalado"
    echo "  Instala pkg-config con:"
    echo "    macOS: brew install pkg-config"
    echo "    Linux: sudo apt install pkg-config"
    exit 1
fi
print_success "pkg-config encontrado"

if ! pkg-config --exists allegro-5; then
    print_error "Allegro 5 no está instalado"
    echo "  Instala Allegro 5 con:"
    echo "    macOS: brew install allegro"
    echo "    Linux: sudo apt install liballegro5-dev"
    exit 1
fi
ALLEGRO_VERSION=$(pkg-config --modversion allegro-5)
print_success "Allegro 5 encontrado: v${ALLEGRO_VERSION}"

# Limpiar archivos antiguos
if [ "$1" == "clean" ]; then
    print_info "Limpiando archivos anteriores..."
    rm -f *.o SpaceInvaders
    print_success "Limpieza completada"
    exit 0
fi

# Compilar
print_info "Compilando Space Invaders..."

if [ -f "Makefile.unix" ]; then
    make -f Makefile.unix "$@"
else
    print_warning "Makefile.unix no encontrado, compilando manualmente..."

    # Compilar archivos objeto
    gcc -c src/main.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o main.o
    gcc -c src/game.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o game.o
    gcc -c src/bullet.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o bullet.o
    gcc -c src/ship.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o ship.o
    gcc -c src/martian.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o martian.o
    gcc -c src/object.c -I include $(pkg-config --cflags allegro-5) -Wall -g -o object.o

    # Enlazar
    gcc -o SpaceInvaders main.o game.o bullet.o ship.o martian.o object.o \
        $(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5)

    print_success "Compilación completada"
fi

# Verificar que el ejecutable se creó
if [ -f "SpaceInvaders" ]; then
    print_success "Ejecutable creado correctamente: ./SpaceInvaders"

    # Dar permisos de ejecución
    chmod +x SpaceInvaders

    # Preguntar si ejecutar
    if [ "$1" == "run" ]; then
        print_info "Iniciando Space Invaders..."
        echo ""
        ./SpaceInvaders
    else
        echo ""
        print_info "Para ejecutar el juego, usa:"
        echo -e "  ${GREEN}./SpaceInvaders${NC}"
        echo ""
        print_info "O ejecuta:"
        echo -e "  ${GREEN}./build.sh run${NC}"
    fi
else
    print_error "La compilación falló"
    exit 1
fi

