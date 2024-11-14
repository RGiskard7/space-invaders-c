/**
 * @file bullet.c
 * @brief Implementation of the Bullet structure and associated functions for a 2D game.
 * 
 * This file provides functions for creating, managing, and rendering bullets within the game.
 * Bullets are created with specific properties, including direction and speed, and can be 
 * checked for collisions with other objects in the game.
 * 
 * Each Bullet contains information on its position, size, direction, and associated bitmap.
 * 
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "bullet.h"

struct _bullet {
    float x, y;                       ///< Bullet's x and y coordinates
    int dir;                          ///< Bullet direction (UP or DOWN)
    ALLEGRO_BITMAP *bitmap;           ///< Bitmap representing the bullet image
    int source_x, source_y;           ///< Source coordinates in the bitmap
    int width, height;                ///< Dimensions of the bullet
    int dx, dy;                       ///< Movement increments for speed adjustments
};

/**
 * @brief Creates a bullet with specified properties.
 * 
 * @param bitmap Bitmap image for the bullet.
 * @param width Width of the bullet.
 * @param height Height of the bullet.
 * @param x Initial x-coordinate.
 * @param y Initial y-coordinate.
 * @param dir Initial direction.
 * @return Pointer to the created bullet or NULL if allocation fails.
 */
BULLET *bullet_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, int dir) {
    BULLET *new_bullet = NULL;

    if (!bitmap) {
        return NULL;
    }

    new_bullet = (BULLET*) malloc(sizeof (BULLET));
    if (!new_bullet) {
        return NULL;
    }

    new_bullet->bitmap = bitmap;

    new_bullet->x = x; //coordenadas de la bullet
    new_bullet->y = y;

    new_bullet->dir = dir; //dirrección de la bullet

    new_bullet->source_x = 0;
    new_bullet->source_y = 0;

    new_bullet->width = width;
    new_bullet->height = height;

    new_bullet->dx = 0; //incremento de las coordenadas para la velocidad de la bullet
    new_bullet->dy = 0;

    return new_bullet;
}

/**
 * @brief Destroys a bullet and frees memory.
 * 
 * @param bullet Pointer to the bullet to destroy.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_destroy(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    free(bullet);
    bullet = NULL;

    return OK;
}

/**
 * @brief Sets the x-coordinate of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @param cx New x-coordinate.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_x(BULLET *bullet, float cx) {
    if (!bullet) {
        return ERROR;
    }

    bullet->x = cx;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return X-coordinate, or ERROR if bullet is NULL.
 */
float bullet_get_x(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    return bullet->x;
}

/**
 * @brief Sets the y-coordinate of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @param cy New y-coordinate.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_y(BULLET *bullet, float cy) {
    if (!bullet) {
        return ERROR;
    }

    bullet->y = cy;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return Y-coordinate, or ERROR if bullet is NULL.
 */
float bullet_get_y(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    return bullet->y;
}

/**
 * @brief Sets the direction of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @param dir Direction to set.
 * @return STATUS code (OK on success, ERROR if bullet is NULL or dir is invalid).
 */
STATUS bullet_set_dir(BULLET *bullet, int dir) {
    if (!bullet || dir < 0) {
        return ERROR;
    }

    bullet->dir = dir;

    return OK;
}

/**
 * @brief Retrieves the direction of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return Direction, or -1 if bullet is NULL.
 */
int bullet_get_dir(BULLET *bullet) {
    if (!bullet) {
        return -1;
    }
    return bullet->dir;
}

/**
 * @brief Sets the bitmap for the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @param image Bitmap image to set.
 * @return STATUS code (OK on success, ERROR if bullet or image is NULL).
 */
STATUS bullet_set_bitmap(BULLET *bullet, ALLEGRO_BITMAP *image) {
    if (!bullet || !image) {
        return ERROR;
    }

    bullet->bitmap = image;

    return OK;
}

/**
 * @brief Retrieves the bitmap of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return Pointer to the bitmap, or NULL if bullet is NULL.
 */
ALLEGRO_BITMAP *bullet_get_bitmap(BULLET *bullet) {
    if (!bullet) {
        return NULL;
    }

    return bullet->bitmap;
}

