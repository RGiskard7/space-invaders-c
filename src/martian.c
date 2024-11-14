/**
 * @file martian.c
 * @brief Manages the creation, movement, and behavior of enemy Martians in the Space Invaders game.
 * 
 * This file contains functions to handle the properties, movement, shooting capabilities, and 
 * graphical rendering of Martians.
 * 
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "martian.h"

/**
 * @struct _martian
 * @brief Structure representing an enemy Martian in the game.
 * 
 * This structure holds the Martian's coordinates, bitmap image, bullets, movement direction, 
 * score, and other necessary attributes for handling its behavior.
 */
struct _martian {
    float x, y;                       ///< Martian's coordinates
    float *dir;                       ///< Pointer to the movement direction
    ALLEGRO_BITMAP *bitmap;           ///< Bitmap image representing the Martian
    BULLET *bullets[MAX_MART_BULLETS];///< Array of bullets fired by the Martian
    long num_shots;                   ///< Number of bullets currently in use
    bool active;                      ///< Active state of the Martian
    int source_x, source_y;           ///< Source coordinates in bitmap for rendering
    int width, height;                ///< Dimensions of the Martian sprite
    //int life; 
    int timer;                        ///< Timer for controlling actions
    int score;                        ///< Score value awarded when destroyed
};

/**
 * @brief Creates a new Martian with specified attributes.
 * 
 * @param bitmap Bitmap image of the Martian.
 * @param width Width of the Martian.
 * @param height Height of the Martian.
 * @param x Initial x-coordinate.
 * @param y Initial y-coordinate.
 * @param dir Pointer to the initial movement direction.
 * @param score Score value awarded when destroyed.
 * 
 * @return A pointer to the created MARTIAN structure, or NULL on failure.
 */
MARTIAN *mart_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, float *dir, int score) { //Crear martian
    MARTIAN *new_martian = NULL;

    if (!bitmap) {
        return NULL;
    }

    new_martian = (MARTIAN*) malloc(sizeof (MARTIAN));
    if (!new_martian) {
        return NULL;
    }

    new_martian->bitmap = bitmap;

    new_martian->x = x;
    new_martian->y = y;

    new_martian->dir = dir; // Comprobar

    new_martian->width = width;
    new_martian->height = height;

    new_martian->source_x = 0;
    new_martian->source_y = 0;

    //new_martian->life = 3;

    new_martian->score = score;

    new_martian->num_shots = 0;

    new_martian->timer = 0;

    new_martian->active = false;

    for (int i = 0; i < MAX_MART_BULLETS; i++) { //Inicializacion de punteros a bala
        new_martian->bullets[i] = NULL;
    }

    return new_martian;
}

/**
 * @brief Destroys the Martian and releases associated resources.
 * 
 * Frees the memory allocated for the Martian and its bullets.
 * 
 * @param martian Pointer to the Martian to destroy.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_destroy(MARTIAN *martian) { //Destruir martian
    STATUS result = OK;

    if (!martian) {
        return ERROR;
    }

    for (int i = 0; i < martian->num_shots && martian->bullets[i] != NULL; i++) { // Recorrer hasta el maximo de balas disparadas
        if (bullet_destroy(martian->bullets[i]) == ERROR) {
            result = ERROR;
        }
        martian->bullets[i] = NULL;
    }

    free(martian);
    martian = NULL;

    return result;
}

/**
 * @brief Sets the x-coordinate of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param cx New x-coordinate.
 * @return STATUS code.
 */
