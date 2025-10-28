# 🚀 CÓMO EMPEZAR - Space Invaders

**Elige tu sistema operativo y sigue SOLO esas instrucciones:**

---

## 🍎 macOS (Apple)

### ✅ OPCIÓN 1: Super Rápida (1 comando)

```bash
scripts/install-deps.sh && scripts/build.sh run
```

**Eso es todo.** Si funciona, ¡a jugar!

### ⚠️ Si da error, OPCIÓN 2:

```bash
# 1. Instalar dependencias
scripts/install-deps.sh

# 2. Si falla, instalar manualmente:
brew install allegro
brew install gcc

# 3. Compilar y ejecutar
scripts/build.sh run
```

---

## 🪟 Windows

### ✅ MÉTODO RECOMENDADO: MSYS2

**Pasos:**

1. **Instala MSYS2** desde: https://www.msys2.org/
   - Descarga el instalador
   - Instala en C:\msys64 (por defecto)

2. **Abre MSYS2 MINGW64** y ejecuta:
   ```bash
   pacman -Sy
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro make
   ```

3. **Compila y ejecuta** desde MSYS2 MINGW64:
   ```bash
   cd /c/ruta/a/tu/proyecto/space-invaders-c
   make -f Makefile.windows
   ./SpaceInvaders.exe
   ```

**O desde CMD de Windows:**
1. Ejecuta: `scripts\build.bat`
2. Si falla, lee las instrucciones que muestra

### ⚠️ Si MSYS2 da problemas:

**Opción Alternativa:**

1. Descarga Allegro desde aquí: https://github.com/liballeg/allegro5/releases
2. Busca: `allegro-5.2.9.1-mingw-14.1.0.zip`
3. Descárgalo y descomprime en `C:\allegro-5.2.9.1-mingw-14.1.0`
4. Ejecuta:
   ```
   mingw32-make
   SpaceInvaders.exe
   ```

---

## 🐧 Linux

```bash
# Ubuntu/Debian
sudo apt install gcc liballegro5-dev make
make -f Makefile.unix && ./SpaceInvaders

# Fedora
sudo dnf install gcc allegro5-devel make
make -f Makefile.unix && ./SpaceInvaders
```

---

## ❓ Problemas Comunes

### "No se encuentra gcc"
- **macOS:** Instala Xcode Command Line Tools: `xcode-select --install`
- **Windows:** Instala MSYS2 desde msys2.org o TDM-GCC

### "No se encuentra Allegro"
- **macOS:** `brew install allegro`
- **Linux:** `sudo apt install liballegro5-dev` o equivalente
- **Windows:** Usa `scripts\install-deps.bat`

### "Error inicializando juego"
- Ejecuta el juego desde la carpeta raíz del proyecto
- Verifica que exista la carpeta `resources`

---

## 🎮 Controles

- **← →** Mover nave
- **ESPACIO** Disparar
- **ESC** Salir

---

**¿Más ayuda?** Lee `README.md` para detalles técnicos.

