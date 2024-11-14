/**
 * @file game.h
 * @brief Declaration of the Game structure and its associated functions.
 *
 * This header defines the structure and essential functions to manage 
 * the game state, including initialization, updates, and rendering.
 * It encapsulates all the components involved in the game's main loop.
 * 
 * Author: RGiskard7
 * Date: 13/11/2024
 */

#include "game.h"

/**
 * @struct _game
 * @brief Main game structure containing all game components and state variables.
 *
 * Holds the display, bitmaps, timers, and other components necessary to run
 * the game. It manages player actions, enemies, bullets, and other objects in 
 * the game world.
 */
struct _game {
    ALLEGRO_DISPLAY *screen;                 ///< Main display 
    ALLEGRO_BITMAP *background;              ///< Background image
    ALLEGRO_BITMAP *frame;                   ///< Frame surrounding the screen
    ALLEGRO_BITMAP *ship_img;                ///< Player ship image 
    ALLEGRO_BITMAP *ship_bullet_img;         ///< Image for the player's bullets
    ALLEGRO_BITMAP *martian_img;             ///< Image for martians
    ALLEGRO_BITMAP *martian_explosion_img;   ///< Image for martian explosions
    ALLEGRO_BITMAP *martian_bullet_img;;     ///< Image for martian bullets
    ALLEGRO_FONT *font;                      ///< Font used in the game

    ALLEGRO_TIMER *timer;                    ///< Main game timer
    ALLEGRO_EVENT_QUEUE *event_queue;        ///< Event queue for managing game events
    ALLEGRO_EVENT events;                    ///< Structure to store current event

    SHIP *ship;                              ///< Player ship instance
    MARTIAN *enemy[MAX_ENEMIES];             ///< Array of enemy instances
    BULLET *orphan_bullets[MAX_ORP_BULLETS]; ///< Array of bullets without an owner
    OBJECT *objects[MAX_OBJECTS];            ///< Array of other objects in the game

    float FPS;                               ///< Frames per second for the game
    bool done, draw;                         ///< Flags to track game state

    int num_enemies_destroyed;               ///< Number of destroyed enemies
    int num_enemies_alive;                   ///< Number of remaining enemies
    int last_enemy_rand;                     ///< Last randomly selected enemy
    int enemy_shoot_timer;                   ///< Timer for enemy shooting frequency
    int enemy_animation_timer;               ///< Timer for enemy animation
    int enemy_move_timer;                    ///< Timer for enemy movement
    float enemies_dir;                       ///< Direction of enemy movement

    int num_orphan_bullets;                  ///< Count of orphaned bullets
    int num_objects;                         ///< Count of other game objects
    
    int total_score;                         ///< Player's total score
};

// Function Declarations

STATUS game_martian_shoot(GAME *game, int i);       /**< Handles martian shooting */
STATUS game_move_martians(GAME *game, float speed); /**< Moves martians */
STATUS game_destroy_martian(GAME *game, int i);     /**< Destroys specified martian */
STATUS game_colisions(GAME *game);                  /**< Checks for collisions */

STATUS game_ship_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key); /**< Updates ship based on input */
STATUS game_martians_update(GAME *game);                          /**< Updates all martians */
STATUS game_animations_update(GAME *game);                        /**< Updates animations */

STATUS game_add_orphan_bullet(GAME *game, BULLET *bullet);        /**< Adds an orphan bullet */
BULLET *game_dequeue_orphan_bullet(GAME *game);                   /**< Dequeues an orphan bullet */
BULLET *game_get_orphan_bullet_at(GAME *game, int i);             /**< Gets a specific orphan bullet */
STATUS game_move_orphan_bullets(GAME *game, float speed);         /**< Moves orphan bullets */

STATUS game_add_object(GAME *game, OBJECT *object);               /**< Adds an object to the game */
OBJECT *game_dequeue_object(GAME *game);                          /**< Removes an object from the game */
OBJECT *game_get_object_at(GAME *game, int i);                    /**< Gets a specific object */

STATUS game_print_ship(GAME *game);                               /**< Renders the player's ship */
STATUS game_print_enemies(GAME *game);                            /**< Renders all enemies */
STATUS game_print_orphan_bullets(GAME *game);                     /**< Renders orphan bullets */
STATUS game_print_other_elements(GAME *game);                     /**< Renders other game elements */
STATUS game_print_score(GAME *game);                              /**< Renders the score */
STATUS game_print_life(GAME *game);                               /**< Renders the player's lives */
STATUS game_print_floor(GAME *game);                              /**< Renders the floor */


// Game Management Functions

/**
 * @brief Creates and initializes a new game instance.
 * 
 * Allocates memory for the GAME structure and sets initial values for all
 * components and state variables.
 * 
 * @return Pointer to the new GAME instance or NULL if allocation fails.
 */
