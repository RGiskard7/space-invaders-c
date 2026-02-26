/**
 * @file bunker.h
 * @brief Declaration of the Bunker structure and its associated functions.
 *
 * This header defines the structure and functions to manage individual bunker
 * parts in the Space Invaders game. Each bunker is composed of several parts,
 * each of which can take a fixed number of hits before being destroyed.
 *
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#ifndef BUNKER_H
#define BUNKER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"

/**
 * @brief Structure representing a single part of a bunker.
 *
 * Bunkers are composed of multiple parts, each rendered as a region of
 * the bunker sprite sheet. Each part tracks its own damage state.
 */
typedef struct _bunker BUNKER;

/**
 * @brief Creates a new bunker part with the specified parameters.
 *
 * @param bitmap Shared bitmap sprite sheet for all bunker parts.
 * @param source_x Initial x-coordinate in the sprite sheet (damage frame).
 * @param source_y Y-coordinate in the sprite sheet (part type/shape).
 * @param width Width of the bunker part.
 * @param height Height of the bunker part.
 * @param x X-coordinate on screen.
 * @param y Y-coordinate on screen.
 * @return Pointer to the created BUNKER or NULL on failure.
 */
BUNKER *bunker_create(ALLEGRO_BITMAP *bitmap, int source_x, int source_y,
                      int width, int height, float x, float y);

/**
 * @brief Destroys a bunker part and frees its memory.
 *
 * @param bunker Pointer to the BUNKER to destroy.
 * @return OK on success, ERROR if bunker is NULL.
 */
STATUS bunker_destroy(BUNKER *bunker);

/**
 * @brief Gets the x-coordinate of the bunker part.
 */
float bunker_get_x(BUNKER *bunker);

/**
 * @brief Gets the y-coordinate of the bunker part.
 */
float bunker_get_y(BUNKER *bunker);

/**
 * @brief Gets the x-source coordinate in the sprite sheet (damage state).
 */
int bunker_get_source_x(BUNKER *bunker);

/**
 * @brief Sets the x-source coordinate in the sprite sheet (damage state).
 */
STATUS bunker_set_source_x(BUNKER *bunker, int source_x);

/**
 * @brief Gets the y-source coordinate in the sprite sheet (part shape).
 */
int bunker_get_source_y(BUNKER *bunker);

/**
 * @brief Gets the remaining life of the bunker part.
 */
int bunker_get_life(BUNKER *bunker);

/**
 * @brief Sets the remaining life of the bunker part.
 */
STATUS bunker_set_life(BUNKER *bunker, int life);

/**
 * @brief Gets the width of the bunker part.
 */
int bunker_get_width(BUNKER *bunker);

/**
 * @brief Gets the height of the bunker part.
 */
int bunker_get_height(BUNKER *bunker);

/**
 * @brief Renders the bunker part on the screen.
 */
STATUS bunker_print(BUNKER *bunker);

#endif /* BUNKER_H */
