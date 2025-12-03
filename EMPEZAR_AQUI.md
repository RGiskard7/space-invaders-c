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

### ✅ MÉTODO RECOMENDADO: Script Automático

**Pasos:**

1. **Ejecuta el instalador** (como Administrador):
   ```cmd
   scripts\install-deps.bat
   ```
   Esto instalará MinGW y Allegro en `C:\mingw64` y `C:\allegro-5.2.9.1-mingw-14.1.0`.

2. **Compila y ejecuta**:
   ```cmd
   scripts\build.bat run
   ```

### ⚠️ Instalación Manual:

1. Descarga **MinGW 14.1.0** (WinLibs) y extráelo en `C:\mingw64`.
2. Descarga **Allegro 5.2.9** y extráelo en `C:\allegro-5.2.9.1-mingw-14.1.0`.
3. Ejecuta:
   ```cmd
   scripts\build.bat run
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

