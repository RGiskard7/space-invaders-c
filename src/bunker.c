/**
 * @file bunker.c
 * @brief Implementation of the Bunker structure and associated functions.
 *
 * This file provides functions to create, manage, and render bunker parts
 * within the Space Invaders game. Each bunker part is a section of a larger
 * shield, rendered from a sprite sheet and capable of absorbing a fixed
 * number of hits before being destroyed.
 *
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "bunker.h"

/**
 * @struct _bunker
 * @brief Represents a single destructible part of a bunker shield.
 *
 * Stores position, sprite sheet coordinates, dimensions, and remaining
 * life for one section of a bunker. The source_x coordinate advances
 * with each hit to show progressive damage on the sprite.
 */
struct _bunker {
    float x, y;              ///< Screen coordinates of the bunker part
    ALLEGRO_BITMAP *bitmap;  ///< Shared sprite sheet for all bunker parts
    int source_x, source_y;  ///< Source coordinates within the sprite sheet
    int width, height;       ///< Dimensions of the bunker part
    int life;                ///< Remaining hits before destruction
};

/**
 * @brief Creates a new bunker part with the specified attributes.
 *
 * @param bitmap Shared sprite sheet bitmap for all bunker parts.
 * @param source_x Initial x-coordinate in the sprite sheet (damage frame).
 * @param source_y Y-coordinate in the sprite sheet (part shape/type).
 * @param width Width of the bunker part.
 * @param height Height of the bunker part.
 * @param x X-coordinate on screen.
 * @param y Y-coordinate on screen.
 * @return Pointer to the created BUNKER or NULL on failure.
 */
BUNKER *bunker_create(ALLEGRO_BITMAP *bitmap, int source_x, int source_y,
                      int width, int height, float x, float y) {
    BUNKER *new_bunker = NULL;

    if (!bitmap) {
        return NULL;
    }

    new_bunker = (BUNKER *)malloc(sizeof(BUNKER));
    if (!new_bunker) {
        return NULL;
    }

    new_bunker->bitmap = bitmap;

    new_bunker->x = x;
    new_bunker->y = y;

    new_bunker->source_x = source_x;
    new_bunker->source_y = source_y;

    new_bunker->width = width;
    new_bunker->height = height;

    new_bunker->life = BUNKER_LIFE;

    return new_bunker;
}

/**
 * @brief Destroys a bunker part and frees its allocated memory.
 *
 * @param bunker Pointer to the BUNKER to destroy.
 * @return OK on success, ERROR if bunker is NULL.
 */
STATUS bunker_destroy(BUNKER *bunker) {
    if (!bunker) {
        return ERROR;
    }

    free(bunker);

    return OK;
}

/**
 * @brief Gets the x-coordinate of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @return X-coordinate, or -1.0 if bunker is NULL.
 */
float bunker_get_x(BUNKER *bunker) {
    if (!bunker) {
        return -1.0;
    }

    return bunker->x;
}

/**
 * @brief Gets the y-coordinate of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Y-coordinate, or -1.0 if bunker is NULL.
 */
float bunker_get_y(BUNKER *bunker) {
    if (!bunker) {
        return -1.0;
    }

    return bunker->y;
}

/**
 * @brief Gets the x-source coordinate in the sprite sheet.
 *
 * The source_x advances with each hit to display progressive damage.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Source x-coordinate, or -1 if bunker is NULL.
 */
int bunker_get_source_x(BUNKER *bunker) {
    if (!bunker) {
        return -1;
    }

    return bunker->source_x;
}

/**
 * @brief Sets the x-source coordinate in the sprite sheet.
 *
 * Used to advance the damage frame after each hit.
 *
 * @param bunker Pointer to the BUNKER.
 * @param source_x New x-source coordinate value.
 * @return OK on success, ERROR if bunker is NULL.
 */
STATUS bunker_set_source_x(BUNKER *bunker, int source_x) {
    if (!bunker) {
        return ERROR;
    }

    bunker->source_x = source_x;

    return OK;
}

/**
 * @brief Gets the y-source coordinate in the sprite sheet.
 *
 * The source_y determines the shape/type of this bunker part and
 * remains constant throughout the part's lifetime.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Source y-coordinate, or -1 if bunker is NULL.
 */
int bunker_get_source_y(BUNKER *bunker) {
    if (!bunker) {
        return -1;
    }

    return bunker->source_y;
}

/**
 * @brief Gets the remaining life of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Remaining life, or 0 if bunker is NULL.
 */
int bunker_get_life(BUNKER *bunker) {
    if (!bunker) {
        return 0;
    }

    return bunker->life;
}

/**
 * @brief Sets the remaining life of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @param life New life value.
 * @return OK on success, ERROR if bunker is NULL.
 */
STATUS bunker_set_life(BUNKER *bunker, int life) {
    if (!bunker) {
        return ERROR;
    }

    bunker->life = life;

    return OK;
}

/**
 * @brief Gets the width of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Width, or 0 if bunker is NULL.
 */
int bunker_get_width(BUNKER *bunker) {
    if (!bunker) {
        return 0;
    }

    return bunker->width;
}

/**
 * @brief Gets the height of the bunker part.
 *
 * @param bunker Pointer to the BUNKER.
 * @return Height, or 0 if bunker is NULL.
 */
int bunker_get_height(BUNKER *bunker) {
    if (!bunker) {
        return 0;
    }

    return bunker->height;
}

/**
 * @brief Renders the bunker part on the screen.
 *
 * Draws the appropriate sprite region based on the current damage state
 * (source_x) and part shape (source_y).
 *
 * @param bunker Pointer to the BUNKER.
 * @return OK on success, ERROR if bunker is NULL.
 */
STATUS bunker_print(BUNKER *bunker) {
    if (!bunker) {
        return ERROR;
    }

    al_draw_bitmap_region(bunker->bitmap,
                          (bunker->source_x * bunker->width),
                          (bunker->source_y * bunker->height),
                          bunker->width, bunker->height,
                          bunker->x, bunker->y, 0);

    return OK;
}
