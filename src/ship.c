/**
 * @file ship.c
 * @brief Manages the creation, movement, and behavior of the ship in the Space Invaders game.
 * 
 * This file contains the functions needed to create and control the ship, 
 * including its position, movement, firing capabilities, and handling of 
 * the bullets it fires.
 * 
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "ship.h"

/**
 * @struct _ship
 * @brief Structure representing the player-controlled ship in the game.
 * 
 * The ship structure holds the ship's coordinates, bitmap image, bullets, 
 * direction, life, and other necessary attributes for managing its behavior 
 * in the game.
 */
struct _ship {
    float x, y;                       ///< Ship's coordinates
    int dir;                          ///< Ship's direction (e.g., LEFT, RIGHT)
    ALLEGRO_BITMAP *bitmap;           ///< Ship's bitmap image
    BULLET *bullets[MAX_SHIP_BULLETS];///< Array holding ship's bullets
    long num_shots;                   ///< Number of bullets currently in use
    bool active;                      ///< Ship's active state
    int source_x, source_y;           ///< Source coordinates in bitmap for rendering
    int width, height;                ///< Dimensions of the ship
    int life;                         ///< Remaining life of the ship
    int timer;                        ///< Timer for controlling shooting rate
};

/**
 * @brief Creates a new ship with the given parameters.
 * 
 * @param bitmap Bitmap image of the ship.
 * @param width Width of the ship.
 * @param height Height of the ship.
 * @param x Initial x-coordinate.
 * @param y Initial y-coordinate.
 * @param dir Initial direction.
 * @param life Initial life value.
 * 
 * @return A pointer to the created SHIP structure, or NULL on failure.
 */
SHIP *ship_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x, float y, int dir, int life) {
    SHIP *new_ship = NULL;

    if (!bitmap) {
        return NULL;
    }

    new_ship = (SHIP*) malloc(sizeof (SHIP));
    if (!new_ship) {
        return NULL;
    }

    new_ship->bitmap = bitmap;

    new_ship->width = width;
    new_ship->height = height;

    new_ship->x = x;
    new_ship->y = y;

    new_ship->dir = dir;

    new_ship->source_x = 0;
    new_ship->source_y = 0;

    new_ship->life = life;

    new_ship->num_shots = 0;

    new_ship->timer = 0;

    new_ship->active = false;

    for (int i = 0; i < MAX_SHIP_BULLETS; i++) { //Inicializacion de punteros a bullet
        new_ship->bullets[i] = NULL;
    }

    return new_ship;
}

/**
 * @brief Destroys the ship, releasing associated resources.
 * 
 * Frees the memory allocated for the ship and its bullets.
 * 
 * @param ship Pointer to the ship to destroy.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS ship_destroy(SHIP *ship) { //Destruir ship
    STATUS result = OK;

    if (!ship) {
        return ERROR;
    }

    for (int i = 0; i < ship->num_shots && ship->bullets[i] != NULL; i++) { // hacer el bucle con num_shots
        if (bullet_destroy(ship->bullets[i]) == ERROR) {
            result = ERROR;
        }
        ship->bullets[i] = NULL;
    }

    free(ship);
    ship = NULL;

    return result;
}

/**
 * @brief Sets the x-coordinate of the ship.
 * 
 * @param ship Pointer to the ship.
 * @param cx New x-coordinate.
 * @return STATUS code.
 */
STATUS ship_set_x(SHIP *ship, float cx) {
    if (!ship) {
        return ERROR;
    }

    ship->x = cx;

    return OK;
}

/**
 * @brief Retrieves the x-coordinate of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's x-coordinate.
 */
float ship_get_x(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    return ship->x;
}

/**
 * @brief Sets the y-coordinate of the ship.
 * 
 * @param ship Pointer to the ship.
 * @param cy New y-coordinate.
 * @return STATUS code.
 */
STATUS ship_set_y(SHIP *ship, float cy) {
    if (!ship) {
        return ERROR;
    }

    ship->y = cy;

    return OK;
}