GAME *game_create() {
    GAME *new_game = NULL;

    new_game = (GAME*) malloc(sizeof (GAME));
    if (!new_game) {
        return NULL;
    }

    new_game->screen = NULL;
    new_game->background = NULL;
    new_game->frame = NULL;
    new_game->ship_img = NULL;
    new_game->ship_bullet_img = NULL;
    new_game->martian_img = NULL;
    new_game->martian_bullet_img = NULL;
    new_game->martian_explosion_img = NULL;
    new_game->font = NULL;

    new_game->timer = NULL;
    new_game->event_queue = NULL;

    new_game->ship = NULL;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        new_game->enemy[i] = NULL;
    }

    for (int i = 0; i < MAX_ORP_BULLETS; i++) {
        new_game->orphan_bullets[i] = NULL;
    }

    for (int i = 0; i < MAX_OBJECTS; i++) {
        new_game->objects[i] = NULL;
    }

    new_game->FPS = 0.0;
    new_game->draw = false;
    new_game->done = false;
    
    new_game->num_enemies_destroyed = 0;
    new_game->num_enemies_alive = 0;
    new_game->last_enemy_rand = 0;

    new_game->enemy_shoot_timer = 0;
    new_game->enemy_animation_timer = 0;
    new_game->enemy_move_timer = 0;
    new_game->enemies_dir = RIGHT;

    new_game->num_orphan_bullets = 0;
    new_game->num_objects = 0;

    new_game->total_score = 0;

    return new_game;
}

/**
 * @brief Destroys the game instance and frees all associated resources.
 *
 * Destroys all loaded images, fonts, and any dynamically allocated memory,
 * as well as clearing event queues and timers.
 *
 * @param game Pointer to the GAME instance to be destroyed.
 * @return OK if successful, ERROR if the game pointer is NULL.
 */
STATUS game_destroy(GAME *game) {
    int i = 0;

    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < game->num_objects; i++) {
        obj_destroy(game->objects[i]);
        game->objects[i] = NULL;
    }

    for (int i = 0; i < game->num_orphan_bullets; i++) {
        bullet_destroy(game->orphan_bullets[i]);
        game->orphan_bullets[i] = NULL;
    }


    for (int i = 0; i < game->num_enemies_alive; i++) {
        mart_destroy(game->enemy[i]);
        game->enemy[i] = NULL;
    }

    if (game->ship) { //eliminacion del jugador
        ship_destroy(game->ship); 
        game->ship = NULL;
    }
    
    if (game->event_queue) { //eliminacion de la pila de eventos
        al_destroy_event_queue(game->event_queue); 
        game->event_queue = NULL;
    }

    if (game->font) {
        al_destroy_font(game->font);
    }

    if (game->martian_explosion_img) {
        al_destroy_bitmap(game->martian_explosion_img); 
        game->martian_explosion_img = NULL;
    }

    if (game->martian_bullet_img) {
        al_destroy_bitmap(game->martian_bullet_img); 
        game->martian_bullet_img = NULL;
    }

    if (game->martian_img) {
        al_destroy_bitmap(game->martian_img); 
        game->martian_img = NULL;
    }

    if (game->ship_bullet_img) {
        al_destroy_bitmap(game->ship_bullet_img); 
        game->ship_bullet_img = NULL;
    }

    if (game->ship_img) {
        al_destroy_bitmap(game->ship_img); 
        game->ship_img = NULL;
    }

    if (game->frame) {
        al_destroy_bitmap(game->frame); //eliminacion del marco
        game->frame = NULL;
    }

    if (game->background) { //eliminacion del fondo
        al_destroy_bitmap(game->background); 
        game->background = NULL;
    }

    if (game->screen) {
        al_destroy_display(game->screen); //elimiacion de la pantalla
        game->screen = NULL;
    }

    if (game->timer) {
        al_destroy_timer(game->timer); //eliminacion del temporizador
        game->timer = NULL;
    }

    free(game); //eliminacion de la estructura GAME
    game = NULL;

    return OK;
}

/**
 * @brief Initializes the game with provided FPS and sets up the display, bitmaps, 
 * fonts, and other resources.
 *
 * This function loads images, initializes timers, creates the player ship, 
 * and generates enemy instances.
 *
 * @param game Pointer to the GAME instance.
 * @param FPS Frames per second setting for the game.
 * @return OK if initialization succeeds, ERROR if any setup fails.
 */
