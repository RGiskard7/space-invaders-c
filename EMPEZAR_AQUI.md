# 🚀 EMPEZAR AQUI - Space Invaders

Elige tu sistema operativo y sigue SOLO esas instrucciones:

---

## 🍎 macOS (Apple)

### ✅ OPCION 1: Super Rapida (2 comandos)

```bash
./scripts/install-deps.sh
./scripts/build.sh run
```

**Eso es todo.** Si funciona, i jugar!

### ⚠️ Si da error, OPCION 2:

```bash
# 1. Instalar dependencias
brew install allegro gcc pkg-config

# 2. Si no te funciona el install-deps.sh, hazlo manual:
./scripts/build.sh run
```

---

## 🐧 Linux

### Ubuntu/Debian
```bash
sudo apt install build-essential gcc liballegro5-dev liballegro-image-5.0-dev liballegro-audio-5.0-dev liballegro-acodec-5.0-dev pkg-config
make -f Makefile.unix && ./SpaceInvaders
```

### Fedora
```bash
sudo dnf install gcc make allegro5-devel pkg-config
make -f Makefile.unix && ./SpaceInvaders
```

### Arch
```bash
sudo pacman -S base-devel allegro pkg-config
make -f Makefile.unix && ./SpaceInvaders
```

---

## 🪟 Windows

### ✅ METODO: MSYS2/MinGW (Recomendado)

**Pasos:**

1. **Instala dependencias (desde MSYS2 MinGW-w64):**
   ```cmd
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro mingw-w64-x86_64-pkg-config
   ```

2. **Compila y ejecuta:**
   ```cmd
   mingw32-make -f Makefile.unix
   SpaceInvaders.exe
   ```

### ⚠️ Si usas MinGW manual:

1. Descarga **MinGW 14.1.0** y extralo en `C:\mingw64`
2. Asegurate que `C:\mingw64\bin` esté en tu PATH
3. Ejecuta:
   ```cmd
   scripts\build.bat run
   ```

---

## ❓ Problemas Comunes

### "No se encuentra gcc"
- **macOS:** Instala Xcode Command Line Tools: `xcode-select --install`
- **Windows:** Instala MSYS2 desde msys2.org o TDM-GCC

### "No se encuentra Allegro"
- **macOS:** `brew install allegro`
- **Linux:** `sudo apt install liballegro5-dev` o equivalente
- **Windows:** Usa `pacman -S mingw-w64-x86_64-allegro` (MSYS2)

### "Error inicializando juego"
- Ejecuta el juego desde la carpeta raiz del proyecto
- Verifica que exista la carpeta `resources`

### "Permission denied" (macOS)
```bash
chmod +x SpaceInvaders ./scripts/*.sh
```

**Mas ayuda?** Lee `README.md` para detalles tecnicos.