/**
 * @brief Retrieves the y-coordinate of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's y-coordinate.
 */
float ship_get_y(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    return ship->y;
}

/**
 * @brief Sets the ship's movement direction.
 * 
 * @param ship Pointer to the ship.
 * @param dir New direction value.
 * @return STATUS code.
 */
STATUS ship_set_dir(SHIP *ship, int dir) {
    if (!ship || dir < 0) {
        return ERROR;
    }

    ship->dir = dir;

    return OK;
}

/**
 * @brief Retrieves the ship's movement direction.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's direction.
 */
int ship_get_dir(SHIP *ship) {
    if (!ship) {
        return -1;
    }

    return ship->dir;
}

/**
 * @brief Sets the ship's bitmap.
 * 
 * @param ship Pointer to the ship.
 * @param bitmap Bitmap to set for the ship.
 * @return STATUS code.
 */
STATUS ship_set_bitmap(SHIP *ship, ALLEGRO_BITMAP *bitmap) {
    if (!ship || !bitmap) {
        return ERROR;
    }

    ship->bitmap = bitmap;

    return OK;
}

/**
 * @brief Retrieves the ship's bitmap.
 * 
 * @param ship Pointer to the ship.
 * @return Pointer to the bitmap.
 */
ALLEGRO_BITMAP *ship_get_bitmap(SHIP *ship) {
    if (!ship) {
        return NULL;
    }

    return ship->bitmap;
}

/**
 * @brief Sets the active state of the ship.
 * 
 * @param ship Pointer to the ship.
 * @param active New active state.
 * @return STATUS code.
 */
STATUS ship_set_active(SHIP *ship, bool active) {
    if (!ship) {
        return ERROR;
    }

    ship->active = active;

    return OK;
}

/**
 * @brief Retrieves the active state of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return true if active, false otherwise.
 */
bool ship_get_active(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    return ship->active;
}

/**
 * @brief Sets the source x-coordinate in the bitmap for rendering.
 * 
 * @param ship Pointer to the ship.
 * @param source_x New source x-coordinate.
 * @return STATUS code.
 */
STATUS ship_set_source_x(SHIP *ship, int source_x) {
    if (!ship) {
        return ERROR;
    }

    ship->source_x = source_x;

    return OK;
}

/**
 * @brief Gets the source x-coordinate for rendering the ship.
 * 
 * @param ship Pointer to the ship.
 * @return The x-coordinate of the ship's source region, or ERROR if ship is NULL.
 */
int ship_get_source_x(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    return ship->source_x;
}

/**
 * @brief Sets the source y-coordinate for rendering the ship.
 * 
 * @param ship Pointer to the ship.
 * @param source_y New source y-coordinate.
 * @return STATUS code.
 */
STATUS ship_set_source_y(SHIP *ship, int source_y) {
    if (!ship) {
        return ERROR;
    }

    ship->source_y = source_y;

    return OK;
}

/**
 * @brief Gets the source y-coordinate for rendering the ship.
 * 
 * @param ship Pointer to the ship.
 * @return The y-coordinate of the ship's source region, or ERROR if ship is NULL.
 */
int ship_get_source_y(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    return ship->source_y;
}

/**
 * @brief Sets the number of shots fired by the ship.
 * 
 * @param ship Pointer to the ship.
 * @param num_shots Number of shots.
 * @return STATUS code.
 */
STATUS ship_set_num_shots(SHIP *ship, long num_shots) {
    if (!ship || num_shots < 0) {
        return ERROR;
    } 

    ship->num_shots = num_shots;

    return OK;
}

/**
 * @brief Gets the number of shots fired by the ship.
 * 
 * @param ship Pointer to the ship.
 * @return The number of shots or ERROR if ship is NULL.
 */
long ship_get_num_shots(SHIP *ship) {
    if (!ship) {
        return ERROR;
    } 

    return ship->num_shots;
}

/**
 * @brief Sets the ship's life.
 * 
 * @param ship Pointer to the ship.
 * @param life New life value.
 * @return STATUS code.
 */