STATUS game_init(GAME *game, float FPS) {
    if (!game) {
        return ERROR;
    }

    game->FPS = FPS; //FPS del game
    game->timer = al_create_timer(1.0 / game->FPS); //Creacion del tiempo del game

    if (!game->timer) {        
        return ERROR;
    }

    game->screen = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); //Creacion de pantalla
    if (!game->screen) {
        return ERROR;
    }

    game->background = al_load_bitmap(BACKGROUND_IMG_RSC);
    if (!game->background) {
        return ERROR;
    }

    game->frame = al_load_bitmap(FRAME_IMG_RSC);
    if (!game->frame) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->frame, al_map_rgb(255, 0, 255)); // Que el color magenta sea tratado como transparente

    game->ship_img = al_load_bitmap(SHIP_IMG_RSC);
    if (!game->ship_img) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->ship_img, al_map_rgb(255, 0, 255));

    game->ship_bullet_img = al_load_bitmap(SHIP_BULLET_IMG_RSC);
    if (!game->ship_bullet_img) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->ship_bullet_img, al_map_rgb(255, 0, 255));

    game->martian_img = al_load_bitmap(MARTIAN_IMG_RSC);
    if (!game->martian_img) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->martian_img, al_map_rgb(255, 0, 255));

    game->martian_bullet_img = al_load_bitmap(MART_BULLET_IMG_RSC);
    if (!game->martian_bullet_img) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->martian_bullet_img, al_map_rgb(255, 0, 255));

    game->martian_explosion_img = al_load_bitmap(EXPLOSION_IMG_RSC);
    if (!game->martian_explosion_img) {
        return ERROR;
    }
    al_convert_mask_to_alpha(game->martian_explosion_img, al_map_rgb(255, 0, 255));
 
    game->font = al_load_ttf_font(FONT_RSC, 18, 0); // 24 es el tamaño de la fuente
        if (!game->font) {
        return ERROR;
    }

    game->event_queue = al_create_event_queue(); //Creacion de pila de eventos del game
    if (!game->event_queue) {
        return ERROR;
    }

    game->ship = ship_create(game->ship_img, SHIP_WIDTH, SHIP_HEIGHT, SHIP_INIT_POS_X, SHIP_INIT_POS_Y, NO_DIR, SHIP_LIFE); //Creacion de nave
    if (!game->ship) {
        return ERROR;
    }

    for (int y = 0, i = 0; y < NUM_ENEMY_Y; y++) { //Creacion de enemigos
        int source_y, score;

        if (i <= 10) {
            source_y = 0;
            score = POINTS_01;
        } else if (i > 10 && i <= 31) {
            source_y = 1;
            score = POINTS_02;
        } else {
            source_y = 2;
            score = POINTS_03;
        }

        for (int x = 0; x < NUM_ENEMY_X; x++) {
            game->enemy[i] = mart_create(game->martian_img, MART_WIDTH, MART_HEIGHT, 
                MART_INIT_POS_X + x * SPACE_BTW_MARTIANS_X, MART_INIT_POS_Y + y * SPACE_BTW_MARTIANS_Y, &(game->enemies_dir), score);

            if (!game->enemy[i]) {
                return ERROR;
            }

            mart_set_source_y(game->enemy[i], source_y); //tipo de enemigo
            i++;
        }
    }

    game->num_enemies_alive = MAX_ENEMIES;

    return OK;
}

/**
 * @brief Returns the main display of the game.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to ALLEGRO_DISPLAY or NULL if game is NULL.
 */
ALLEGRO_DISPLAY *game_get_screen(GAME *game) {
    if (!game) {
        return NULL;
    }

    return game->screen;
}

/**
 * @brief Returns the main timer of the game.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to ALLEGRO_TIMER or NULL if game is NULL.
 */
ALLEGRO_TIMER *game_get_timer(GAME *game) {
    if (!game) {
        return NULL;
    }

    return game->timer;
}

/**
 * @brief Returns the event queue for the game.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to ALLEGRO_EVENT_QUEUE or NULL if game is NULL.
 */
ALLEGRO_EVENT_QUEUE *game_get_ev_queue(GAME *game) {
    if (!game) {
        return NULL;
    }

    return game->event_queue;
}

/**
 * @brief Returns the latest event from the game's event structure.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to ALLEGRO_EVENT or NULL if game is NULL.
 */
ALLEGRO_EVENT *game_get_event(GAME *game) {
    if (!game) {
        return NULL;
    }

    return &game->events;
}

/**
 * @brief Checks if the game has finished.
 *
 * @param game Pointer to the GAME instance.
 * @return true if the game is marked as done, false otherwise.
 */
bool game_is_done(GAME *game) {
    if (!game) {
        return ERROR;
    }

    return game->done;
}

// Martian Game Functions

/**
 * @brief Sets a randomly chosen martian as the shooter.
 *
 * @param game Pointer to the GAME instance.
 * @param last_rand Index of the randomly chosen martian.
 * @return OK if successful, ERROR if game is NULL.
 */
STATUS game_set_rand_enemy(GAME *game, int last_rand) {
    if (!game) {
        return ERROR;
    }

    game->last_enemy_rand = last_rand;

    return OK;
}

/**
 * @brief Initiates a shooting action for the specified martian.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the martian to shoot.
 * @return OK if successful, ERROR if the game or index is invalid.
 */
STATUS game_martian_shoot(GAME *game, int i) {
    if (!game) {
        return ERROR;
    }

    if (i < 0 || i >= MAX_ENEMIES) {
        return ERROR;
    }

    return mart_shoot(game->enemy[i], game->martian_bullet_img);
}

/**
 * @brief Moves all martians by the specified speed and updates their direction as necessary.
 *
 * This function adjusts the movement of all martians and ensures that 
 * direction changes occur when they reach screen boundaries.
 *
 * @param game Pointer to the GAME instance.
 * @param speed Movement speed for the martians.
 * @return OK if successful, ERROR if game is NULL.
 */
