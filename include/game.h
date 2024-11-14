#ifndef GAME_H
#define	GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "config.h"
#include "types.h"
#include "ship.h"
#include "martian.h"
#include "bullet.h"
#include "object.h"

typedef struct _game GAME;

/**
 * @brief Creates a new game instance.
 */
GAME *game_create();

/**
 * @brief Initializes the game with specified FPS.
 */
STATUS game_init(GAME *game, float FPS);

/**
 * @brief Destroys the game and frees resources.
 */
STATUS game_destroy(GAME *game);

/**
 * @brief Retrieves the game display.
 */
ALLEGRO_DISPLAY *game_get_screen(GAME *game);

/**
 * @brief Retrieves the game timer.
 */
ALLEGRO_TIMER *game_get_timer(GAME *game);

/**
 * @brief Retrieves the game's event queue.
 */
ALLEGRO_EVENT_QUEUE *game_get_ev_queue(GAME *game);

/**
 * @brief Retrieves the current game event.
 */
ALLEGRO_EVENT *game_get_event(GAME *game);

/**
 * @brief Sets a random enemy for shooting.
 */
STATUS game_set_rand_enemy(GAME *game, int lastrand);

/**
 * @brief Updates the game state.
 */
STATUS game_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key);

/**
 * @brief Renders the game to the display.
 */
STATUS game_render(GAME *game);

/**
 * @brief Checks if the game has ended.
 */
bool game_is_done(GAME *game);

#endif /* GAME_H */