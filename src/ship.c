/**
 * @file ship.c
 * @brief Manages the creation, movement, and behavior of the ship in the Space
 * Invaders game.
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
  float x, y;                        ///< Ship's coordinates
  int dir;                           ///< Ship's direction (e.g., LEFT, RIGHT)
  ALLEGRO_BITMAP *bitmap;            ///< Ship's bitmap image
  BULLET *bullets[MAX_SHIP_BULLETS]; ///< Array holding ship's bullets
  long num_shots;                    ///< Number of bullets currently in use
  bool active;                       ///< Ship's active state
  int source_x, source_y;            ///< Source coordinates in bitmap for rendering
  int width, height;                 ///< Dimensions of the ship
  int life;                          ///< Remaining life of the ship
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
SHIP *ship_create(ALLEGRO_BITMAP *bitmap, int width, int height, float x,
                  float y, int dir, int life) {
  SHIP *new_ship = NULL;

  if (!bitmap) {
    return NULL;
  }

  new_ship = (SHIP *)malloc(sizeof(SHIP));
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

  new_ship->active = false;

  // Inicializacion de punteros a bullet
  for (int i = 0; i < MAX_SHIP_BULLETS; i++) { 
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
STATUS ship_destroy(SHIP *ship) { // Destruir ship
  STATUS result = OK;

  if (ship != NULL) {
    for (int i = 0; i < MAX_SHIP_BULLETS; i++) {
      if (ship->bullets[i] != NULL) {
        if (bullet_destroy(ship->bullets[i]) == ERROR) {
          result = ERROR;
        }
      }
    }
    free(ship);
  }

  return result;
}

/**
 * @brief Sets the x-coordinate of the ship.
 *
 * @param ship Pointer to the ship.
 * @param x New x-coordinate.
 * @return STATUS code (OK on success, ERROR on failure).
 */
