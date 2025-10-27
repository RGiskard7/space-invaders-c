#!/bin/bash

# Script para verificar que los recursos del juego son accesibles

echo "🔍 Verificando recursos del juego..."
echo ""

RESOURCES_OK=true

# Lista de recursos necesarios
declare -a RESOURCES=(
    "resources/images/background.bmp"
    "resources/images/frame.bmp"
    "resources/images/ship.bmp"
    "resources/images/martians.bmp"
    "resources/images/ship_bullet.bmp"
    "resources/images/martian_bullet.bmp"
    "resources/images/martian_explosion.bmp"
    "resources/fonts/space_invaders.ttf"
)

# Verificar cada recurso
for resource in "${RESOURCES[@]}"; do
    if [ -f "$resource" ]; then
        echo "✅ $resource"
    else
        echo "❌ FALTA: $resource"
        RESOURCES_OK=false
    fi
done

echo ""

if [ "$RESOURCES_OK" = true ]; then
    echo "✅ Todos los recursos están disponibles"
    echo ""
    echo "Las rutas en config.h son correctas. El juego debería funcionar."
    echo "Para probarlo con interfaz gráfica, ejecuta:"
    echo "  ./SpaceInvaders"
    exit 0
else
    echo "❌ Faltan recursos. Verifica las rutas."
    exit 1
fi