STATUS game_move_martians(GAME *game, float speed) {
    MARTIAN *martian = NULL;
    int right_limit = (CANVAS_WIDTH - 32);
    int left_limit = FRAME_WIDTH;
    int bottom_limit = (DISPLAY_HEIGHT - (FRAME_WIDTH * 2)) - 10;
    int cx, cy;
    
    if (!game) {
        return ERROR;
    }

    if (game->enemies_dir != NO_DIR) { // Se mueven todos los marcianos
        for(int i = 0; i < game->num_enemies_alive && game->enemy[i] != NULL; i++) {
            martian = game->enemy[i];
            cx = mart_get_x(martian);
            cy = mart_get_y(martian);

            if (game->enemies_dir == DOWN) {
                if (cx + speed >= right_limit) {
                    game->enemies_dir = LEFT;
                    i = game->num_enemies_alive; // Break
                } else if (cx - speed <= left_limit) {
                    game->enemies_dir = RIGHT;
                    i = game->num_enemies_alive;
                }

            } else if (cx + speed >= right_limit || cx - speed <= left_limit) {
                game->enemies_dir = DOWN;
                i = game->num_enemies_alive;

            } else if (cy + MART_HEIGHT >= bottom_limit) {
                game->enemies_dir = NO_DIR;
                i = game->num_enemies_alive;
            }
        }

        for(int i = 0; i < game->num_enemies_alive && game->enemy[i] != NULL; i++) {
            martian = game->enemy[i];
            mart_move(martian, speed);
        }
    }

    return OK;
}

/**
 * @brief Destroys a specific martian and removes it from the game.
 *
 * The function also shifts remaining enemies in the array to fill the 
 * empty position.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the martian to destroy.
 * @return OK if successful, ERROR if the game or index is invalid.
 */
STATUS game_destroy_martian(GAME* game, int i) { // Cambiar estructura y devolver martian
    if (!game || game->num_enemies_alive <= 0) {
        return ERROR;
    }

    if (i < 0 || i >= game->num_enemies_alive) {
        return ERROR;
    }

    if (mart_destroy(game->enemy[i]) == ERROR) {
        return ERROR;
    }

    // Desplazamos todos los enemigos restantes hacia adelante
    for (int j = i; j < game->num_enemies_alive - 1; j++) {
        game->enemy[j] = game->enemy[j + 1];
    }

    // Aseguramos que el último espacio ahora sea NULL
    game->enemy[game->num_enemies_alive - 1] = NULL;

    game->num_enemies_destroyed++;
    game->num_enemies_alive--;

    return OK;
}

// ORPHAN BULLET GAMES FUNCTION

/**
 * @brief Adds an orphan bullet to the game's orphan bullet list.
 *
 * @param game Pointer to the GAME instance.
 * @param bullet Pointer to the BULLET to be added.
 * @return OK if the bullet is added successfully, ERROR if game, bullet, 
 *         or the limit of orphan bullets is exceeded.
 */
STATUS game_add_orphan_bullet(GAME *game, BULLET *bullet) {
    if (!game || !bullet || game->num_orphan_bullets >= MAX_ORP_BULLETS) {
        return ERROR;
    }

    game->orphan_bullets[game->num_orphan_bullets] = bullet;
    game->num_orphan_bullets++;

    return OK;
}

/**
 * @brief Removes and returns the first orphan bullet in the game.
 *
 * Dequeues an orphan bullet, shifts the remaining bullets forward, and 
 * decreases the orphan bullet count.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to the removed bullet or NULL if there are no orphan bullets.
 */
BULLET *game_dequeue_orphan_bullet(GAME *game) {
    BULLET *bullet = NULL;

    if (game != NULL && game->num_orphan_bullets > 0) {
        bullet = game->orphan_bullets[0];
        game->orphan_bullets[0] = NULL;

        for (int i = 0; i < game->num_orphan_bullets - 1; i++) {
            game->orphan_bullets[i] = game->orphan_bullets[i + 1];
        }

        game->num_orphan_bullets--;
        game->orphan_bullets[game->num_orphan_bullets] = NULL; // Nulificación del último elemento
    }

    return bullet;
}

/**
 * @brief Retrieves the orphan bullet at the specified index.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the orphan bullet.
 * @return Pointer to the bullet at index i or NULL if index is out of range.
 */
BULLET *game_get_orphan_bullet_at(GAME *game, int i) {
    if (!game || i < 0 || i >= game->num_orphan_bullets) {
        return NULL;
    }

    return game->orphan_bullets[i];
}

/**
 * @brief Moves all orphan bullets in the game by a specified speed.
 *
 * If a bullet exceeds the bottom limit, it is removed from the orphan bullets list.
 *
 * @param game Pointer to the GAME instance.
 * @param speed Movement speed of the orphan bullets.
 * @return OK if successful, ERROR if game is NULL.
 */