/**
 * @brief Sets the x-coordinate in the bitmap's source region.
 * 
 * @param bullet Pointer to the bullet.
 * @param source_x Source x-coordinate.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_source_x(BULLET *bullet, int source_x) {
    if (!bullet) {
        return ERROR;
    }

    bullet->source_x = source_x;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate of the source region.
 * 
 * @param bullet Pointer to the bullet.
 * @return Source x-coordinate, or ERROR if bullet is NULL.
 */
int bullet_get_source_x(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    return bullet->source_x;
}

/**
 * @brief Sets the y-coordinate in the bitmap's source region.
 * 
 * @param bullet Pointer to the bullet.
 * @param source_y Source y-coordinate.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_source_y(BULLET *bullet, int source_x) {
    if (!bullet) {
        return ERROR;
    }

    bullet->source_x = source_x;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate of the source region.
 * 
 * @param bullet Pointer to the bullet.
 * @return Source y-coordinate, or ERROR if bullet is NULL.
 */
int bullet_get_source_y(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    return bullet->source_x;
}

/**
 * @brief Sets the x-coordinate increment (dx) for movement.
 * 
 * @param bullet Pointer to the bullet.
 * @param dx X increment.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_dx(BULLET *bullet, int dx) {
    if (!bullet) {
        return ERROR;
    }

    bullet->dx = dx;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate increment (dx) for movement.
 * 
 * @param bullet Pointer to the bullet.
 * @return dx value, or 0 if bullet is NULL.
 */
int bullet_get_dx(BULLET *bullet) {
    if (!bullet) {
        return 0;
    }

    return bullet->dx;
}

/**
 * @brief Sets the y-coordinate increment (dy) for movement.
 * 
 * @param bullet Pointer to the bullet.
 * @param dy Y increment.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_set_dy(BULLET *bullet, int dy) {
    if (!bullet) {
        return ERROR;
    }

    bullet->dy = dy;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate increment (dy) for movement.
 * 
 * @param bullet Pointer to the bullet.
 * @return dy value, or 0 if bullet is NULL.
 */
int bullet_get_dy(BULLET *bullet) {
    if (!bullet) {
        return 0;
    }

    return bullet->dy;
}

/**
 * @brief Retrieves the width of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return Width of the bullet, or 0 if bullet is NULL.
 */
int bullet_get_width(BULLET *bullet) {
    if (!bullet) {
        return 0;
    }

    return bullet->width;
}

/**
 * @brief Retrieves the height of the bullet.
 * 
 * @param bullet Pointer to the bullet.
 * @return Height of the bullet, or 0 if bullet is NULL.
 */
int bullet_get_height(BULLET *bullet) {
    if (!bullet) {
        return 0;
    }

    return bullet->height;
}

/**
 * @brief Moves the bullet based on its direction and speed.
 * 
 * @param bullet Pointer to the bullet.
 * @param speed Speed to move the bullet.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_move(BULLET *bullet, float speed) {
    if (!bullet) {
        return ERROR;
    }

    if (bullet->dir == UP) {
        bullet->y -= speed;
    } else if (bullet->dir == DOWN) {
        bullet->y += speed;
    }

    return OK;
}

/**
 * @brief Draws the bullet on the screen.
 * 
 * @param bullet Pointer to the bullet.
 * @return STATUS code (OK on success, ERROR if bullet is NULL).
 */
STATUS bullet_print(BULLET *bullet) {
    if (!bullet) {
        return ERROR;
    }

    al_draw_bitmap_region(bullet->bitmap, (bullet->source_x * bullet->width), (bullet->source_y * bullet->height), 
        bullet->width, bullet->height, bullet->x, bullet->y, 0);

    return OK;
}

/**
 * @brief Checks if the bullet collides with a given object.
 * 
 * @param bullet Pointer to the bullet.
 * @param obj_x X-coordinate of the object.
 * @param obj_y Y-coordinate of the object.
 * @param obj_width Width of the object.
 * @param obj_height Height of the object.
 * @return true if collision is detected, false otherwise.
 */
bool bullet_check_colision(BULLET *bullet, int obj_x, int obj_y, int obj_width, int obj_height) {
    if ((bullet->x < obj_x + obj_width) && 
        (bullet->x + bullet->width > obj_x) && 
        (bullet->y < obj_y + obj_height) && 
        (bullet->y + bullet->height > obj_y)) {

        return true;
    } 

    return false;
}