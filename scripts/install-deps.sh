#!/bin/bash

# Script de instalación automática de dependencias para Space Invaders
# Soporta: macOS (Homebrew), Ubuntu/Debian, Fedora, Arch Linux
# Autor: RGiskard7

set -e

# Cambiar al directorio raíz del proyecto
cd "$(dirname "$0")/.." || exit 1

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

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

echo -e "${BLUE}"
echo "═══════════════════════════════════════════════════"
echo "    Space Invaders - Instalador de Dependencias"
echo "═══════════════════════════════════════════════════"
echo -e "${NC}"

# Detectar sistema operativo
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
    print_info "Sistema operativo detectado: macOS"
elif [[ -f /etc/os-release ]]; then
    . /etc/os-release
    OS=$ID
    print_info "Sistema operativo detectado: $NAME"
else
    print_error "No se pudo detectar el sistema operativo"
    exit 1
fi

# Función de instalación para macOS
install_macos() {
    print_info "Instalando dependencias para macOS..."

    # Verificar si Homebrew está instalado
    if ! command -v brew &> /dev/null; then
        print_warning "Homebrew no está instalado"
        echo "¿Deseas instalar Homebrew? (s/n)"
        read -r response
        if [[ "$response" =~ ^[Ss]$ ]]; then
            print_info "Instalando Homebrew..."
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        else
            print_error "Homebrew es necesario para instalar las dependencias"
            exit 1
        fi
    fi

    print_info "Actualizando Homebrew..."
    brew update

    print_info "Instalando Allegro 5..."
    brew install allegro

    print_info "Instalando pkg-config (si no está instalado)..."
    brew install pkg-config || true

    print_success "Dependencias instaladas correctamente en macOS"
}

# Función de instalación para Ubuntu/Debian
install_ubuntu() {
    print_info "Instalando dependencias para Ubuntu/Debian..."

    print_info "Actualizando lista de paquetes..."
    sudo apt update

    print_info "Instalando herramientas de compilación..."
    sudo apt install -y build-essential

    print_info "Instalando Allegro 5..."
    sudo apt install -y liballegro5-dev liballegro5.2

    print_info "Instalando pkg-config..."
    sudo apt install -y pkg-config

    print_success "Dependencias instaladas correctamente en Ubuntu/Debian"
}

# Función de instalación para Fedora
install_fedora() {
    print_info "Instalando dependencias para Fedora..."

    print_info "Instalando herramientas de compilación..."
    sudo dnf install -y gcc make

    print_info "Instalando Allegro 5..."
    sudo dnf install -y allegro5-devel allegro5

    print_info "Instalando pkg-config..."
    sudo dnf install -y pkg-config

    print_success "Dependencias instaladas correctamente en Fedora"
}

# Función de instalación para Arch Linux
install_arch() {
    print_info "Instalando dependencias para Arch Linux..."

    print_info "Instalando herramientas de compilación..."
    sudo pacman -S --needed --noconfirm base-devel

    print_info "Instalando Allegro 5..."
    sudo pacman -S --needed --noconfirm allegro

    print_info "Instalando pkg-config..."
    sudo pacman -S --needed --noconfirm pkg-config

    print_success "Dependencias instaladas correctamente en Arch Linux"
}

# Instalar según el sistema operativo
case "$OS" in
    macos)
        install_macos
        ;;
    ubuntu|debian)
        install_ubuntu
        ;;
    fedora)
        install_fedora
        ;;
    arch|manjaro)
        install_arch
        ;;
    *)
        print_error "Sistema operativo no soportado: $OS"
        echo ""
        print_info "Instala manualmente las siguientes dependencias:"
        echo "  - GCC (compilador de C)"
        echo "  - Allegro 5 (biblioteca gráfica)"
        echo "  - pkg-config (herramienta de configuración)"
        exit 1
        ;;
esac

# Verificar instalación
echo ""
print_info "Verificando instalación..."

if command -v gcc &> /dev/null; then
    print_success "GCC: $(gcc --version | head -n1)"
else
    print_error "GCC no se instaló correctamente"
    exit 1
fi

if command -v pkg-config &> /dev/null; then
    print_success "pkg-config instalado"
else
    print_error "pkg-config no se instaló correctamente"
    exit 1
fi

if pkg-config --exists allegro-5; then
    ALLEGRO_VERSION=$(pkg-config --modversion allegro-5)
    print_success "Allegro 5 v${ALLEGRO_VERSION} instalado"
else
    print_error "Allegro 5 no se instaló correctamente"
    exit 1
fi

echo ""
print_success "¡Todas las dependencias se instalaron correctamente!"
echo ""
print_info "Ahora puedes compilar el juego con:"
echo -e "  ${GREEN}./build.sh${NC}"
echo ""
print_info "O ejecutar directamente:"
echo -e "  ${GREEN}./build.sh run${NC}"