STATUS game_move_orphan_bullets(GAME *game, float speed) {
    int bottom_limit = CANVAS_HEIGTH;

    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < game->num_orphan_bullets; i++) {  // Se mueven las balas huerfanas del juego
        if (bullet_get_y(game->orphan_bullets[i]) + speed < bottom_limit) { // Revisar
            if (bullet_move(game->orphan_bullets[i], speed) == ERROR) {
                return ERROR;
            }
        } else {
            if (bullet_destroy(game_dequeue_orphan_bullet(game)) == ERROR) {
                return ERROR;
            }
        }
    }

    return OK;
}

// OBJECTS GAMES FUNCTION

/**
 * @brief Adds an object to the game's object list.
 *
 * @param game Pointer to the GAME instance.
 * @param object Pointer to the OBJECT to be added.
 * @return OK if the object is added successfully, ERROR if game, object, 
 *         or the limit of objects is exceeded.
 */
STATUS game_add_object(GAME *game, OBJECT *object) {
    if (!game || !object|| game->num_objects >= MAX_OBJECTS) {
        return ERROR;
    }

    game->objects[game->num_objects] = object;
    game->num_objects++;

    return OK;
}

/**
 * @brief Removes and returns the first object in the game's object list.
 *
 * Dequeues an object, shifts the remaining objects forward, and decreases the object count.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to the removed object or NULL if there are no objects.
 */
OBJECT *game_dequeue_object(GAME *game) {
    OBJECT *object = NULL;

    if (game != NULL && game->num_objects > 0) {
        object = game->objects[0];
        game->objects[0] = NULL;

        for (int i = 0; i < game->num_objects - 1; i++) {
            game->objects[i] = game->objects[i + 1];
        }

        game->num_objects--;
        game->objects[game->num_objects] = NULL; // Nulificación del último elemento
    }

    return object;
}

/**
 * @brief Retrieves the object at the specified index.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the object.
 * @return Pointer to the object at index i or NULL if index is out of range.
 */
OBJECT *game_get_object_at(GAME *game, int i) {
    if (!game || i < 0 || i >= game->num_objects) {
        return NULL;
    }

    return game->objects[i];
}

// SHIP MOVEMENT CALLBACKS

/**
 * @brief Moves the player's ship to the left.
 *
 * Checks if the ship can move left within bounds and updates its direction.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if movement is successful, ERROR if game is NULL.
 */
STATUS callback_left(GAME * game) { // Hacer función ship_move
    float x = 0;

    if (!game) {
        return ERROR;
    } else {
        x = ship_get_x(game->ship);

        if (x - SHIP_SPEED >= FRAME_WIDTH) {
            ship_move(game->ship, SHIP_SPEED);
            ship_set_dir(game->ship, LEFT);
        }

        return OK;
    }
}

/**
 * @brief Moves the player's ship to the right.
 *
 * Checks if the ship can move right within bounds and updates its direction.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if movement is successful, ERROR if game is NULL.
 */
STATUS callback_right(GAME * game) {
    float x = 0;

    if (!game) {
        return ERROR;
    } else {
        x = ship_get_x(game->ship);

        if (x + SHIP_SPEED <= (CANVAS_WIDTH - 32)) {
            ship_move(game->ship, SHIP_SPEED);
            ship_set_dir(game->ship, RIGHT);
        }

        return OK;
    }
}

/**
 * @brief Triggers the ship's shooting action.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if shooting is successful, ERROR if game or ship's bullet image is NULL.
 */
STATUS callback_space(GAME * game) {
    if (!game) {
        return ERROR;
    }

    if (ship_shoot(game->ship, game->ship_bullet_img) == ERROR) {
        return ERROR;
    }

    return OK;
}

// Para aumentar la dificultad, aumentar la cadencia y velocidad de los marcianos, y reducir la de la nave
/**
 * @brief Updates the ship's movement, shooting actions, and bullet movement.
 *
 * Handles input for the ship's direction, space for shooting, and ESC for ending the game.
 *
 * @param game Pointer to the GAME instance.
 * @param key Pointer to the current keyboard state.
 * @return OK if update is successful, ERROR if game is NULL.
 */
STATUS game_ship_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key) {
    if (!game) {
        return ERROR;
    }

    if (ship_set_active(game->ship, true) == ERROR) { //hay que mirar si el active vale para algo
        return ERROR;
    }

    if (al_key_down(key, ALLEGRO_KEY_LEFT)) { //movimiento nave(jugador)
        callback_left(game);

    } else if (al_key_down(key, ALLEGRO_KEY_RIGHT)) {
        callback_right(game);

    } else if (al_key_down(key, ALLEGRO_KEY_SPACE) && ship_get_time(game->ship) == 0) {
        callback_space(game);

    } else {
        if (ship_set_active(game->ship, false) == ERROR) {
            return ERROR;
        }
    }
    
    if (al_key_down(key, ALLEGRO_KEY_ESCAPE)) {
        game->done = true;
    }

    ship_set_timer(game->ship, SHIP_TIMER); //temporizador para las balas de la nave 

    if (ship_move_bullet(game->ship, SHIP_BULLET_SPEED) == ERROR) { //mover bala nave
        return ERROR;
    }

    return OK;
}