STATUS ship_set_x(SHIP *ship, float x) {
  if (ship != NULL) {
    ship->x = x;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current x-coordinate of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The x-coordinate, or -1.0 if ship is NULL.
 */
float ship_get_x(SHIP *ship) {
  if (ship != NULL) {
    return ship->x;
  }
  return -1.0;
}

/**
 * @brief Sets the y-coordinate of the ship.
 *
 * @param ship Pointer to the ship.
 * @param y New y-coordinate.
 * @return STATUS code.
 */
STATUS ship_set_y(SHIP *ship, float y) {
  if (ship != NULL) {
    ship->y = y;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current y-coordinate of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The y-coordinate, or -1.0 on failure.
 */
float ship_get_y(SHIP *ship) {
  if (ship != NULL) {
    return ship->y;
  }
  return -1.0;
}

/**
 * @brief Sets the direction of the ship.
 *
 * @param ship Pointer to the ship.
 * @param dir New direction value.
 * @return STATUS code.
 */
STATUS ship_set_dir(SHIP *ship, int dir) {
  if (ship != NULL) {
    ship->dir = dir;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current direction of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The direction value, or -1 on failure.
 */
int ship_get_dir(SHIP *ship) {
  if (ship != NULL) {
    return ship->dir;
  }
  return -1;
}

/**
 * @brief Sets the bitmap image of the ship.
 *
 * @param ship Pointer to the ship.
 * @param bitmap Pointer to the new bitmap.
 * @return STATUS code.
 */
STATUS ship_set_bitmap(SHIP *ship, ALLEGRO_BITMAP *bitmap) {
  if (ship != NULL && bitmap != NULL) {
    ship->bitmap = bitmap;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the bitmap image of the ship.
 *
 * @param ship Pointer to the ship.
 * @return Pointer to the ship's bitmap, or NULL if ship is NULL.
 */
ALLEGRO_BITMAP *ship_get_bitmap(SHIP *ship) {
  if (ship != NULL) {
    return ship->bitmap;
  }
  return NULL;
}

/**
 * @brief Sets the active state of the ship.
 *
 * @param ship Pointer to the ship.
 * @param active New active state.
 * @return STATUS code.
 */
STATUS ship_set_active(SHIP *ship, bool active) {
  if (ship != NULL) {
    ship->active = active;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current active state of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The active state (true/false).
 */
bool ship_get_active(SHIP *ship) {
  if (ship != NULL) {
    return ship->active;
  }
  return false;
}

/**
 * @brief Sets the source x offset for the ship's bitmap rendering.
 *
 * @param ship Pointer to the ship.
 * @param source_x New source x value.
 * @return STATUS code.
 */
STATUS ship_set_source_x(SHIP *ship, int source_x) {
  if (ship != NULL) {
    ship->source_x = source_x;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current source x offset of the ship's bitmap.
 *
 * @param ship Pointer to the ship.
 * @return The source x value, or -1 on failure.
 */
int ship_get_source_x(SHIP *ship) {
  if (ship != NULL) {
    return ship->source_x;
  }
  return -1;
}

/**
 * @brief Sets the source y offset for the ship's bitmap rendering.
 *
 * @param ship Pointer to the ship.
 * @param source_y New source y value.
 * @return STATUS code.
 */
STATUS ship_set_source_y(SHIP *ship, int source_y) {
  if (ship != NULL) {
    ship->source_y = source_y;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current source y offset of the ship's bitmap.
 *
 * @param ship Pointer to the ship.
 * @return The source y value, or -1 on failure.
 */
int ship_get_source_y(SHIP *ship) {
  if (ship != NULL) {
    return ship->source_y;
  }
  return -1;
}

/**
 * @brief Sets the current number of shots (bullets) the ship has fired.
 *
 * @param ship Pointer to the ship.
 * @param num_shots New number of shots.
 * @return STATUS code.
 */
STATUS ship_set_num_shots(SHIP *ship, long num_shots) {
  if (ship != NULL) {
    ship->num_shots = num_shots;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the current number of bullets the ship has fired.
 *
 * @param ship Pointer to the ship.
 * @return The number of shots, or -1 on failure.
 */
long ship_get_num_shots(SHIP *ship) {
  if (ship != NULL) {
    return ship->num_shots;
  }
  return -1;
}

/**
 * @brief Sets the life points for the ship.
 *
 * @param ship Pointer to the ship.
 * @param life New life value.
 * @return STATUS code.
 */
STATUS ship_set_life(SHIP *ship, int life) {
  if (ship != NULL) {
    ship->life = life;
    return OK;
  }
  return ERROR;
}

/**
 * @brief Gets the remaining life points of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The life points, or -1 on failure.
 */
int ship_get_life(SHIP *ship) {
  if (ship != NULL) {
    return ship->life;
  }
  return -1;
}

/**
 * @brief Gets the width of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The width, or -1 on failure.
 */
int ship_get_width(SHIP *ship) {
  if (ship != NULL) {
    return ship->width;
  }
  return -1;
}

/**
 * @brief Gets the height of the ship.
 *
 * @param ship Pointer to the ship.
 * @return The height, or -1 on failure.
 */
int ship_get_height(SHIP *ship) {
  if (ship != NULL) {
    return ship->height;
  }
  return -1;
}

/**
 * @brief Renders the ship on the screen.
 *
 * @param ship Pointer to the ship to print.
 * @return STATUS code.
 */
STATUS ship_print(SHIP *ship) {
  if (ship != NULL && ship->bitmap != NULL) {
    al_draw_bitmap_region(ship->bitmap, (ship->source_x * ship->width),
                          (ship->source_y * ship->height), ship->width,
                          ship->height, ship->x, ship->y, 0);

    return OK;
  }
  return ERROR;
}

/**
 * @brief Decreases the life points of the ship.
 *
 * @param ship Pointer to the ship.
 * @param value Amount to decrease.
 * @return STATUS code.
 */
STATUS ship_decrease_life(SHIP *ship, int value) {
  if (ship != NULL) {
    ship->life -= value;
    return OK;
  }
  return ERROR;
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
 * @brief Removes and returns the oldest bullet in the ship's queue.
 *
 * @param ship Pointer to the ship.
 * @return The oldest bullet, or NULL if no bullets are found.
 */
BULLET *ship_dequeue_bullet(SHIP *ship) {
  BULLET *bullet = NULL;

  if (ship != NULL && ship->num_shots > 0) {
    bullet = ship->bullets[0];

    for (int i = 0; i < ship->num_shots - 1; i++) {
      ship->bullets[i] = ship->bullets[i + 1];
    }

    ship->num_shots--;
    ship->bullets[ship->num_shots] = NULL;
  }

  return bullet;
}

/**
 * @brief Removes and returns the bullet at a specified index.
 *
 * @param ship Pointer to the ship.
 * @param i Index of bullet to remove.
 * @return Pointer to the removed bullet or NULL if index is invalid.
 */
 // Las balas se comportan como una lista dinamica, se pueden eliminar 
 // en cualquier orden, pero se deben desplazar las balas restantes 
 // para mantener la continuidad de la lista
BULLET *ship_extract_bullet_at(SHIP *ship, int i) {
  BULLET *bullet = NULL;

  if (ship != NULL && ship->num_shots > 0) {
    if (i >= 0 && i < ship->num_shots) {
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
 // Pasar los limites por parametro
STATUS ship_move_bullet(SHIP *ship, float speed) { 
  int top_limit = 160; // Limite justo debajo de la UI

  if (!ship) {
    return ERROR;
  }

  for (int i = ship->num_shots - 1; i >= 0; i--) {
    // Comprobar si ha llegado a arriba (0)
    if (bullet_get_y(ship->bullets[i]) - speed > top_limit) {
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

  if (ship->num_shots >= MAX_SHIP_BULLETS) {
    return ERROR;
  }

  // La bullet se situa a 12 por encima
  new_bullet = bullet_create(bitmap, 6, 12, ship->x + 12, ship->y, UP);
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
  ship->x += speed;
  return OK;
}

/**
 * @brief Check if the ship is in the position (x, y)
 *
 * @param ship Pointer to the ship.
 * @param x x position.
 * @param y y position.
 * @return bool.
 */
bool ship_some_loc(SHIP *ship, int x, int y) {
  if (!ship) {
    return false;
  }

  if (x >= ship->x && x <= ship->x + ship->width && y >= ship->y &&
      y <= ship->y + ship->height) {
    return true;
  }

  return false;
}