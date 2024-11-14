#ifndef MARTIAN_H
#define	MARTIAN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "config.h"
#include "types.h"
#include "bullet.h"

#define MAX_MART_BULLETS 25 //Maximo de balas por marciano
#define MART_WIDTH 25
#define MART_HEIGHT 20

/**
 * @brief Structure representing a bullet within the game.
 * 
 * Bullets can belong to the player's ship or the martians and are represented
 * by position, direction, image, dimensions, and movement increments.
 */
typedef struct _martian MARTIAN;

/**
 * @brief Creates a new martian.
 * 
 * Allocates and initializes a MARTIAN structure.
 */
MARTIAN *mart_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, float *dir, int score);

/**
 * @brief Destroys a martian, freeing allocated resources.
 * 
 * Frees the memory of the MARTIAN structure and its associated bullets.
 */
STATUS mart_destroy(MARTIAN *martian);

/**
 * @brief Sets the X position of the martian.
 */
STATUS mart_set_x(MARTIAN *martian, float cx);

/**
 * @brief Gets the X position of the martian.
 */
float mart_get_x(MARTIAN *martian);

/**
 * @brief Sets the Y position of the martian.
 */
STATUS mart_set_y(MARTIAN *martian, float cy);

/**
 * @brief Gets the Y position of the martian.
 */
float mart_get_y(MARTIAN *martian);

/**
 * @brief Sets the direction of the martian.
 */
STATUS mart_set_dir(MARTIAN *martian, float *dir);

/**
 * @brief Gets the direction of the martian.
 */
float mart_get_dir(MARTIAN *martian);

/**
 * @brief Sets the bitmap image for the martian.
 */
STATUS mart_set_bitmap(MARTIAN *martian, ALLEGRO_BITMAP *image);

/**
 * @brief Retrieves the bitmap associated with the martian.
 */
ALLEGRO_BITMAP *mart_get_bitmap(MARTIAN *martian);

/**
 * @brief Activates or deactivates the martian's active state.
 */
STATUS mart_set_active(MARTIAN *martian, bool active);

/**
 * @brief Checks if the martian is currently active.
 */
bool mart_get_active(MARTIAN *martian);

/**
 * @brief Sets the X source coordinate of the martian image.
 */
STATUS mart_set_source_x(MARTIAN *martian, int source_x);

/**
 * @brief Gets the X source coordinate of the martian image.
 */
int mart_get_source_x(MARTIAN *martian);

/**
 * @brief Sets the Y source coordinate of the martian image.
 */
STATUS mart_set_source_y(MARTIAN *martian, int source_y);

/**
 * @brief Gets the Y source coordinate of the martian image.
 */
int mart_get_source_y(MARTIAN *martian);

/**
 * @brief Sets the number of bullets the martian has fired.
 */
STATUS mart_set_num_shots(MARTIAN *martian, long num_shots);

/**
 * @brief Retrieves the number of bullets the martian has fired.
 */
long mart_get_num_shots(MARTIAN *martian);

/**
 * @brief Sets the score associated with the martian.
 */
STATUS mart_set_Score(MARTIAN *martian, int score);

/**
 * @brief Retrieves the score value of the martian.
 */
int mart_get_score(MARTIAN * martian);

/**
 * @brief Gets the width of the martian.
 */
int mart_get_width(MARTIAN *martian);

/**
 * @brief Gets the height of the martian.
 */
int mart_get_height(MARTIAN *martian);

/**
 * @brief Adds a bullet to the martian's bullet array.
 */
STATUS mart_add_bullet(MARTIAN *martian, BULLET *bullet);

/**
 * @brief Dequeues a bullet from the martian's bullet array.
 * 
 * Treats the bullet array as a queue, removing the oldest bullet.
 */
BULLET *mart_dequeue_bullet(MARTIAN *martian);

/**
 * @brief Extracts a bullet from a specified position in the bullet array.
 * 
 * Treats the bullet array as a dynamic list, allowing access to specific bullet positions.
 */
BULLET *mart_extract_bullet_at(MARTIAN* martian, int i);

/**
 * @brief Retrieves a bullet at a specific index in the martian's bullet array.
 */
BULLET *mart_get_bullet_at(MARTIAN *martian, int i);

/**
 * @brief Moves all bullets of the martian at a specified speed.
 * 
 * Uses speed to determine the distance moved per call.
 */
STATUS mart_move_bullet(MARTIAN *martian, float speed);

/**
 * @brief Causes the martian to fire a bullet.
 */
STATUS mart_shoot(MARTIAN *martian, ALLEGRO_BITMAP *bitmap);

/**
 * @brief Moves the martian at a specified speed.
 * 
 * Uses the direction and speed to calculate new position.
 */
STATUS mart_move(MARTIAN *martian, float speed);

/**
 * @brief Renders the martian on the screen.
 */
STATUS mart_print(MARTIAN *martian);

/**
 * @brief Updates the animation timer for the martian.
 * 
 * Controls the timing of the martian's animations.
 */
void mart_set_timer(MARTIAN *martian, int max_time);

/**
 * @brief Retrieves the current animation timer value.
 */
int mart_get_time(MARTIAN *martian);

/*STATUS mart_set_life(MARTIAN *martian, int life);
int mart_get_life(MARTIAN *martian);*/

#endif	/* MARTIAN_H */