/**
 * @brief Updates the martians' movement, shooting, and bullet movement.
 *
 * Uses timers to control martian shooting and movement intervals.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if update is successful, ERROR if game is NULL.
 */
STATUS game_martians_update(GAME *game) {
    if (!game) {
        return ERROR;
    }

    if (game->num_enemies_alive > 0) {
        // Si usamos el temporizador de cada marciano, se puede controlar si el mismo puede volver a disparar inmediatamente despues o no (dos temp, el del game y el de cada marciano)
        if (++game->enemy_shoot_timer >= MART_SHOOT_FREQ) { // (temporizador frecuencia) Puede que haya que sacar la frecuencia fuera
            if (game_martian_shoot(game, game->last_enemy_rand) == ERROR) {
                return ERROR;
            }
            game->enemy_shoot_timer = 0;    
        }

        if (++game->enemy_move_timer >= MART_MOVE_TIMER) {
            game_move_martians(game, MART_SPEED);
            game->enemy_move_timer = 0; 
        }

        for(int i = 0; i < game->num_enemies_alive; i++) { // Se mueven las balas de todos los marcianos que hayan disparado
            if (mart_get_num_shots(game->enemy[i]) > 0) {
                if (mart_move_bullet(game->enemy[i],  MART_BULLET_SPEED) == ERROR) { //mover bala marciano
                    return ERROR;
                }
            }
        }   
    }

    return OK;
}

/**
 * @brief Checks for collisions between all game elements.
 *
 * Detects and handles collisions between bullets and martians, as well as
 * collisions between the player's ship and martian bullets.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR if game is NULL.
 */
STATUS game_colisions(GAME * game) {
    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < ship_get_num_shots(game->ship); i++) {
        BULLET *ship_bullet = ship_get_bullet_at(game->ship, i);

        for (int j = 0; j < game->num_enemies_alive; j++) {      
            MARTIAN *martian = game->enemy[j];
            int enemy_coord_x = mart_get_x(martian);
            int enemy_coord_y = mart_get_y(martian);
            int enemy_width = mart_get_width(martian);
            int enemy_height = mart_get_height(martian);

            if (bullet_check_colision(ship_bullet, enemy_coord_x, enemy_coord_y, enemy_width, enemy_height) == true) { // Comprobar si bala nave ha chocado con marciano
                OBJECT *explosion = NULL;

                if (bullet_destroy(ship_extract_bullet_at(game->ship, i)) == ERROR) {
                    return ERROR;
                }

                for (int xi = 0; xi < mart_get_num_shots(martian); xi++) { // Pasar las balas disparadas del marcianas a huerfanas
                    BULLET *orphan_bullet = mart_extract_bullet_at(martian, xi);
                    game_add_orphan_bullet(game, orphan_bullet);
                }

                game->total_score += mart_get_score(martian);
                
                if (game_destroy_martian(game, j) == ERROR) {
                    return ERROR;
                }

                explosion = obj_create(game->martian_explosion_img, 0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, enemy_coord_x - 10, enemy_coord_y, true);
                obj_set_timer(explosion, OBJECT_TIMER);

                if (game_add_object(game, explosion) == ERROR) {
                    return ERROR;
                }

                i--;
                break;

            } else { // Comprobar si bala nave ha chocado con alguna bala del marciano
                bool exit_loop = false;

                for (int k = 0; k < mart_get_num_shots(martian); k++) {
                    BULLET *martian_bullet = mart_get_bullet_at(martian, k);
                    int bullet_coord_x = bullet_get_x(martian_bullet);
                    int bullet_coord_y = bullet_get_y(martian_bullet);
                    int bullet_width = bullet_get_width(martian_bullet);
                    int bullet_height = bullet_get_height(martian_bullet);

                    if (bullet_check_colision(ship_bullet, bullet_coord_x, bullet_coord_y, bullet_width, bullet_height) == true) {
                        OBJECT *explosion = NULL;

                        if (bullet_destroy(ship_extract_bullet_at(game->ship, i)) == ERROR) {
                            return ERROR;
                        }

                        if (bullet_destroy(mart_extract_bullet_at(martian, k)) == ERROR) {
                            return ERROR;
                        }

                        explosion = obj_create(game->martian_explosion_img, 0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, bullet_coord_x - 10, bullet_coord_y, true);
                        obj_set_timer(explosion, OBJECT_TIMER);

                        if (game_add_object(game, explosion) == ERROR) {
                            return ERROR;
                        }

                        i--;
                        exit_loop = true;
                        break; // Salimos del bucle interior
                    }
                }

                if (exit_loop) {
                    break; // Salimos del bucle exterior
                }
            }
        }

        for (int j = 0; j < game->num_orphan_bullets; j++) {
            int bullet_coord_x = bullet_get_x(game->orphan_bullets[j]);
            int bullet_coord_y = bullet_get_y(game->orphan_bullets[j]);
            int bullet_width = bullet_get_width(game->orphan_bullets[j]);
            int bullet_height = bullet_get_height(game->orphan_bullets[j]);

            if (bullet_check_colision(ship_bullet, bullet_coord_x, bullet_coord_y, bullet_width, bullet_height) == true) {
                OBJECT *explosion = NULL;

                if (bullet_destroy(ship_extract_bullet_at(game->ship, i)) == ERROR) {
                    return ERROR;
                }

                /*if (bullet_destroy(game_dequeue_orphan_bullet(martian, k)) == ERROR) {
                    return ERROR;
                }*/

                explosion = obj_create(game->martian_explosion_img, 0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, bullet_coord_x - 10, bullet_coord_y, true);
                obj_set_timer(explosion, OBJECT_TIMER);

                if (game_add_object(game, explosion) == ERROR) {
                    return ERROR;
                }

                i--;
                break;
            }
        }
    }

    for (int i = 0; i < game->num_enemies_alive; i++)  { // Comprobar si se ha colisionado con bala de marciano
        MARTIAN *martian = game->enemy[i];
        bool exit_loop = false;

        for (int j = 0; j < mart_get_num_shots(martian); j++) {
            BULLET *martian_bullet = mart_get_bullet_at(martian, j);
            int ship_coord_x = ship_get_x(game->ship);
            int ship_coord_y = ship_get_y(game->ship);
            int ship_width = ship_get_width(game->ship);
            int ship_height = ship_get_height(game->ship);

            if (bullet_check_colision(martian_bullet, ship_coord_x, ship_coord_y, ship_width, ship_height) == true) {
                OBJECT *explosion = NULL;

                if (bullet_destroy(mart_extract_bullet_at(martian, j)) == ERROR) {
                    return ERROR;
                }

                if (GOD_MODE == 0) {
                    ship_decrease_life(game->ship, 1);
                    if (ship_get_life(game->ship) == 0) {
                        game->done = true;
                    }
                }

                explosion = obj_create(game->martian_explosion_img, 0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, ship_coord_x - 10, ship_coord_y, true);
                obj_set_timer(explosion, OBJECT_TIMER);

                if (game_add_object(game, explosion) == ERROR) {
                    return ERROR;
                }

                j--;
            }
        }
    }

    return OK;
}