STATUS ship_set_life(SHIP *ship, int life) {
    if (!ship) {
        return ERROR;
    }

    ship->life = life;

    return OK;
}

/**
 * @brief Gets the current life of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's life or 0 if ship is NULL.
 */
int ship_get_life(SHIP *ship) {
    if (!ship) {
        return 0;
    }

    return ship->life;
}

/**
 * @brief Gets the width of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's width or 0 if ship is NULL.
 */
int ship_get_width(SHIP *ship) {
    if (!ship) {
        return 0;
    }

    return ship->width;
}

/**
 * @brief Gets the height of the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Ship's height or 0 if ship is NULL.
 */
int ship_get_height(SHIP *ship) {
    if (!ship) {
        return 0;
    }

    return ship->height;
}

/**
 * @brief Decreases the life of the ship by a specified amount.
 * 
 * @param ship Pointer to the ship.
 * @param amount Amount to decrease.
 * @return STATUS code.
 */
STATUS ship_decrease_life(SHIP *ship, int amount) {
    if (!ship) {
        return ERROR;
    }

    if (ship->life - amount <= 0) {
        ship->life = 0;
    } else {
        ship->life -= amount;
    }

    return OK;
}

/**
 * @brief Adds a bullet to the ship's bullet array.
 * 
 * @param ship Pointer to the ship.
 * @param bullet Bullet to add.
 * @return STATUS code.
 */
STATUS ship_add_bullet(SHIP *ship, BULLET *bullet) {
    if (!ship || !bullet || ship->num_shots >= MAX_SHIP_BULLETS) {
        return ERROR;
    }

    ship->bullets[ship->num_shots] = bullet;
    ship->num_shots++;

    return OK;
}

/**
 * @brief Removes and returns the oldest bullet from the ship's bullet array (FIFO).
 * 
 * @param ship Pointer to the ship.
 * @return Pointer to the removed bullet or NULL if no bullets are present.
 */
BULLET *ship_dequeue_bullet(SHIP *ship) { // Las balas se comportan como una cola
    BULLET *bullet = NULL;

    if (ship != NULL && ship->num_shots > 0) {
        bullet = ship->bullets[0];
        ship->bullets[0] = NULL;

        for (int i = 0; i < ship->num_shots - 1; i++) {
            ship->bullets[i] = ship->bullets[i + 1];
        }

        ship->num_shots--;
        ship->bullets[ship->num_shots] = NULL;
    }

    return bullet;
}

/**
 * @brief Removes and returns a specific bullet at index i from the ship's bullet array.
 * 
 * @param ship Pointer to the ship.
 * @param i Index of bullet to remove.
 * @return Pointer to the removed bullet or NULL if index is invalid.
 */
BULLET *ship_extract_bullet_at(SHIP* ship, int i) { // Las balas se comportan como una lista dinamica
    BULLET *bullet = NULL;

    if (ship != NULL && ship->num_shots > 0) {
        if (i >= 0 && i < ship->num_shots ) {
            if (ship->bullets[i] != NULL) {
                bullet = ship->bullets[i];

                // Desplazamos todas las balas restantes hacia adelante
                for (int j = i; j < ship->num_shots - 1; j++) {
                    ship->bullets[j] = ship->bullets[j + 1];
                }

                // Reducimos el contador de balas y aseguramos que el último espacio sea NULL
                ship->num_shots--;
                ship->bullets[ship->num_shots] = NULL;
            }
        }
    }
    
    return bullet;
}

/**
 * @brief Retrieves a bullet at the specified index.
 * 
 * @param ship Pointer to the ship.
 * @param i Index of bullet.
 * @return Pointer to the bullet or NULL if index is invalid.
 */
BULLET *ship_get_bullet_at(SHIP *ship, int i) {
    if (!ship || i < 0 || i >= ship->num_shots) {
        return NULL;
    }

    return ship->bullets[i];
}

/**
 * @brief Moves all bullets of the ship upwards by a given speed.
 * 
 * @param ship Pointer to the ship.
 * @param speed Speed of bullet movement.
 * @return STATUS code.
 */
