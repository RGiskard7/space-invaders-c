# Guia Rapida - Space Invaders

Arranca el juego en menos de 5 minutos.

---

## El camino mas corto

### macOS / Linux

```bash
scripts/install-deps.sh
scripts/build.sh run
```

### Windows

```cmd
scripts\install-deps.bat
scripts\build.bat run
```

---

## Controles

| Tecla        | Accion           |
|--------------|------------------|
| Left / Right | Mover nave       |
| Space        | Disparar         |
| P            | Pausa            |
| Enter        | Iniciar / Seguir |
| Escape       | Salir            |

### Al poner tus iniciales

| Tecla          | Accion               |
|----------------|----------------------|
| Up / Down      | Cambiar letra        |
| Left / Right   | Mover cursor         |
| Enter          | Guardar y reiniciar  |
| Escape         | Saltar y reiniciar   |

---

## Si algo falla

**"undefined reference" al compilar**  
Faltan las librerias de audio. Revisa que `allegro_audio-5` y `allegro_acodec-5` esten instaladas.

**No se ve nada**  
Ejecuta siempre desde la raiz del proyecto (`space-invaders-c/`).

**"Permission denied" en macOS/Linux**  
```bash
chmod +x SpaceInvaders
```

---

## Verificar que todo esta bien

```bash
gcc --version
pkg-config --modversion allegro-5
scripts/test_resources.sh
```
