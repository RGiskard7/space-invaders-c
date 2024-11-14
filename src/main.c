/**
 * @file main.c
 * @brief Main entry point for the Space Invaders game.
 *
 * This file contains the main function and supporting initialization,
 * configuration, and cleanup functions required to run the game.
 * It sets up Allegro, initializes game resources, handles the main game loop,
 * and processes input and rendering.
 *
 * Usage:
 * Compile and run the program. The game window will open, allowing the player
 * to control a spaceship and battle enemy invaders.
 *
 * Allegro Components:
 * - Primitives for graphics rendering
 * - Keyboard input
 * - Font and TTF for text display
 * - Image loading and bitmap handling
 *
 * Dependencies:
 * - Allegro 5 libraries
 *
 * Author: RGiskard7
 * Date: 13/11/2024
 * Version: 1.0
 */

#include "game.h"

/**
 * @brief Structure to store initialization flags for Allegro components.
 *
 * This structure keeps track of which Allegro modules have been successfully
 * initialized, allowing for proper cleanup if an error occurs.
 */
typedef struct {
    bool is_primitives_initialized;   ///< Flag for Allegro Primitives Addon
    bool is_keyboard_initialized;     ///< Flag for Keyboard Installation
    bool is_font_initialized;         ///< Flag for Allegro Font Addon
    bool is_ttf_initialized;          ///< Flag for Allegro TTF Addon
    bool is_image_initialized;        ///< Flag for Allegro Image Addon
} Flags;

/**
 * @brief Cleans up allocated resources and shuts down initialized Allegro components.
 *
 * @param flags Pointer to Flags structure, indicating initialized components.
 * @param game Pointer to GAME instance, which will be destroyed if not NULL.
 */
void clean_up(Flags *flags, GAME *game);

/**
 * @brief Registers all event sources used in the game.
 *
 * Registers the timer, display, and keyboard event sources to the event queue.
 *
 * @param game Pointer to the GAME instance.
 */
void register_event_sources(GAME *game);

/**
 * @brief Configures window positioning and title.
 *
 * Centers the game window on the screen and sets the window title.
 *
 * @param game Pointer to the GAME instance.
 */
void windows_configuration(GAME *game);

/**
 * @brief Initializes Allegro and its addons.
 *
 * Sets up the core Allegro library and its addons for primitives, fonts, TTF, 
 * images, and keyboard handling. Tracks initialization status in Flags for safe cleanup.
 *
 * @param flags Pointer to Flags structure to update initialization status.
 * @return true if all initializations are successful, false otherwise.
 */
bool init_allegro(Flags *flags);

/**
 * @brief Main entry point for the game.
 *
 * Initializes Allegro, creates the game instance, and starts the main game loop.
 * Handles cleanup in case of initialization errors.
 *
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise.
 */
int main() {
    GAME *game = NULL; // Game instance
    ALLEGRO_KEYBOARD_STATE key; // Stores the state of pressed keys
    Flags flags = {false, false, false};

    if (!init_allegro(&flags)) {
        clean_up(&flags, NULL);
        return EXIT_FAILURE;
    }

    game = game_create(); //Creacion del juego
    if (!game) {
        clean_up(&flags, NULL);
        fprintf(stderr, "Error creating game instance.\n");
        return (EXIT_FAILURE);
    }

    if (game_init(game, 30.0) == ERROR) {
        clean_up(&flags, game);
        fprintf(stderr, "Error initializing game.\n");
        return (EXIT_FAILURE);
    }

    register_event_sources(game);

    srand(time(NULL));
    game_set_rand_enemy(game, rand() % MAX_ENEMIES);
    al_start_timer(game_get_timer(game)); // Start the game timer

    windows_configuration(game);

    fprintf(stdout, "Starting main game loop.\n");

    while (game_is_done(game) != true) {
        al_wait_for_event(game_get_ev_queue(game), game_get_event(game)); // Wait for events
        al_get_keyboard_state(&key);

        if (game_update(game, &key) == ERROR) {
            clean_up(&flags, game);
            fprintf(stderr, "Error during update.\n");
            return (EXIT_FAILURE);
        }

        if (game_render(game) == ERROR) {
            clean_up(&flags, game);
            fprintf(stderr, "Error rendering.\n");
            return (EXIT_FAILURE);
        }
    }

    return (EXIT_SUCCESS);
}

