#!/bin/bash

# Empaqueta Space Invaders en una carpeta portable (dist) para macOS/Linux.
# A diferencia de Windows, aqui Allegro es una libreria del sistema, asi que
# no hay ningun .dll/.so que copiar: la carpeta lleva el binario y los recursos,
# y la maquina destino solo necesita tener Allegro 5 instalado.
# Autor: RGiskard7

set -e

cd "$(dirname "$0")/.." || exit 1

DIST="dist"

echo "═══════════════════════════════════════════════════"
echo "        Empaquetando Space Invaders (dist)"
echo "═══════════════════════════════════════════════════"

# 1. Compilar usando el script de build
bash scripts/build.sh

# 2. Preparar carpeta limpia
rm -rf "$DIST"
mkdir -p "$DIST"

# 3. Copiar binario y todos los recursos del juego
cp SpaceInvaders "$DIST/"
cp -r resources "$DIST/resources"

echo ""
echo "✅ Carpeta portable lista en: $DIST"
echo "La maquina destino necesita Allegro 5 instalado (brew/apt)."
