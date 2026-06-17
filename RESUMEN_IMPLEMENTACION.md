# Resumen de Implementacion - Space Invaders

## Codigo

| Archivo | Lineas | Que hace |
|---------|--------|----------|
| `src/main.c` | 314 | Entrada, inicializa Allegro, bucle principal |
| `src/game.c` | ~2400 | Logica central, estados, colisiones, render, records |
| `src/ship.c` | 610 | Nave del jugador: movimiento, disparo, balas |
| `src/martian.c` | 677 | Marcianos: formacion, disparo, animacion |
| `src/bullet.c` | 352 | Proyectiles: creacion, movimiento, colision AABB |
| `src/bunker.c` | 249 | Escudos destructibles con estados de dano |
| `src/object.c` | 340 | Objetos genericos: explosiones y OVNI |
| `include/config.h` | 148 | Constantes, rutas y parametros del juego |

## Arquitectura

- Structs opacos con getters/setters
- Configuracion centralizada en `config.h`
- Maquina de 5 estados: titulo, jugando, game over, oleada superada, entrada de iniciales
- Recursos creados y destruidos explicitamente, en orden correcto

## Fidelidad arcade

- Pantalla de titulo con tabla de records ciclando
- Solo los marcianos de primera fila disparan
- Dificultad por oleada: bajan una fila (max 6), +10% velocidad, mas disparos
- Velocidad exponencial conforme quedan menos enemigos
- Pausa breve al empezar cada oleada (no disparan)
- 4 bunkers de 5 partes con 3 estados de dano cada una
- OVNI con sprite embebido en codigo, timer de ~25s, puntua 50/100/150/300
- Vida extra a los 1500 puntos con sonido
- Entrada de 3 iniciales al morir si entras en el top 5
- Top 5 persistente en `highscores.dat`
- Sonido de marcha de 4 pasos que acelera con menos enemigos
- Explosion de la nave con frames de invulnerabilidad

## Sistema de compilacion

- `Makefile` (Windows/MinGW)
- `Makefile.unix` (macOS/Linux con pkg-config)
- `Makefile.windows` (MSYS2 con pkg-config)
- `scripts/build.sh` / `scripts/build.bat`
- `scripts/install-deps.sh` / `scripts/install-deps.bat`

## Constantes principales (config.h)

| Constante | Valor | Descripcion |
|-----------|-------|-------------|
| `DISPLAY_WIDTH/HEIGHT` | 600 | Tamano de ventana |
| `MAX_ENEMIES` | 55 | Total marcianos (11x5) |
| `SHIP_LIFE` | 3 | Vidas iniciales |
| `EXTRA_LIFE_SCORE` | 1500 | Puntos para vida extra |
| `UFO_EMBEDDED` | 1 | Sprite OVNI embebido (0 = cargar PNG) |
| `UFO_TIMER` | 1 | Spawn por timer (0 = aleatorio) |
| `MART_MOVE_TIMER` | 40 | Intervalo base de movimiento |
| `MART_SHOOT_FREQ` | 90 | Intervalo base de disparo |
| `GOD_MODE` | 0 | Modo invencible |
