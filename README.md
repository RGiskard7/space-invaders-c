# Space Invaders

<div align="center">
  <img src="https://github.com/user-attachments/assets/48a46d8a-0180-436b-8c95-7769712331ff" alt="Space Invaders" width="600"/>
</div

> **Quick Start (macOS/Linux)**
> ```bash
> scripts/install-deps.sh
> scripts/build.sh run
> ```

</div>

---

## Overview

Space Invaders is a faithful recreation of the classic 1978 arcade game, implemented in C using the Allegro 5 graphics library. The project demonstrates structured programming, dynamic memory management, collision detection, and 2D sprite rendering.

### Features

- Player-controlled spaceship with lateral movement and one-at-a-time shooting
- 55 alien invaders in a 11x5 grid formation with zigzag movement
- Progressive difficulty: aliens speed up as their numbers decrease
- Four destructible bunkers (damage persists between waves)
- Mystery UFO with random spawn and bonus points
- Multi-level progression with increasing difficulty
- Persistent high score table (top 5 scores with player initials)
- Authentic arcade sound effects (movement, shooting, explosions)
- Fully configurable via `config.h`

---

## Project Structure

```
space-invaders-c/
├── scripts/              # Automation scripts
│   ├── install-deps.sh   # Dependency installer (macOS/Linux)
│   ├── install-deps.bat  # Dependency installer (Windows)
│   ├── build.sh          # Build script (macOS/Linux)
│   ├── build.bat         # Build script (Windows)
│   └── test_resources.sh # Resource verification
├── include/              # Header files
│   ├── types.h           # Types and enumerations
│   ├── config.h          # Centralized configuration
│   ├── object.h          # Generic game objects
│   ├── bullet.h          # Projectile management
│   ├── bunker.h          # Shield/destructible objects
│   ├── ship.h            # Player ship
│   ├── martian.h         # Enemy aliens
│   └── game.h            # Game state management
├── src/                  # Source files
│   ├── main.c            # Entry point
│   ├── game.c            # Core game logic and main loop
│   ├── bullet.c          # Projectile implementation
│   ├── ship.c            # Player ship implementation
│   ├── martian.c         # Alien implementation
│   ├── object.c          # Generic object implementation
│   └── bunker.c          # Destructible bunker implementation
├── resources/            # Game assets
│   ├── images/           # Sprites and graphics (.bmp, .png)
│   ├── sounds/           # Sound effects (.wav)
│   └── fonts/            # Text fonts (.ttf)
├── Makefile              # Makefile (Windows/minimal)
├── Makefile.unix         # Makefile (macOS/Linux)
├── Makefile.windows      # Makefile (Windows/MSYS2)
└── README.md             # This file
```

---

## Requirements

- **C Compiler**: GCC (MinGW-w64 on Windows, GCC/Clang on macOS, build-essential on Linux)
- **Allegro 5**: Version 5.2 or later with audio support
- **Make**: Build tool (optional on Windows, use `mingw32-make`)
- **pkg-config**: Automatic library detection (macOS/Linux)

### Supported Platforms

- **Windows** 10/11 (x64) via MSYS2/MinGW or manual MinGW installation
- **macOS** 10.15+ (Catalina or later)
- **Linux** (Ubuntu, Debian, Fedora, Arch)

---

## Setup and Installation

### macOS

Install Homebrew if not already installed:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Then install dependencies:

```bash
./scripts/install-deps.sh
```

Or install manually:

```bash
brew install allegro gcc
```

Verify installation:

```bash
pkg-config --modversion allegro-5
```

### Linux

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential gcc liballegro5-dev liballegro-image-5.0-dev liballegro-audio-5.0-dev liballegro-acodec-5.0-dev pkg-config
```

**Fedora:**
```bash
sudo dnf install gcc make allegro5-devel allegro5 pkg-config
```

**Arch Linux:**
```bash
sudo pacman -S base-devel allegro pkg-config
```

### Windows

Install MSYS2 from https://www.msys2.org/. Open **MSYS2 MinGW-w64** and run:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-allegro mingw-w64-x86_64-pkg-config
```

Alternatively, use the bundled setup script (run in CMD or PowerShell as Administrator):

```cmd
scripts\install-deps.bat
```

This installs MinGW 14.1.0 to `C:\mingw64` and Allegro 5.2.9 to `C:\allegro-5.2.9.1-mingw-14.1.0`.

---

## Building and Running

### 1. Clone the Repository

```bash
git clone https://github.com/RGiskard7/space-invaders-c.git
cd space-invaders-c
```

### 2. Build the Project

**macOS/Linux:**
```bash
make -f Makefile.unix          # Build
make -f Makefile.unix run      # Build and run
make -f Makefile.unix clean    # Clean build artifacts
```

**Windows (MSYS2):**
```bash
make -f Makefile.windows          # Build
mingw32-make -f Makefile.unix     # Alternative
```

