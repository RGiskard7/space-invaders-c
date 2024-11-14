#ifndef BULLET_H
#define	BULLET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"

/**
 * @brief Represents a bullet within the game.
 */
typedef struct _bullet BULLET;

/**
 * @brief Creates a new bullet instance.
 */
BULLET *bullet_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, int dir);

/**
 * @brief Destroys a bullet and frees resources.
 */
STATUS bullet_destroy(BULLET *bullet);

/**
 * @brief Sets the x-coordinate of the bullet.
 */
STATUS bullet_set_x(BULLET *bullet, float x);

/**
 * @brief Gets the x-coordinate of the bullet.
 */
float bullet_get_x(BULLET *bullet);

/**
 * @brief Sets the y-coordinate of the bullet.
 */
STATUS bullet_set_y(BULLET *bullet, float y);

/**
 * @brief Gets the y-coordinate of the bullet.
 */
float bullet_get_y(BULLET *bullet);

/**
 * @brief Sets the direction of the bullet.
 */
STATUS bullet_set_dir(BULLET *bullet, int dir);

/**
 * @brief Gets the direction of the bullet.
 */
int bullet_get_dir(BULLET *bullet);

/**
 * @brief Sets the bitmap for the bullet.
 */
STATUS bullet_set_bitmap(BULLET *bullet, ALLEGRO_BITMAP *bitmap);

/**
 * @brief Gets the bitmap of the bullet.
 */
ALLEGRO_BITMAP *bullet_get_bitmap(BULLET *bullet);

/**
 * @brief Sets the x-coordinate of the bullet's source on the bitmap.
 */
STATUS bullet_set_source_x(BULLET *bullet, int source_x);

/**
 * @brief Gets the x-coordinate of the bullet's source on the bitmap.
 */
int bullet_get_source_x(BULLET *bullet);

/**
 * @brief Sets the y-coordinate of the bullet's source on the bitmap.
 */
STATUS bullet_set_source_y(BULLET *bullet, int source_y);

/**
 * @brief Gets the y-coordinate of the bullet's source on the bitmap.
 */
int bullet_get_source_y(BULLET *bullet);

/**
 * @brief Sets the dx (horizontal increment) of the bullet.
 */
STATUS bullet_set_dx(BULLET *bullet, int dx);

/**
 * @brief Gets the dx of the bullet.
 */
int bullet_get_dx(BULLET *bullet);

/**
 * @brief Sets the dy (vertical increment) of the bullet.
 */
STATUS bullet_set_dy(BULLET *bullet, int dy);

/**
 * @brief Gets the dy of the bullet.
 */
int bullet_get_dy(BULLET *bullet);

/**
 * @brief Gets the width of the bullet.
 */
int bullet_get_width(BULLET *bullet);

/**
 * @brief Gets the height of the bullet.
 */
int bullet_get_height(BULLET *bullet);

/**
 * @brief Renders the bullet to the screen.
 */
STATUS bullet_print(BULLET *bullet);

/**
 * @brief Moves the bullet based on its speed and direction.
 */
STATUS bullet_move(BULLET *bullet, float speed);

/**
 * @brief Checks for collision between the bullet and a specified object.
 */
bool bullet_check_colision(BULLET *bullet, int obj_x, int obj_y, int obj_width, int obj_height);

#endif /* BULLET_H */