/**
 * @brief Initializes Allegro and its required addons.
 *
 * Initializes core Allegro and modules for primitive drawing, keyboard input, 
 * font handling, TTF, and image loading.
 *
 * @param flags Pointer to Flags structure to mark successful initializations.
 * @return true if all modules initialized successfully, false otherwise.
 */
bool init_allegro(Flags *flags) {
    if (!al_init()) {
        fprintf(stderr, "Error initializing Allegro.\n");
        return false;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Error initializing Allegro Primitives Addon.\n");
        return false;
    }
    flags->is_primitives_initialized = true;

    if (!al_install_keyboard()) {
        fprintf(stderr, "Error installing keyboard.\n");
        return false;
    }
    flags->is_keyboard_initialized = true;

    if (!al_init_font_addon()) {
        fprintf(stderr, "Error initializing Allegro Font Addon.\n");
        return false;
    }
    flags->is_font_initialized = true;

    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Error initializing Allegro TTF Addon.\n");
        return false;
    }
    flags->is_ttf_initialized = true;

    if (!al_init_image_addon()) {
        fprintf(stderr, "Error initializing Allegro Image Addon.\n");
        return false;
    }
    flags->is_image_initialized = true;

    return true;
}

/**
 * @brief Registers event sources to the event queue.
 *
 * Registers the timer, display, and keyboard events to ensure they can be 
 * detected in the game loop.
 *
 * @param game Pointer to the GAME instance.
 */
void register_event_sources(GAME *game) {
    al_register_event_source(game_get_ev_queue(game), al_get_timer_event_source(game_get_timer(game))); //Registrar en la pila todos los eventos de tiempo
    al_register_event_source(game_get_ev_queue(game), al_get_display_event_source(game_get_screen(game))); //Registrar en la pila todos los eventos de pantalla
    al_register_event_source(game_get_ev_queue(game), al_get_keyboard_event_source()); //Registrar en la pila todos los eventos del teclado

    return;
}

/**
 * @brief Configures the game window position and title.
 *
 * Centers the window on the main display and sets the window title to "Space Invaders."
 *
 * @param game Pointer to the GAME instance.
 */
void windows_configuration(GAME *game) {
    ALLEGRO_MONITOR_INFO monitor_info;
    int monitor_width, monitor_height;
    int window_pos_x, window_pos_y;

    al_get_monitor_info(0, &monitor_info); // Obtener las dimensiones del monitor principal

    monitor_width = monitor_info.x2 - monitor_info.x1;
    monitor_height = monitor_info.y2 - monitor_info.y1;

    window_pos_x = (monitor_width - DISPLAY_WIDTH) / 2;
    window_pos_y = (monitor_height - DISPLAY_HEIGHT) / 2;

    al_set_window_position(game_get_screen(game), window_pos_x, window_pos_y); //Posicionar la pantalla creada
    al_set_window_title(game_get_screen(game), "Space Invaders");
    
    return;
}

/**
 * @brief Cleans up allocated resources and shuts down initialized Allegro components.
 *
 * Destroys the game instance and shuts down Allegro modules based on initialization flags.
 *
 * @param flags Pointer to Flags structure indicating initialized modules.
 * @param game Pointer to GAME instance to be destroyed, if not NULL.
 */
void clean_up(Flags *flags, GAME *game) {
    if (game) {
        game_destroy(game);
    }

    if (flags->is_image_initialized) {
        al_shutdown_image_addon();
    }

    if (flags->is_ttf_initialized) {
        al_shutdown_ttf_addon();
    }

    if (flags->is_font_initialized) {
        al_shutdown_font_addon();
    }

    if (flags->is_keyboard_initialized) {
        al_uninstall_keyboard();
    }

    if (flags->is_primitives_initialized) {
        al_shutdown_primitives_addon();
    }

    return;
}