STATUS ship_move_bullet(SHIP *ship, float speed) { // Pasar los limites por parametro
    int top_limit = (0 + FRAME_WIDTH_SUP + 50); // Customizable top limit

    if (!ship) {
        return ERROR;
    }

    for (int i = 0; i < ship->num_shots && ship->bullets[i] != NULL; i++) {
        if (bullet_get_y(ship->bullets[i]) - speed > top_limit) { // Comprobar si ha llegado a arriba (0)
            if (bullet_move(ship->bullets[i], speed) == ERROR) {
                return ERROR;
            }
        } else {
            if (bullet_destroy(ship_extract_bullet_at(ship, i)) == ERROR) {
                return ERROR;
            }
        }
    }

    return OK;
}

/**
 * @brief Fires a new bullet from the ship.
 * 
 * @param ship Pointer to the ship.
 * @param bitmap Bitmap for the bullet.
 * @return STATUS code.
 */
STATUS ship_shoot(SHIP *ship, ALLEGRO_BITMAP *bitmap) {
    BULLET *new_bullet = NULL;

    if (!ship || !bitmap) {
        return ERROR;
    }

    if (ship->num_shots > MAX_SHIP_BULLETS) {
        return ERROR;
    }

    if (ship->num_shots == MAX_SHIP_BULLETS) {
        return OK;
    }

    new_bullet = bullet_create(bitmap, 6, 12, ship->x + 12, ship->y, UP); // La bullet se situa a 12 por encima
    if (new_bullet == NULL) {
        return ERROR;
    }

    if (ship_add_bullet(ship, new_bullet) == ERROR) {
        bullet_destroy(new_bullet);
        return ERROR;
    }

    return OK;
}


/**
 * @brief Moves the ship based on its direction and speed.
 * 
 * @param ship Pointer to the ship.
 * @param speed Speed of movement.
 * @return STATUS code.
 */
STATUS ship_move(SHIP *ship, float speed) { // Pedir los limites por parametro
    if (!ship) {
        return ERROR;
    }

    if (ship->dir == RIGHT) {
        ship->x += speed;
    } else if (ship->dir == LEFT) {
        ship->x -= speed;
    } else {
        ship->dir = NO_DIR;
    }

    return OK;
}

/**
 * @brief Renders the ship at its current position.
 * 
 * @param ship Pointer to the ship.
 * @return STATUS code.
 */
STATUS ship_print(SHIP *ship) {
    if (!ship) {
        return ERROR;
    }

    al_draw_bitmap_region(ship->bitmap, (ship->source_x * ship->width), (ship->source_y * ship->height), 
        ship->width, ship->height, ship->x, ship->y, 0);

    return OK;
}

/**
 * @brief Updates the ship's internal timer for controlling firing rate.
 * 
 * @param ship Pointer to the ship.
 * @param max_time Maximum timer threshold for firing.
 */
void ship_set_timer(SHIP *ship, int max_time) { // Para controlar la cadencia de disparo (la frecuencia)
    if (!ship) {
        return;
    }

    ship->timer++;
    if (ship->timer >= max_time) { // (ship->timer++ >= num) temporizador para las balas
        ship->timer = 0;
    }

    return;
}

/**
 * @brief Retrieves the current timer value for the ship.
 * 
 * @param ship Pointer to the ship.
 * @return Timer value or -1 if ship is NULL.
 */
int ship_get_time(SHIP *ship) {
    if (!ship) {
        return -1;
    }

    return ship->timer;
}

/**
 * @brief Checks if the ship occupies a specific location.
 * 
 * @param ship Pointer to the ship.
 * @param x X-coordinate to check.
 * @param y Y-coordinate to check.
 * @return true if the ship is at (x, y), false otherwise.
 */
bool ship_some_loc(SHIP *ship, int x, int y) {
    if (!ship) {
        return false;
    }

    if (ship->x == x) {
        if (ship->y == y) {
            return true;
        }
    }

    return false;
}