STATUS mart_set_x(MARTIAN *martian, float cx) {
    if (!martian) {
        return ERROR;
    }

    martian->x = cx;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Martian's x-coordinate, or ERROR if martian is NULL.
 */
float mart_get_x(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->x;
}

/**
 * @brief Sets the y-coordinate of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param cy New y-coordinate.
 * @return STATUS code.
 */
STATUS mart_set_y(MARTIAN *martian, float cy) {
    if (!martian) {
        return ERROR;
    }

    martian->y = cy;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Martian's y-coordinate, or ERROR if martian is NULL.
 */
float mart_get_y(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->y;
}

/**
 * @brief Sets the movement direction of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param dir Pointer to the new direction.
 * @return STATUS code.
 */
STATUS mart_set_dir(MARTIAN *martian, float *dir) {
    if (!martian || !dir) {
        return ERROR;
    }

    martian->dir = dir;

    return OK;
}

/**
 * @brief Retrieves the current movement direction of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Current direction, or -1 if martian is NULL.
 */
float mart_get_dir(MARTIAN *martian) {
    if (!martian) {
        return -1;
    }

    return *(martian->dir);
}

/**
 * @brief Sets the bitmap image for the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param image New bitmap image.
 * @return STATUS code.
 */
STATUS mart_set_bitmap(MARTIAN *martian, ALLEGRO_BITMAP *image) {
    if (!martian || !image) {
        return ERROR;
    }

    martian->bitmap = image;

    return OK;
}

/**
 * @brief Retrieves the bitmap image of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Pointer to the bitmap image, or NULL if martian is NULL.
 */
ALLEGRO_BITMAP *mart_get_bitmap(MARTIAN *martian) {
    if (!martian) {
        return NULL;
    }

    return martian->bitmap;
}

/**
 * @brief Sets the active state of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param active New active state.
 * @return STATUS code.
 */
STATUS mart_set_active(MARTIAN *martian, bool active) {
    if (!martian) {
        return ERROR;
    }

    martian->active = active;

    return OK;
}

/**
 * @brief Retrieves the active state of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return true if active, false otherwise.
 */
bool mart_get_active(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->active;
}

/**
 * @brief Sets the x-coordinate for the source region in the Martian's bitmap.
 * 
 * @param martian Pointer to the Martian.
 * @param source_x X-coordinate in the bitmap source.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_set_source_x(MARTIAN *martian, int source_x) {
    if (!martian) {
        return ERROR;
    }

    martian->source_x = source_x;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate for the source region in the Martian's bitmap.
 * 
 * @param martian Pointer to the Martian.
 * @return X-coordinate in the bitmap source, or ERROR if martian is NULL.
 */
int mart_get_source_x(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->source_x;
}

/**
 * @brief Sets the y-coordinate for the source region in the Martian's bitmap.
 * 
 * @param martian Pointer to the Martian.
 * @param source_y Y-coordinate in the bitmap source.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_set_source_y(MARTIAN *martian, int source_y) {
    if (!martian) {
        return ERROR;
    }

    martian->source_y = source_y;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate for the source region in the Martian's bitmap.
 * 
 * @param martian Pointer to the Martian.
 * @return Y-coordinate in the bitmap source, or ERROR if martian is NULL.
 */
int mart_get_source_y(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->source_y;
}

/**
 * @brief Sets the number of bullets fired by the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @param num_shots Number of bullets.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_set_num_shots(MARTIAN *martian, long num_shots) {
    if (!martian || num_shots < 0) {
        return ERROR;
    }

    martian->num_shots = num_shots;

    return OK;
}

/**
 * @brief Retrieves the number of bullets fired by the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Number of bullets, or ERROR if martian is NULL.
 */
long mart_get_num_shots(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    return martian->num_shots;
}

/*STATUS mart_set_life(MARTIAN *martian, int life) {
    if (!martian) {
        return ERROR;
    }

    martian->life = life;

    return OK;
}

int mart_get_life(MARTIAN *martian) {
    if (!martian) {
        return 0;
    }

    return martian->life;
}*/

/**
 * @brief Sets the Martian's score value.
 * 
 * @param martian Pointer to the Martian.
 * @param score Score to assign.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_set_score(MARTIAN *martian, int score) {
    if (!martian || score <= 0) {
        return ERROR;
    }

    martian->score = score;
    
    return OK;
}

/**
 * @brief Retrieves the Martian's score value.
 * 
 * @param martian Pointer to the Martian.
 * @return Score value, or -1 if martian is NULL.
 */
int mart_get_score(MARTIAN * martian) {
    if (!martian) {
        return -1;
    }

    return martian->score;
}

/**
 * @brief Returns the width of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Width of the Martian, or 0 if martian is NULL.
 */
int mart_get_width(MARTIAN *martian) {
    if (!martian) {
        return 0;
    }

    return martian->width;
}

/**
 * @brief Returns the height of the Martian.
 * 
 * @param martian Pointer to the Martian.
 * @return Height of the Martian, or 0 if martian is NULL.
 */
int mart_get_height(MARTIAN *martian) {
    if (!martian) {
        return 0;
    }

    return martian->height;
}

/**
 * @brief Adds a bullet to the Martian's bullet list.
 * 
 * @param martian Pointer to the Martian.
 * @param bullet Pointer to the bullet to add.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_add_bullet(MARTIAN *martian, BULLET *bullet) {
    if (!martian || !bullet || martian->num_shots >= MAX_MART_BULLETS) {
        return ERROR;
    }

    martian->bullets[martian->num_shots] = bullet;
    martian->num_shots++;

    return OK;
}

/**
 * @brief Removes and returns the first bullet in the Martian's list (FIFO).
 * 
 * @param martian Pointer to the Martian.
 * @return Pointer to the dequeued bullet, or NULL if none available.
 */
BULLET *mart_dequeue_bullet(MARTIAN *martian) { // Las balas se comportan como una cola
    BULLET *bullet = NULL;

    if (martian != NULL && martian->num_shots > 0) {
        bullet = martian->bullets[0];
        martian->bullets[0] = NULL;

        for (int i = 0; i < martian->num_shots - 1; i++) {
            martian->bullets[i] = martian->bullets[i + 1];
        }

        martian->num_shots--;
        martian->bullets[martian->num_shots] = NULL;
    }

    return bullet;
}

/**
 * @brief Extracts a bullet at a specific index from the Martian's list.
 * 
 * @param martian Pointer to the Martian.
 * @param i Index of the bullet to extract.
 * @return Pointer to the extracted bullet, or NULL if not found.
 */
BULLET *mart_extract_bullet_at(MARTIAN* martian, int i) { // Las balas se comportan como una lista dinamica
    BULLET *bullet = NULL;

    if (martian != NULL && martian->num_shots > 0) {
        if (i >= 0 && i < martian->num_shots ) {
            if (martian->bullets[i] != NULL) {
                bullet = martian->bullets[i];

                // Desplazamos todas las balas restantes hacia adelante
                for (int j = i; j < martian->num_shots - 1; j++) {
                    martian->bullets[j] = martian->bullets[j + 1];
                }

                // Reducimos el contador de balas y aseguramos que el último espacio sea NULL
                martian->num_shots--;
                martian->bullets[martian->num_shots] = NULL;
            }
        }
    }
    
    return bullet;
}

/**
 * @brief Returns a pointer to a bullet at a specific index.
 * 
 * @param martian Pointer to the Martian.
 * @param i Index of the bullet.
 * @return Pointer to the bullet, or NULL if not found.
 */
BULLET *mart_get_bullet_at(MARTIAN *martian, int i) {
    if (!martian || i < 0 || i >= martian->num_shots) {
        return NULL;
    }

    return martian->bullets[i];
}

/**
 * @brief Moves all bullets fired by the Martian within screen limits.
 * 
 * @param martian Pointer to the Martian.
 * @param speed Movement speed.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_move_bullet(MARTIAN *martian, float speed) { // Pasar los limites por parametro
    float bottom_limit = CANVAS_HEIGTH;

    if (!martian) {
        return ERROR;
    }

    for (int i = 0; i < martian->num_shots && martian->bullets[i] != NULL; i++) {
        if (bullet_get_y(martian->bullets[i]) + speed < bottom_limit) {
            if (bullet_move(martian->bullets[i], speed) == ERROR) {
                return ERROR;
            }
        } else {
            if (bullet_destroy(mart_extract_bullet_at(martian, i)) == ERROR) {
                return ERROR;
            }
        }
    }

    return OK;
}

/**
 * @brief Makes the Martian fire a bullet.
 * 
 * @param martian Pointer to the Martian.
 * @param bitmap Bitmap image for the bullet.
 * @return STATUS code (OK on success, ERROR if bullet can't be fired).
 */
STATUS mart_shoot(MARTIAN *martian, ALLEGRO_BITMAP *bitmap) {
    BULLET *new_bullet = NULL;

    if (!martian || !bitmap) {
        return ERROR;
    }

    if (martian->num_shots >= MAX_MART_BULLETS) {
        return OK;
    }

    if (martian->num_shots == MAX_MART_BULLETS) {
        return OK;
    }

    new_bullet = bullet_create(bitmap, 6, 12, martian->x + 12, martian->y, DOWN);

    if (!new_bullet) {
        return ERROR;
    }

    if (mart_add_bullet(martian, new_bullet) == ERROR) {
        bullet_destroy(new_bullet);
        return ERROR;
    }

    return OK;
}

/**
 * @brief Moves the Martian based on its direction.
 * 
 * @param martian Pointer to the Martian.
 * @param speed Movement speed.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_move(MARTIAN *martian, float speed) { // Pedir los limites por parametro
    if (!martian) {
        return ERROR;
    }

    if (*(martian->dir) == RIGHT) {
        martian->x += speed;
    } else if (*(martian->dir) == LEFT) {
        martian->x -= speed;
    } else if (*(martian->dir) == DOWN) {
        martian->y += MART_HEIGHT;
        //martian->y += speed;
    }

    return OK;
}

/**
 * @brief Renders the Martian on the screen.
 * 
 * @param martian Pointer to the Martian.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS mart_print(MARTIAN *martian) {
    if (!martian) {
        return ERROR;
    }

    al_draw_bitmap_region(martian->bitmap, (martian->source_x * martian->width), (martian->source_y * martian->height), 
        martian->width, martian->height, martian->x, martian->y, 0);

    return OK;
}

/**
 * @brief Sets a timer for the Martian to control its actions.
 * 
 * @param martian Pointer to the Martian.
 * @param max_time Maximum timer value before resetting.
 */
void mart_set_timer(MARTIAN *martian, int max_time) {
    if (!martian) {
        return;
    }

    martian->timer++;
    if (martian->timer >= max_time) { //temporizador para las balas
        martian->timer = 0;
    }

    return;
}

/**
 * @brief Retrieves the Martian's current timer value.
 * 
 * @param martian Pointer to the Martian.
 * @return Timer value, or -1 if martian is NULL.
 */
int mart_get_time(MARTIAN *martian) {
    if (!martian) {
        return -1;
    }

    return martian->timer;
}