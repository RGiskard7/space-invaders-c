#ifndef SHIP_H
#define	SHIP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "config.h"
#include "types.h"
#include "bullet.h"

#define MAX_SHIP_BULLETS 50
#define SHIP_WIDTH 30
#define SHIP_HEIGHT 20

typedef struct _ship SHIP;

/**
 * @brief Creates a new ship with the specified parameters.
 */
SHIP *ship_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, int dir, int life);

/**
 * @brief Destroys the ship, freeing its resources.
 */
STATUS ship_destroy(SHIP *ship);

/**
 * @brief Sets the X position of the ship.
 */
STATUS ship_set_x(SHIP *ship, float x);

/**
 * @brief Gets the X position of the ship.
 */
float ship_get_x(SHIP *ship);

/**
 * @brief Sets the Y position of the ship.
 */
STATUS ship_set_y(SHIP *ship, float y);

/**
 * @brief Gets the Y position of the ship.
 */
float ship_get_y(SHIP *ship);

/**
 * @brief Sets the direction of the ship.
 */
STATUS ship_set_dir(SHIP *ship, int dir);

/**
 * @brief Gets the current direction of the ship.
 */
int ship_get_dir(SHIP *ship);

/**
 * @brief Sets the bitmap image for the ship.
 */
STATUS ship_set_bitmap(SHIP *ship, ALLEGRO_BITMAP *bitmap);

/**
 * @brief Gets the bitmap image of the ship.
 */
ALLEGRO_BITMAP *ship_get_bitmap(SHIP *ship);

/**
 * @brief Activates or deactivates the ship.
 */
STATUS ship_set_active(SHIP *ship, bool active);

/**
 * @brief Checks if the ship is active.
 */
bool ship_get_active(SHIP *ship);

/**
 * @brief Sets the source X coordinate for rendering.
 */
STATUS ship_set_source_x(SHIP *ship, int source_x);

/**
 * @brief Gets the source X coordinate for rendering.
 */
int ship_get_source_x(SHIP *ship);

/**
 * @brief Sets the source Y coordinate for rendering.
 */
STATUS ship_set_source_y(SHIP *ship, int source_y);

/**
 * @brief Gets the source Y coordinate for rendering.
 */
int ship_get_source_y(SHIP *ship);

/**
 * @brief Sets the number of bullets fired by the ship.
 */
STATUS ship_set_num_shots(SHIP *ship, long num_shots);

/**
 * @brief Gets the number of bullets currently in play.
 */
long ship_get_num_shots(SHIP *ship);

/**
 * @brief Sets the life points of the ship.
 */
STATUS ship_set_life(SHIP *ship, int life);

/**
 * @brief Gets the remaining life points of the ship.
 */
int ship_get_life(SHIP *ship);

/**
 * @brief Gets the width of the ship.
 */
int ship_get_width(SHIP *ship);

/**
 * @brief Gets the height of the ship.
 */
int ship_get_height(SHIP *ship);

/**
 * @brief Sets a timer for the ship's actions.
 */
void ship_set_timer(SHIP *ship, int num);

/**
 * @brief Gets the current timer value for the ship.
 */
int ship_get_time(SHIP *max_time);

/**
 * @brief Renders the ship on the display.
 */
STATUS ship_print(SHIP *ship);

/**
 * @brief Decreases the life points of the ship by a specified amount.
 */
STATUS ship_decrease_life(SHIP *ship, int amount);

/**
 * @brief Adds a bullet to the ship's bullet array.
 */
STATUS ship_add_bullet(SHIP *ship, BULLET *bala);

/**
 * @brief Removes and returns the oldest bullet in the ship's queue.
 */
BULLET *ship_dequeue_bullet(SHIP *ship);

/**
 * @brief Removes and returns the bullet at a specified index.
 */
BULLET *ship_extract_bullet_at(SHIP *ship, int i);

/**
 * @brief Gets the bullet at a specified index.
 */
BULLET *ship_get_bullet_at(SHIP *ship, int i);

/**
 * @brief Moves the ship's bullets based on speed.
 */
STATUS ship_move_bullet(SHIP *ship, float speed);

/**
 * @brief Fires a new bullet from the ship.
 */
STATUS ship_shoot(SHIP *ship, ALLEGRO_BITMAP *bitmap);

/**
 * @brief Moves the ship based on its direction and speed.
 */
STATUS ship_move(SHIP *ship, float speed);

/**
 * @brief Checks if the ship is located at the given coordinates.
 */
bool ship_some_loc(SHIP *ship, int x, int y);

#endif /* SHIP_H */