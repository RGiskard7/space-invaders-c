#!/bin/bash

# Script para verificar que los recursos del juego son accesibles

# Cambiar al directorio raiz del proyecto
cd "$(dirname "$0")/.." || exit 1

echo "🔍 Verificando recursos del juego..."
echo ""

RESOURCES_OK=true

# Lista de recursos necesarios (imagenes)
declare -a IMAGES=(
    "resources/images/background.bmp"
    "resources/images/frame.bmp"
    "resources/images/ship.bmp"
    "resources/images/martians.bmp"
    "resources/images/ship_bullet.bmp"
    "resources/images/martian_bullet.bmp"
    "resources/images/martian_explosion.bmp"
    "resources/images/escudos.bmp"
    "resources/images/ovni.png"
)

# Lista de sonidos necesarios
declare -a SOUNDS=(
    "resources/sounds/shoot.wav"
    "resources/sounds/invaderkilled.wav"
    "resources/sounds/shipexplosion.wav"
    "resources/sounds/mysteryentered.wav"
    "resources/sounds/mysterykilled.wav"
    "resources/sounds/0.wav"
    "resources/sounds/1.wav"
    "resources/sounds/2.wav"
    "resources/sounds/3.wav"
)

# Lista de fuentes
declare -a FONTS=(
    "resources/fonts/space_invaders.ttf"
)

# Verificar imagenes
echo "Imagens:"
for resource in "${IMAGES[@]}"; do
    if [ -f "$resource" ]; then
        echo "  ✅ $resource"
    else
        echo "  ❌ FALTA: $resource"
        RESOURCES_OK=false
    fi
done

# Verificar sonidos
echo ""
echo "Sonidos:"
for resource in "${SOUNDS[@]}"; do
    if [ -f "$resource" ]; then
        echo "  ✅ $resource"
    else
        echo "  ⚠️  NO ENCONTRADO: $resource (no critico)"
    fi
done

# Verificar fuentes
echo ""
echo "Fuentes:"
for resource in "${FONTS[@]}"; do
    if [ -f "$resource" ]; then
        echo "  ✅ $resource"
    else
        echo "  ❌ FALTA: $resource"
        RESOURCES_OK=false
    fi
done

echo ""

if [ "$RESOURCES_OK" = true ]; then
    echo "✅ Todos los recursos criticos están disponibles"
    echo ""
    echo "Las rutas en config.h son correctas. El juego deberia funcionar."
    echo "Para probarlo con interfaz grafica, ejecuta:"
    echo "  ./SpaceInvaders"
    exit 0
else
    echo "❌ Faltan recursos criticos. Verifica las rutas."
    exit 1
fi