**Manual compilation (macOS/Linux):**
```bash
gcc -c src/main.c -I include $(pkg-config --cflags allegro-5) -g -o main.o
gcc -c src/game.c    -I include $(pkg-config --cflags allegro-5) -g -o game.o
gcc -c src/bullet.c  -I include $(pkg-config --cflags allegro-5) -g -o bullet.o
gcc -c src/ship.c    -I include $(pkg-config --cflags allegro-5) -g -o ship.o
gcc -c src/martian.c -I include $(pkg-config --cflags allegro-5) -g -o martian.o
gcc -c src/object.c  -I include $(pkg-config --cflags allegro-5) -g -o object.o
gcc -c src/bunker.c  -I include $(pkg-config --cflags allegro-5) -g -o bunker.o

gcc -o SpaceInvaders main.o game.o bullet.o ship.o martian.o object.o bunker.o \
    $(pkg-config --libs allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 \
                    allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5)
```

**Manual compilation (Windows/MinGW):**
```cmd
mingw32-make -f Makefile.unix
SpaceInvaders.exe
```

### 3. Launch the Game

**macOS/Linux:**
```bash
./SpaceInvaders
```

**Windows:**
```cmd
SpaceInvaders.exe
```

### 4. Visual Studio Code

The project is configured for VS Code debugging (`.vscode` directory):

- **F5**: Compile and launch with debugger
- **Ctrl+Shift+B / Cmd+Shift+B**: Build only

---

## Controls

| Key         | Action                          |
|-------------|---------------------------------|
| Left Arrow  | Move ship left                  |
| Right Arrow | Move ship right                 |
| Space       | Fire projectile                 |
| P           | Pause / Resume                  |
| Escape      | Quit game                       |
| Enter       | Confirm / Continue (Game Over)  |

---

## Game Mechanics

- **Player Ship**: Controlled by arrow keys. Fires one projectile at a time.
- **Aliens**: 55 invaders in a 11x5 grid. Movement pattern follows zigzag trajectory. Speed increases as aliens are eliminated.
- **Mystery UFO**: Randomly appears across the top of the screen for bonus points (50-300).
- **Bunkers**: Four destructible shields. Damage is persistent across waves.
- **Levels**: Complete a wave to advance. Aliens start lower each level, and shooting/movement frequency increases.
- **Scoring**: Top row = 30 points, middle = 20, bottom = 10. UFO = random bonus.
- **Lives**: 3 starting lives. Game ends when all lives are lost or aliens reach the bottom.
- **High Score Table**: Top 5 persistent scores with player initials (saved to `highscores.dat`).

---

## Game Configuration

Edit `include/config.h` to customize gameplay. Key constants:

```c
// Display
#define DISPLAY_HEIGHT 600
#define DISPLAY_WIDTH  600

// Player ship
#define SHIP_SPEED           6
#define SHIP_BULLET_SPEED   15
#define SHIP_LIFE            3

// Alien configuration
#define MAX_ENEMIES         55
#define NUM_ENEMY_X         11
#define NUM_ENEMY_Y          5
#define MART_BASE_SPEED      5
#define MART_BULLET_SPEED    5

// Destructible bunkers
#define NUM_BUNKERS          4
#define BUNKER_PARTS         5

// High scores
#define MAX_TOP_SCORES       5

// God mode (invincibility): 0 = off, 1 = on
#define GOD_MODE             0
```

After changing `config.h`, rebuild the project.

---

## Troubleshooting

### Allegro Not Found (macOS/Linux)

```bash
pkg-config --modversion allegro-5
# If it fails:
brew reinstall allegro    # macOS
sudo apt install liballegro5-dev  # Linux
```

### Undefined Reference to Audio Symbols

Ensure `allegro_audio` and `allegro_acodec` are linked. Use the provided build scripts, which include all required libraries automatically.

### Error: "Cannot find -lallegro_monolith" (Windows)

The static MinGW build on Windows uses monoithic linking. Solutions:

1. Copy `allegro_monolith-5.2.dll` alongside the executable, or
2. Use MSYS2 which provides proper pkg-config support.

### Game Opens but Graphics Appear Incorrect

The game must be launched from the project root directory, where the `resources/` folder is accessible:

```bash
cd space-invaders-c
./SpaceInvaders
```

Verify resources are accessible:

```bash
./scripts/test_resources.sh
```

### "Permission Denied" on macOS

```bash
chmod +x SpaceInvaders
./SpaceInvaders
```

### macOS Retina Display

On Retina displays, the game window will appear smaller due to macOS's display scaling. To increase window size, edit `DISPLAY_HEIGHT` and `DISPLAY_WIDTH` in `include/config.h` (e.g., 900 or 1200) and rebuild.

---

## Development

### Debug Build

```bash
make -f Makefile.unix debug
```

### Memory Analysis

```bash
valgrind --leak-check=full --show-leak-kinds=all ./SpaceInvaders
```

### Commit Convention

Follow the Conventional Commits specification:

```
type(scope): description

- Detail 1
- Detail 2
```

Examples:
- `feat(ship): add temporary shield power-up`
- `fix(collision): correct edge collision detection`
- `docs(readme): update macOS installation instructions`

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Author

**Edu Diaz (RGiskard7)**

- GitHub: [@RGiskard7](https://github.com/RGiskard7)
- Repository: [space-invaders-c](https://github.com/RGiskard7/space-invaders-c)
- Bugs & Feature Requests: [GitHub Issues](https://github.com/RGiskard7/space-invaders-c/issues)