/**
 * @brief Updates the animation frames for martians and their bullets.
 *
 * Adjusts the animation source coordinates for both martians and bullets
 * at a set interval to simulate movement.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR if game is NULL.
 */
STATUS game_animations_update(GAME *game) {
    if (!game) {
        return ERROR;
    }

    if (++game->enemy_animation_timer > MART_ANIMATION_SPEED) { //temporizador animaciones imagen enemy
        for (int i = 0; i < game->num_enemies_alive; i++) { // movimiento animacion enemigo
            if (mart_get_source_x(game->enemy[i]) > 0) {
                mart_set_source_x(game->enemy[i], 0);
            } else {
                mart_set_source_x(game->enemy[i], 1); // La segunda imagen del tile para simular el movimiento
            }

            if (mart_get_num_shots(game->enemy[i]) > 0) { // movimiento animacion bala enemigo
                for (int j = 0; j < mart_get_num_shots(game->enemy[i]); j++) {
                    BULLET *bullet = mart_get_bullet_at(game->enemy[i], j);
                    
                    if (bullet_get_source_x(bullet) > 0) {
                        bullet_set_source_x(bullet, 0);
                    } else {
                        bullet_set_source_x(bullet, 1);  // La segunda imagen del tile para simular el movimiento
                    }
                }
            }
        }

        for (int i = 0; i < game->num_orphan_bullets; i++) { // movimiento animacion bala huerfana enemigo
            BULLET *bullet = game_get_orphan_bullet_at(game, i);
            
            if (bullet_get_source_x(bullet) > 0) {
                bullet_set_source_x(bullet, 0);
            } else {
                bullet_set_source_x(bullet, 1);  // La segunda imagen del tile para simular el movimiento
            }
        }
        
        game->enemy_animation_timer = 0;
    }

    return OK;
}

/**
 * @brief Main update function for the game.
 *
 * Processes player inputs, martian movements, bullet actions, collision checks, 
 * and animations each frame.
 *
 * @param game Pointer to the GAME instance.
 * @param key Pointer to the keyboard state.
 * @return OK if update is successful, ERROR if game is NULL.
 */
STATUS game_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key) {
    if (!game) {
        return ERROR;
    }

    switch (game->events.type) {
        case(ALLEGRO_EVENT_DISPLAY_CLOSE):
            game->done = true;
            break;

        case(ALLEGRO_EVENT_TIMER):
            if (game_ship_update(game, key) == ERROR) {
                return ERROR;
            }

            if (game_martians_update(game) == ERROR) {
                return ERROR;
            }

            if (game_move_orphan_bullets(game, MART_BULLET_SPEED) == ERROR) {
                return ERROR;
            }

            if (game_colisions(game) == ERROR) { //Colisiones
                return ERROR;
            }

            if (game_animations_update(game) == ERROR) {
                return ERROR;
            }

            if (game->num_enemies_alive > 0) {
                game->last_enemy_rand = (rand() % game->num_enemies_alive);
            }

            game->draw = true;
            break;

        default:
            break;
    }

    return OK;
}

