/**
 * @file object.c
 * @brief Implementation of the Object structure and associated functions for 2D game elements.
 *
 * This file provides functions to create, manage, and render generic objects within the game.
 * Objects in this context can represent various game elements, with properties for position,
 * bitmap, dimensions, lifespan, and fixed or dynamic status.
 * 
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "object.h"

/**
 * @struct _object
 * @brief Represents a generic game object.
 *
 * Stores information for rendering, positioning, and lifespan of the object.
 * The object can be either fixed in place or dynamic, and it includes a timer
 * to control animations or other time-based actions.
 */
struct _object {
    float x, y;                       ///< X and Y coordinates of the object
    ALLEGRO_BITMAP *bitmap;           ///< Bitmap representing the object's appearance
    int source_x, source_y;           ///< Source coordinates within the bitmap
    int width, height;                ///< Width and height of the object
    int life;                         ///< Lifespan or health of the object
    int timer;                        ///< Timer for time-based events or animations
    bool fixed;                       ///< Whether the object is fixed in place
};

/**
 * @brief Creates a new object with specified properties.
 *
 * @param bitmap Bitmap representing the object's image.
 * @param source_x Source x-coordinate in the bitmap.
 * @param source_y Source y-coordinate in the bitmap.
 * @param width Width of the object.
 * @param height Height of the object.
 * @param cx Initial x-coordinate of the object.
 * @param cy Initial y-coordinate of the object.
 * @param fixed True if the object is fixed in place, false if it is movable.
 * @return Pointer to the created OBJECT structure, or NULL if allocation fails.
 */
OBJECT *obj_create(ALLEGRO_BITMAP *bitmap, int source_x, int source_y, int width, int height, float cx, float cy, bool fixed) {
    OBJECT *new_object = NULL;

    if (!bitmap) {
        return NULL;
    }

    new_object = (OBJECT*)malloc(sizeof(OBJECT));
    if (!new_object) {
        return NULL;
    }

    new_object->bitmap = bitmap;

    new_object->x = cx;
    new_object->y = cy;

    new_object->source_x = source_x;
    new_object->source_y = source_y;

    new_object->width = width;
    new_object->height = height;

    new_object->life = 3;

    new_object->timer = 0;

    new_object->fixed = fixed;

    return new_object;
}

/**
 * @brief Destroys an object and frees associated memory.
 *
 * @param object Pointer to the OBJECT structure to destroy.
 * @return OK on successful destruction, ERROR if the object pointer is NULL.
 */
STATUS obj_destroy(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    free(object);

    return OK;
}

/**
 * @brief Sets the x-coordinate of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @param cx New x-coordinate.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_set_x(OBJECT *object, float cx) {
    if (!object) {
        return ERROR;
    }

    object->x = cx;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The x-coordinate or ERROR if the object is NULL.
 */
float obj_get_x(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    return object->x;
}

/**
 * @brief Sets the y-coordinate of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @param cy New y-coordinate.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_set_y(OBJECT *object, float cy) {
    if (!object) {
        return ERROR;
    }

    object->y = cy;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The y-coordinate or ERROR if the object is NULL.
 */
float obj_get_y(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    return object->y;
}

/**
 * @brief Retrieves the bitmap associated with the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return Pointer to the bitmap or NULL if the object is NULL.
 */
ALLEGRO_BITMAP *obj_get_bitmap(OBJECT *object) {
    if (!object) {
        return NULL;
    }

    return object->bitmap;
}

/**
 * @brief Sets the x-source coordinate of the object's bitmap.
 *
 * @param object Pointer to the OBJECT structure.
 * @param source_x New x-source coordinate value.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_set_source_x(OBJECT *object, int source_x) {
    if (!object) {
        return ERROR;
    }

    object->source_x = source_x;

    return OK;
}

/**
 * @brief Retrieves the x-source coordinate of the object's bitmap.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The x-source coordinate or ERROR if the object is NULL.
 */
int obj_get_source_x(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    return object->source_x;
}

/**
 * @brief Sets the y-source coordinate of the object's bitmap.
 *
 * @param object Pointer to the OBJECT structure.
 * @param source_y New y-source coordinate value.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_set_source_y(OBJECT *object, int source_y) {
    if (!object) {
        return ERROR;
    }

    object->source_y = source_y;

    return OK;
}

/**
 * @brief Retrieves the y-source coordinate of the object's bitmap.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The y-source coordinate or ERROR if the object is NULL.
 */
int obj_get_source_y(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    return object->source_y;
}

/**
 * @brief Sets the lifespan or health of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @param life New lifespan value.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_set_life(OBJECT *object, int life) {
    if (!object) {
        return ERROR;
    }

    object->life = life;

    return OK;
}

/**
 * @brief Retrieves the lifespan or health of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The lifespan or 0 if the object is NULL.
 */
int obj_get_life(OBJECT *object) {
    if (!object) {
        return 0;
    }

    return object->life;
}

/**
 * @brief Retrieves the width of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The width of the object or 0 if the object is NULL.
 */
int obj_get_width(OBJECT *object) {
    if (!object) {
        return 0;
    }

    return object->width;
}

/**
 * @brief Retrieves the height of the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The height of the object or 0 if the object is NULL.
 */
int obj_get_height(OBJECT *object) {
    if (!object) {
        return 0;
    }

    return object->height;
}

/**
 * @brief Draws the object on the screen.
 *
 * @param object Pointer to the OBJECT structure.
 * @return OK if successful, ERROR if the object is NULL.
 */
STATUS obj_print(OBJECT *object) {
    if (!object) {
        return ERROR;
    }

    al_draw_bitmap_region(object->bitmap, (object->source_x * object->width), (object->source_y * object->height), 
        object->width, object->height, object->x, object->y, 0);

    return OK;
}

/**
 * @brief Increments the object's timer, resetting it if it reaches max_time.
 *
 * @param object Pointer to the OBJECT structure.
 * @param max_time Maximum timer value before reset.
 */
void obj_set_timer(OBJECT *object, int max_time) {
    if (!object) {
        return;
    }

    object->timer++;
    if (object->timer >= max_time) {
        object->timer = 0;
    }

    return;
}

/**
 * @brief Retrieves the current timer value for the object.
 *
 * @param object Pointer to the OBJECT structure.
 * @return The timer value or -1 if the object is NULL.
 */
int obj_get_time(OBJECT *object) {
    if (!object) {
        return -1;
    }

    return object->timer;
}