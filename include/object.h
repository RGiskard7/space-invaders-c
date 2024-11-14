#ifndef OBJECT_H
#define	OBJECT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"

/**
 * @brief Represents a game object, such as an explosion or other in-game element.
 */
typedef struct _object OBJECT;

/**
 * @brief Creates a new object instance.
 */
OBJECT *obj_create(ALLEGRO_BITMAP *bitmap, int source_x, int source_y, int width, int height, float x, float y, bool fixed);

/**
 * @brief Destroys an object and frees resources.
 */
STATUS obj_destroy(OBJECT *object);

/**
 * @brief Sets the x-coordinate of the object.
 */
STATUS obj_set_x(OBJECT *object, float x);

/**
 * @brief Gets the x-coordinate of the object.
 */
float obj_get_x(OBJECT *object);

/**
 * @brief Sets the y-coordinate of the object.
 */
STATUS obj_set_y(OBJECT *object, float y);

/**
 * @brief Gets the y-coordinate of the object.
 */
float obj_get_y(OBJECT *object);

/**
 * @brief Retrieves the bitmap of the object.
 */
ALLEGRO_BITMAP *obj_get_bitmap(OBJECT *object);

/**
 * @brief Sets the x-source coordinate for the object bitmap.
 */
STATUS obj_set_source_x(OBJECT *object, int source_x);

/**
 * @brief Gets the x-source coordinate for the object bitmap.
 */
int obj_get_source_x(OBJECT *object);

/**
 * @brief Sets the y-source coordinate for the object bitmap.
 */
STATUS obj_set_source_y(OBJECT *object, int source_y);

/**
 * @brief Gets the y-source coordinate for the object bitmap.
 */
int obj_get_source_y(OBJECT *object);

/**
 * @brief Sets the life value of the object.
 */
STATUS obj_set_life(OBJECT *object, int life);

/**
 * @brief Retrieves the current life of the object.
 */
int obj_get_life(OBJECT *object);

/**
 * @brief Gets the width of the object.
 */
int obj_get_width(OBJECT *object);

/**
 * @brief Gets the height of the object.
 */
int obj_get_height(OBJECT *object);

/**
 * @brief Prints the object to the screen.
 */
STATUS obj_print(OBJECT *object);

/**
 * @brief Sets the object's timer.
 */
void obj_set_timer(OBJECT *object, int max_time);

/**
 * @brief Gets the current timer value of the object.
 */
int obj_get_time(OBJECT *object);

#endif /* OBJECT_H */