/**
 * @brief Renders the player's ship and its bullets.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_ship(GAME *game) {
    if (!game) {
        return ERROR;
    }

    ship_print(game->ship); //pintar nave

    for (int i = 0; i < ship_get_num_shots(game->ship); i++) { //pintar bala nave
        bullet_print(ship_get_bullet_at(game->ship, i)); // quitar los sources de los parametros
    }

    return OK;
}

/**
 * @brief Renders all alive martians and their bullets.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_enemies(GAME *game) {
    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < game->num_enemies_alive; i++) { //pintar enemy
        mart_print(game->enemy[i]);

        for (int j = 0; j < mart_get_num_shots(game->enemy[i]); j++) { //pintar bala marciano
            BULLET *bullet = mart_get_bullet_at(game->enemy[i], j); // Se puede acceder sin una funcion extra
            bullet_print(bullet);
        }
    }
    
    return OK;
}

/**
 * @brief Renders all orphan bullets currently in the game.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_orphan_bullets(GAME *game) {
    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < game->num_orphan_bullets; i++) { // pintar balas huerfanas
        BULLET *bullet = game_get_orphan_bullet_at(game, i); // Se puede acceder sin una funcion extra
        bullet_print(bullet);
    }

    return OK;
}

/**
 * @brief Renders other non-bullet, non-ship objects like explosions.
 *
 * Handles timer-based destruction of temporary objects.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_other_elements(GAME *game) {
    if (!game) {
        return ERROR;
    }

    for (int i = 0; i < game->num_objects; i++) {
        OBJECT *object = game->objects[i];

        if (obj_get_time(object) > 0) {
            obj_print(object);
            obj_set_timer(object, OBJECT_TIMER);
        } else if (obj_get_time(object) == 0) {
            if (obj_destroy(game_dequeue_object(game)) == ERROR) {
                return ERROR;
            }
        } 
    }

    return OK;
}

/**
 * @brief Renders the player's current score on the screen.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_score(GAME *game) {
    char score_text[10];

    if (!game) {
        return ERROR;
    }

    // pintar puntuacion
    al_draw_text(game->font, al_map_rgb(255, 255, 255), FRAME_WIDTH + 10, 120, 0, "SCORE");
    sprintf(score_text, "%d", game->total_score);
    al_draw_text(game->font, al_map_rgb(0, 255, 0), FRAME_WIDTH + 90, 120, 0, score_text);

    return OK;
}

/**
 * @brief Renders the player's remaining lives as ship icons.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_life(GAME *game) {
    if (!game) {
        return ERROR;
    }

    // pintar vida
    al_draw_text(game->font, al_map_rgb(255, 255, 255), CANVAS_WIDTH - 180 , 120, 0, "LIVES");
    for (int i = 0, space_btw = 0; i < ship_get_life(game->ship); i++, space_btw += (ship_get_width(game->ship))) {
            al_draw_bitmap_region(ship_get_bitmap(game->ship), (ship_get_source_x(game->ship) * ship_get_width(game->ship)), 
                (ship_get_source_y(game->ship) * ship_get_height(game->ship)), ship_get_width(game->ship), ship_get_height(game->ship), 
                (CANVAS_WIDTH - 105) + space_btw, 120, 0);
    }

    return OK;
}

/**
 * @brief Draws a green horizontal line at the bottom of the screen to represent the "ground."
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_floor(GAME *game) {
    ALLEGRO_COLOR green_color = al_map_rgb(0, 255, 0); //Color verde

    if (!game) {
        return ERROR;
    }

    // pintar linea verde suelo
    al_draw_line(FRAME_WIDTH + 10, CANVAS_HEIGTH, CANVAS_WIDTH - 15, CANVAS_HEIGTH, green_color, 2.0);

    return OK;
}

/**
 * @brief Main render function to draw all game elements.
 *
 * Draws the background, frame, ship, enemies, bullets, score, lives, and floor.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_render(GAME * game) {
    if (!game) {
        return ERROR;
    }

    if (game->draw == true) {
        al_draw_bitmap(game->background, 0, 0, -10);
        al_draw_bitmap(game->frame, 0, 0, 0);

        if (game_print_ship(game) == ERROR) {
            return ERROR;
        }

        if (game_print_enemies(game) == ERROR) {
            return ERROR;
        }

        if (game_print_orphan_bullets(game) == ERROR) {
            return ERROR;
        }

        if (game_print_other_elements(game) == ERROR) {
            return ERROR;
        }

        if (game_print_score(game) == ERROR) {
            return ERROR;
        }

        if (game_print_life(game) == ERROR) {
            return ERROR;
        }

        if (game_print_floor(game) == ERROR) {
            return ERROR;
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

        game->draw = false;
    }

    return OK;
}