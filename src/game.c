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
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

typedef enum { STATE_PLAYING, STATE_GAME_OVER, STATE_NAME_INPUT, STATE_WIN } GAME_STATE;

/**
 * @struct _game
 * @brief Main game structure containing all game components and state
 * variables.
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
  ALLEGRO_BITMAP *martian_bullet_img;      ///< Image for martian bullets
  ALLEGRO_BITMAP *bunker_img;              ///< Image for bunkers
  ALLEGRO_BITMAP *ufo_img;                 ///< Image for UFO
  ALLEGRO_FONT *font;                      ///< Font used in the game

  ALLEGRO_TIMER *timer;                    ///< Main game timer
  ALLEGRO_EVENT_QUEUE *event_queue;        ///< Event queue for managing game events
  ALLEGRO_EVENT events;                    ///< Structure to store current event

  SHIP *ship;                              ///< Player ship instance
  MARTIAN *enemy[MAX_ENEMIES];             ///< Array of enemy instances
  BULLET *orphan_bullets[MAX_ORP_BULLETS]; ///< Array of bullets without an owner
  OBJECT *objects[MAX_OBJECTS];            ///< Array of other objects in the game
  BUNKER *bunkers[NUM_BUNKERS * BUNKER_PARTS]; ///< Array of bunker parts (BUNKER_PARTS pieces per bunker)

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

  OBJECT *ufo;                             ///< Mystery ship (UFO)
  int ufo_timer;                           ///< Timer for UFO spawn
  int ufo_dir;                             ///< Direction of UFO movement (-1: left, 1: right)

  ALLEGRO_SAMPLE *samples[10];             ///< Sound samples for the game

  int total_score;                         ///< Player's total score
  int level;                               ///< Current wave/level number (starts at 1)
  int level_y_offset;                      ///< Extra Y pixels enemies start lower each wave
  int high_score;                          ///< All-time high score (persisted to file)
  bool paused;                             ///< Pause state
  bool p_was_down;                         ///< Previous P-key state for edge-detection
  bool ship_exploding;                     ///< Flag for ship death animation
  int ship_explosion_timer;                ///< Timer for death animation
  GAME_STATE state;                        ///< Current game state

  // High scores
  TOP_ENTRY top_scores[MAX_TOP_SCORES + 1]; ///< Array of top scores
  int name_input_cursor;                   ///< Current cursor position for name input
  char name_buffer[MAX_NAME_LENGTH + 3];   ///< Buffer for name input (3 + \0 + newline)
};

// Function Declarations

STATUS game_martian_shoot(GAME *game, int i);                     /**< Handles martian shooting */
STATUS game_move_martians(GAME *game, float speed);               /**< Moves martians */
STATUS game_destroy_martian(GAME *game, int i);                   /**< Destroys specified martian */
STATUS game_colisions(GAME *game);                                /**< Checks for collisions */

STATUS game_ship_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key); /**< Updates ship based on input */
STATUS game_martians_update(GAME *game, float speed);             /**< Updates all martians */
STATUS game_animations_update(GAME *game);                        /**< Updates animations */

STATUS game_add_orphan_bullet(GAME *game, BULLET *bullet);        /**< Adds an orphan bullet */
BULLET *game_dequeue_orphan_bullet(GAME *game);                   /**< Dequeues an orphan bullet */
BULLET *game_extract_orphan_bullet_at(GAME *game, int i);         /**< Extracts a specific orphan bullet */
BULLET *game_get_orphan_bullet_at(GAME *game, int i);             /**< Gets a specific orphan bullet */
STATUS game_move_orphan_bullets(GAME *game, float speed);         /**< Moves orphan bullets */

STATUS game_add_object(GAME *game, OBJECT *object);               /**< Adds an object to the game */
OBJECT *game_dequeue_object(GAME *game);                          /**< Removes an object from the game */
OBJECT *game_extract_object_at(GAME *game, int i);                /**< Extracts a specific object */
OBJECT *game_get_object_at(GAME *game, int i);                    /**< Gets a specific object */

STATUS game_print_ship(GAME *game);                               /**< Renders the player's ship */
STATUS game_print_enemies(GAME *game);                            /**< Renders all enemies */
STATUS game_print_orphan_bullets(GAME *game);                     /**< Renders orphan bullets */
STATUS game_print_other_elements(GAME *game);                     /**< Renders other game elements */
STATUS game_print_score(GAME *game);                              /**< Renders the score */
STATUS game_print_life(GAME *game);                               /**< Renders the player's lives */
STATUS game_print_floor(GAME *game);                              /**< Renders the floor */

static STATUS game_load_highscore(GAME *game);                    /**< Loads high score from file */
static STATUS game_save_highscore(GAME *game);                    /**< Saves high score to file if new record */
static STATUS game_reset_enemies(GAME *game);                     /**< Destroys + recreates full enemy grid */
static STATUS game_reset_bunkers(GAME *game);                     /**< Destroys + recreates all bunker parts */
static STATUS game_reset_ship(GAME *game);                        /**< Resets ship position, lives, bullets */
static STATUS game_next_level(GAME *game);                        /**< Advances to next wave */
static STATUS game_full_reset(GAME *game);                        /**< Full game restart (score + level reset) */

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

  new_game = (GAME *)malloc(sizeof(GAME));
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
  new_game->bunker_img = NULL;
  new_game->ufo_img = NULL;
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

  for (int i = 0; i < NUM_BUNKERS * BUNKER_PARTS; i++) {
    new_game->bunkers[i] = NULL;
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
  new_game->level = 1;
  new_game->level_y_offset = 0;
  new_game->high_score = 0;
  new_game->paused = false;
  new_game->p_was_down = false;

  new_game->ufo = NULL;
  new_game->ufo_timer = 0;

  for (int i = 0; i < 10; i++) {
    new_game->samples[i] = NULL;
  }

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

  for (int i = 0; i < NUM_BUNKERS * BUNKER_PARTS; i++) {
    if (game->bunkers[i] != NULL) {
      bunker_destroy(game->bunkers[i]);
      game->bunkers[i] = NULL;
    }
  }

  if (game->ship) { // eliminacion del jugador
    ship_destroy(game->ship);
    game->ship = NULL;
  }

  if (game->event_queue) { // eliminacion de la pila de eventos
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
    al_destroy_bitmap(game->frame); // eliminacion del marco
    game->frame = NULL;
  }

  if (game->background) { // eliminacion del fondo
    al_destroy_bitmap(game->background);
    game->background = NULL;
  }

  if (game->bunker_img) {
    al_destroy_bitmap(game->bunker_img);
    game->bunker_img = NULL;
  }

  if (game->ufo_img) {
    al_destroy_bitmap(game->ufo_img);
    game->ufo_img = NULL;
  }

  if (game->ufo) {
    obj_destroy(game->ufo);
    game->ufo = NULL;
  }

  if (game->screen) {
    al_destroy_display(game->screen); // elimiacion de la pantalla
    game->screen = NULL;
  }

  for (int i = 0; i < 10; i++) {
    if (game->samples[i]) {
      al_destroy_sample(game->samples[i]);
      game->samples[i] = NULL;
    }
  }

  if (game->timer) {
    al_destroy_timer(game->timer); // eliminacion del temporizador
    game->timer = NULL;
  }

  free(game); // eliminacion de la estructura GAME
  game = NULL;

  return OK;
}

// =========================================================================
// Helper Functions: Persistence and Reset
// =========================================================================

/**
 * @brief Loads the high score from the persistence file.
 *
 * @param game Pointer to the GAME instance.
 * @return OK always (missing file is silently ignored).
 */
static STATUS game_load_highscore(GAME *game) {
  if (!game) return ERROR;

  FILE *f = fopen(HIGHSCORE_FILE, "r");
  if (f) {
    fscanf(f, "%d", &game->high_score);
    fclose(f);
  }

  return OK;
}

/**
 * @brief Saves the high score to the persistence file if a new record is set.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR if game is NULL.
 */
static STATUS game_save_highscore(GAME *game) {
  if (!game) return ERROR;

  if (game->total_score > game->high_score) {
    game->high_score = game->total_score;
    FILE *f = fopen(HIGHSCORE_FILE, "w");
    if (f) {
      fprintf(f, "%d", game->high_score);
      fclose(f);
    }
  }

  return OK;
}

/**
 * @brief Destroys all current enemies, orphan bullets, and objects, then
 * recreates the full 11x5 martian formation.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR on allocation failure.
 */
static STATUS game_reset_enemies(GAME *game) {
  if (!game) return ERROR;

  for (int i = 0; i < game->num_enemies_alive; i++) {
    if (game->enemy[i] != NULL) {
      mart_destroy(game->enemy[i]);
      game->enemy[i] = NULL;
    }
  }

  for (int i = game->num_orphan_bullets - 1; i >= 0; i--) {
    bullet_destroy(game_extract_orphan_bullet_at(game, i));
  }

  for (int i = game->num_objects - 1; i >= 0; i--) {
    obj_destroy(game_extract_object_at(game, i));
  }

  game->enemies_dir = RIGHT;
  game->enemy_shoot_timer = 0;
  game->enemy_move_timer = 0;
  game->enemy_animation_timer = 0;

  for (int y = 0, i = 0; y < NUM_ENEMY_Y; y++) {
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
                                   MART_INIT_POS_X + x * SPACE_BTW_MARTIANS_X,
                                   MART_INIT_POS_Y + game->level_y_offset + y * SPACE_BTW_MARTIANS_Y,
                                   &(game->enemies_dir), score);
      if (!game->enemy[i]) {
        return ERROR;
      }
      mart_set_source_y(game->enemy[i], source_y);
      i++;
    }
  }

  game->num_enemies_alive = MAX_ENEMIES;
  game->num_enemies_destroyed = 0;
  game->last_enemy_rand = 0;

  return OK;
}

/**
 * @brief Destroys all bunker parts and recreates them in their original
 * positions.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR on allocation failure.
 */
static STATUS game_reset_bunkers(GAME *game) {
  if (!game) return ERROR;

  for (int i = 0; i < NUM_BUNKERS * BUNKER_PARTS; i++) {
    if (game->bunkers[i] != NULL) {
      bunker_destroy(game->bunkers[i]);
      game->bunkers[i] = NULL;
    }
  }

  float bunker_spacing = (DISPLAY_WIDTH - 120) / NUM_BUNKERS;
  for (int i = 0; i < NUM_BUNKERS; i++) {
    float bx = 60 + i * bunker_spacing;
    float by = BUNKER_INIT_POS_Y;

    game->bunkers[i * BUNKER_PARTS + 0] =
        bunker_create(game->bunker_img, 0, 0, BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT, bx, by);
    game->bunkers[i * BUNKER_PARTS + 1] =
        bunker_create(game->bunker_img, 0, 4, BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT, bx + BUNKER_PART_WIDTH, by);
    game->bunkers[i * BUNKER_PARTS + 2] =
        bunker_create(game->bunker_img, 0, 2, BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT, bx + BUNKER_PART_WIDTH * 2, by);
    game->bunkers[i * BUNKER_PARTS + 3] =
        bunker_create(game->bunker_img, 0, 1, BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT, bx, by + BUNKER_PART_HEIGHT);
    game->bunkers[i * BUNKER_PARTS + 4] =
        bunker_create(game->bunker_img, 0, 3, BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT, bx + BUNKER_PART_WIDTH * 2, by + BUNKER_PART_HEIGHT);

    for (int j = 0; j < BUNKER_PARTS; j++) {
      if (!game->bunkers[i * BUNKER_PARTS + j]) {
        return ERROR;
      }
    }
  }

  return OK;
}

/**
 * @brief Destroys all ship bullets, resets ship position, life, and
 * explosion state.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR if game or ship is NULL.
 */
static STATUS game_reset_ship(GAME *game) {
  if (!game || !game->ship) return ERROR;

  for (int i = ship_get_num_shots(game->ship) - 1; i >= 0; i--) {
    bullet_destroy(ship_extract_bullet_at(game->ship, i));
  }

  ship_set_x(game->ship, SHIP_INIT_POS_X);
  ship_set_y(game->ship, SHIP_INIT_POS_Y);
  ship_set_life(game->ship, SHIP_LIFE);
  ship_set_source_x(game->ship, 0);
  game->ship_exploding = false;
  game->ship_explosion_timer = 0;

  return OK;
}

/**
 * @brief Advances to the next wave: increments level, resets enemies.
 * Bunkers are NOT reset (authentic arcade behavior).
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR on failure.
 */
static STATUS game_next_level(GAME *game) {
  if (!game) return ERROR;

  if (game->ufo) {
    al_stop_samples();
    obj_destroy(game->ufo);
    game->ufo = NULL;
  }

  game->level++;

  // En el original, los enemigos empiezan una fila más abajo cada oleada
  game->level_y_offset = (game->level - 1) * SPACE_BTW_MARTIANS_Y;
  if (game->level_y_offset > 6 * SPACE_BTW_MARTIANS_Y)
    game->level_y_offset = 6 * SPACE_BTW_MARTIANS_Y;

  if (game_reset_enemies(game) == ERROR) {
    return ERROR;
  }

  game->state = STATE_PLAYING;

  return OK;
}

/**
 * @brief Performs a complete game restart: resets score, level, ship,
 * enemies, and bunkers.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if successful, ERROR on failure.
 */
static STATUS game_full_reset(GAME *game) {
  if (!game) return ERROR;

  if (game->ufo) {
    al_stop_samples();
    obj_destroy(game->ufo);
    game->ufo = NULL;
  }

  game->total_score = 0;
  game->level = 1;
  game->level_y_offset = 0;
  game->paused = false;

  if (game_reset_ship(game) == ERROR) {
    return ERROR;
  }

  if (game_reset_enemies(game) == ERROR) {
    return ERROR;
  }

  if (game_reset_bunkers(game) == ERROR) {
    return ERROR;
  }

  game->state = STATE_PLAYING;

  return OK;
}

// =========================================================================
// Functions: Game Initialization and Cleanup
// =========================================================================

/**
 * @brief Initializes the game with provided FPS and sets up the display,
 * bitmaps, fonts, and other resources.
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

  game->FPS = FPS;                                // FPS del game
  game->timer = al_create_timer(1.0 / game->FPS); // Creacion del tiempo del game

  if (!game->timer) {
    return ERROR;
  }

  game->screen = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); // Creacion de pantalla
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

  game->bunker_img = al_load_bitmap(BUNKER_IMG_RSC);
  if (!game->bunker_img) {
    return ERROR;
  }
  al_convert_mask_to_alpha(game->bunker_img, al_map_rgb(255, 0, 255));

  game->ufo_img = al_load_bitmap(UFO_IMG_RSC);
  if (!game->ufo_img) {
    return ERROR;
  }

  // Carga de sonidos
  game->samples[0] = al_load_sample(SND_SHOOT);
  game->samples[1] = al_load_sample(SND_INVADER_KILLED);
  game->samples[2] = al_load_sample(SND_SHIP_EXPLOSION);
  game->samples[3] = al_load_sample(SND_MYSTERY_ENTERED);
  game->samples[4] = al_load_sample(SND_MYSTERY_KILLED);
  game->samples[5] = al_load_sample(SND_MOVE_0);
  game->samples[6] = al_load_sample(SND_MOVE_1);
  game->samples[7] = al_load_sample(SND_MOVE_2);
  game->samples[8] = al_load_sample(SND_MOVE_3);

  game->font = al_load_ttf_font(FONT_RSC, 18, 0); // 24 es el tamaño de la fuente
  if (!game->font) {
    return ERROR;
  }

  game->event_queue = al_create_event_queue(); // Creacion de pila de eventos del game
  if (!game->event_queue) {
    return ERROR;
  }

  game->ship = ship_create(game->ship_img, SHIP_WIDTH, SHIP_HEIGHT, SHIP_INIT_POS_X,
                           SHIP_INIT_POS_Y, NO_DIR, SHIP_LIFE); // Creacion de nave
  if (!game->ship) {
    return ERROR;
  }

  // Nuevos campos de estado
  game->level = 1;
  game->high_score = 0;
  game->paused = false;
  game->p_was_down = false;

  game->ship_exploding = false;
  game->ship_explosion_timer = 0;
  game->state = STATE_PLAYING;

  // Creacion de enemigos
  if (game_reset_enemies(game) == ERROR) {
    return ERROR;
  }

  // Inicialización de escudos
  if (game_reset_bunkers(game) == ERROR) {
    return ERROR;
  }

  // Cargar puntuacion maxima persistida
  game_load_highscore(game);

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

// =========================================================================
// Functions: Enemy Management - Shooting, Movement, and Destruction
// =========================================================================

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
 * @brief Moves all martians by the specified speed and updates their direction
 * as necessary.
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
    for (int i = 0; i < game->num_enemies_alive && game->enemy[i] != NULL; i++) {
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
        game_save_highscore(game);
        game->state = STATE_GAME_OVER;
        i = game->num_enemies_alive;
      }
    }

    for (int i = 0; i < game->num_enemies_alive && game->enemy[i] != NULL;
         i++) {
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
STATUS game_destroy_martian(GAME *game, int i) { // Cambiar estructura y devolver martian
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

// =========================================================================
// Functions: Orphan Bullet Management - Adding, Moving, and Removing
// =========================================================================

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
  return game_extract_orphan_bullet_at(game, 0);
}

/**
 * @brief Removes and returns a specific orphan bullet at index i.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the orphan bullet to extract.
 * @return Pointer to the extracted bullet or NULL if index is invalid.
 */
BULLET *game_extract_orphan_bullet_at(GAME *game, int i) {
  BULLET *bullet = NULL;

  if (game != NULL && i >= 0 && i < game->num_orphan_bullets) {
    bullet = game->orphan_bullets[i];

    for (int j = i; j < game->num_orphan_bullets - 1; j++) {
      game->orphan_bullets[j] = game->orphan_bullets[j + 1];
    }

    game->num_orphan_bullets--;
    game->orphan_bullets[game->num_orphan_bullets] = NULL;
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
 * If a bullet exceeds the bottom limit, it is removed from the orphan bullets
 * list.
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

  for (int i = game->num_orphan_bullets - 1; i >= 0;
       i--) { // Se mueven las balas huerfanas del juego
    if (bullet_get_y(game->orphan_bullets[i]) + speed < bottom_limit) {
      if (bullet_move(game->orphan_bullets[i], speed) == ERROR) {
        return ERROR;
      }
    } else {
      if (bullet_destroy(game_extract_orphan_bullet_at(game, i)) == ERROR) {
        return ERROR;
      }
    }
  }

  return OK;
}

// =========================================================================
// Functions: Object Management - Adding, Retrieving, and Removing Game Objects
// =========================================================================

/**
 * @brief Adds an object to the game's object list.
 *
 * @param game Pointer to the GAME instance.
 * @param object Pointer to the OBJECT to be added.
 * @return OK if the object is added successfully, ERROR if game, object,
 *         or the limit of objects is exceeded.
 */
STATUS game_add_object(GAME *game, OBJECT *object) {
  if (!game || !object || game->num_objects >= MAX_OBJECTS) {
    return ERROR;
  }

  game->objects[game->num_objects] = object;
  game->num_objects++;

  return OK;
}

/**
 * @brief Removes and returns the first object in the game's object list.
 *
 * Dequeues an object, shifts the remaining objects forward, and decreases the
 * object count.
 *
 * @param game Pointer to the GAME instance.
 * @return Pointer to the removed object or NULL if there are no objects.
 */
OBJECT *game_dequeue_object(GAME *game) {
  return game_extract_object_at(game, 0);
}

/**
 * @brief Removes and returns a specific object at index i.
 *
 * @param game Pointer to the GAME instance.
 * @param i Index of the object to extract.
 * @return Pointer to the extracted object or NULL if index is invalid.
 */
OBJECT *game_extract_object_at(GAME *game, int i) {
  OBJECT *object = NULL;

  if (game != NULL && i >= 0 && i < game->num_objects) {
    object = game->objects[i];

    for (int j = i; j < game->num_objects - 1; j++) {
      game->objects[j] = game->objects[j + 1];
    }

    game->num_objects--;
    game->objects[game->num_objects] = NULL;
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

// =========================================================================
// Functions: Input Callbacks - Ship Movement and Shooting
// =========================================================================

/**
 * @brief Moves the player's ship to the left.
 *
 * Checks if the ship can move left within bounds and updates its direction.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if movement is successful, ERROR if game is NULL.
 */
STATUS callback_left(GAME *game) {
  if (!game)
    return ERROR;

  float x = ship_get_x(game->ship);

  if (x - SHIP_SPEED >= FRAME_WIDTH) {
    ship_set_dir(game->ship, LEFT);
    ship_move(game->ship, -SHIP_SPEED);
  }

  return OK;
}

/**
 * @brief Moves the player's ship to the right.
 *
 * Checks if the ship can move right within bounds and updates its direction.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if movement is successful, ERROR if game is NULL.
 */
STATUS callback_right(GAME *game) {
  if (!game)
    return ERROR;

  float x = ship_get_x(game->ship);

  if (x + SHIP_SPEED <= (CANVAS_WIDTH - 32)) {
    ship_set_dir(game->ship, RIGHT);
    ship_move(game->ship, SHIP_SPEED);
  }

  return OK;
}

/**
 * @brief Triggers the ship's shooting action.
 *
 * @param game Pointer to the GAME instance.
 * @return OK if shooting is successful, ERROR if game or ship's bullet image is
 * NULL.
 */
STATUS callback_space(GAME *game) {
  if (!game) {
    return ERROR;
  }

  if (ship_shoot(game->ship, game->ship_bullet_img) == ERROR) {
    return ERROR;
  }

  return OK;
}

// =========================================================================
// Functions: Game Update - Ship and Martian Actions, Collision Detection
// =========================================================================

// Para aumentar la dificultad, aumentar la cadencia y velocidad de los
// marcianos, y reducir la de la nave
/**
 * @brief Updates the ship's movement, shooting actions, and bullet movement.
 *
 * Handles input for the ship's direction, space for shooting, and ESC for
 * ending the game.
 *
 * @param game Pointer to the GAME instance.
 * @param key Pointer to the current keyboard state.
 * @return OK if update is successful, ERROR if game is NULL.
 */
STATUS game_ship_update(GAME *game, ALLEGRO_KEYBOARD_STATE *key) {
  if (!game || !key) {
    return ERROR;
  }

  if (al_key_down(key, ALLEGRO_KEY_LEFT)) {
    ship_move(game->ship, -SHIP_SPEED);
  } else if (al_key_down(key, ALLEGRO_KEY_RIGHT)) {
    ship_move(game->ship, SHIP_SPEED);
  }

  if (al_key_down(key, ALLEGRO_KEY_SPACE)) {
    if (ship_shoot(game->ship, game->ship_bullet_img) == OK) {
      al_play_sample(game->samples[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
  }

  if (ship_move_bullet(game->ship, SHIP_BULLET_SPEED) == ERROR) {
    return ERROR;
  }

  if (al_key_down(key, ALLEGRO_KEY_ESCAPE)) {
    game->done = true;
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
STATUS game_martians_update(GAME *game, float speed) {
  static int move_sound_idx = 0;

  if (!game) {
    return ERROR;
  }

  if (game->num_enemies_alive > 0) {
    // Frecuencia dinámica: aumenta con menos enemigos vivos y con el nivel
    int dyn_freq = MART_SHOOT_FREQ
        - (int)((MART_SHOOT_FREQ - MART_SHOOT_FREQ_MIN)
                * (1.0f - (float)game->num_enemies_alive / MAX_ENEMIES))
        - (game->level - 1) * 5;
    if (dyn_freq < MART_SHOOT_FREQ_MIN) dyn_freq = MART_SHOOT_FREQ_MIN;

    if (++game->enemy_shoot_timer >= dyn_freq) {
      if (game_martian_shoot(game, game->last_enemy_rand) == ERROR) {
        return ERROR;
      }
      game->enemy_shoot_timer = 0;
    }

    // En el arcade original la velocidad escala reduciendo el intervalo entre pasos,
    // no aumentando píxeles por paso: con 55 enemigos el timer es MART_MOVE_TIMER,
    // con 1 enemigo cae a MART_MOVE_TIMER_MIN (casi un paso por frame).
    int dyn_move_timer = (int)(MART_MOVE_TIMER * game->num_enemies_alive / MAX_ENEMIES);
    if (dyn_move_timer < MART_MOVE_TIMER_MIN) dyn_move_timer = MART_MOVE_TIMER_MIN;

    if (++game->enemy_move_timer >= dyn_move_timer) {
      game_move_martians(game, speed);
      game->enemy_move_timer = 0;

      // Sonido de movimiento (cíclico 0-3)
      al_play_sample(game->samples[5 + move_sound_idx], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      move_sound_idx = (move_sound_idx + 1) % 4;
    }

    for (int i = 0; i < game->num_enemies_alive; i++) {
      if (mart_get_num_shots(game->enemy[i]) > 0) {
        if (mart_move_bullet(game->enemy[i], MART_BULLET_SPEED) == ERROR) {
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
STATUS game_colisions(GAME *game) {
  if (!game)
    return ERROR;

  // 1. Balas del jugador
  for (int i = ship_get_num_shots(game->ship) - 1; i >= 0; i--) {
    BULLET *sb = ship_get_bullet_at(game->ship, i);
    bool destroyed = false;

    // Contra Marcianos
    for (int j = 0; j < game->num_enemies_alive; j++) {
      MARTIAN *m = game->enemy[j];

      if (bullet_check_colision(sb, mart_get_x(m), mart_get_y(m), MART_WIDTH, MART_HEIGHT)) {

        al_play_sample(game->samples[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        for (int k = mart_get_num_shots(m) - 1; k >= 0; k--) {
          game_add_orphan_bullet(game, mart_extract_bullet_at(m, k));
        }

        game->total_score += mart_get_score(m);

        // Explosion
        OBJECT *exp = obj_create(game->martian_explosion_img, 0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, mart_get_x(m), mart_get_y(m), true);

        if (exp) {
          obj_set_timer(exp, OBJECT_TIMER);
          game_add_object(game, exp);
        }

        bullet_destroy(ship_extract_bullet_at(game->ship, i));
        game_destroy_martian(game, j);
        destroyed = true;
        break;
      }
    }

    if (destroyed)
      continue;

    // Contra Balas Enemigas (unificadas)
    for (int j = 0; j < game->num_enemies_alive; j++) {
      MARTIAN *m = game->enemy[j];

      for (int k = mart_get_num_shots(m) - 1; k >= 0; k--) {
        BULLET *mb = mart_get_bullet_at(m, k);

        if (bullet_check_colision(sb, bullet_get_x(mb), bullet_get_y(mb),
                                  bullet_get_width(mb),
                                  bullet_get_height(mb))) {

          // Explosion por choque de balas
          OBJECT *exp = obj_create(game->martian_explosion_img, 0, 0,
                                   EXPLOSION_WIDTH, EXPLOSION_HEIGHT,
                                   bullet_get_x(mb), bullet_get_y(mb), true);
          if (exp) {
            obj_set_timer(exp, OBJECT_TIMER);
            game_add_object(game, exp);
          }

          bullet_destroy(ship_extract_bullet_at(game->ship, i));
          bullet_destroy(mart_extract_bullet_at(m, k));
          destroyed = true;
          break;
        }
      }

      if (destroyed)
        break;
    }

    if (destroyed)
      continue;

    for (int j = game->num_orphan_bullets - 1; j >= 0; j--) {
      BULLET *ob = game->orphan_bullets[j];

      if (bullet_check_colision(sb, bullet_get_x(ob), bullet_get_y(ob),
                                bullet_get_width(ob), bullet_get_height(ob))) {

        OBJECT *exp = obj_create(game->martian_explosion_img, 0, 0,
                                 EXPLOSION_WIDTH, EXPLOSION_HEIGHT,
                                 bullet_get_x(ob), bullet_get_y(ob), true);
        if (exp) {
          obj_set_timer(exp, OBJECT_TIMER);
          game_add_object(game, exp);
        }

        bullet_destroy(ship_extract_bullet_at(game->ship, i));
        bullet_destroy(game_extract_orphan_bullet_at(game, j));
        destroyed = true;
        break;
      }
    }

    if (destroyed)
      continue;

    // Contra UFO
    if (game->ufo && bullet_check_colision(sb, obj_get_x(game->ufo), obj_get_y(game->ufo),
              UFO_WIDTH, UFO_HEIGHT)) {

      game->total_score += UFO_POINTS_MIN + (rand() % (UFO_POINTS_MAX - UFO_POINTS_MIN));
      al_stop_samples();
      al_play_sample(game->samples[4], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

      // Explosion UFO
      OBJECT *exp = obj_create(game->martian_explosion_img, 0, 0, 
                               EXPLOSION_WIDTH, EXPLOSION_HEIGHT, obj_get_x(game->ufo), 
                               obj_get_y(game->ufo), true);

      if (exp) {
        obj_set_timer(exp, OBJECT_TIMER);
        game_add_object(game, exp);
      }

      bullet_destroy(ship_extract_bullet_at(game->ship, i));
      obj_destroy(game->ufo);
      game->ufo = NULL;

      continue;
    }

    // Contra Bunkers (Cualquiera de las partes)
    for (int j = 0; j < NUM_BUNKERS * BUNKER_PARTS; j++) {
      if (!game->bunkers[j])
        continue;

      if (bullet_check_colision(sb, bunker_get_x(game->bunkers[j]),
                                bunker_get_y(game->bunkers[j]), BUNKER_PART_WIDTH,
                                BUNKER_PART_HEIGHT)) {

        int life = bunker_get_life(game->bunkers[j]) - 1;
        bunker_set_life(game->bunkers[j], life);
        bunker_set_source_x(game->bunkers[j], (BUNKER_LIFE - life)); // 1 state per hit
        bullet_destroy(ship_extract_bullet_at(game->ship, i));

        if (life <= 0) {
          bunker_destroy(game->bunkers[j]);
          game->bunkers[j] = NULL;
        }

        destroyed = true;
        break;
      }
    }
  }

  // 2. Balas de marcianos vs Jugador y Bunkers
  for (int j = 0; j < game->num_enemies_alive; j++) {
    MARTIAN *m = game->enemy[j];

    for (int k = mart_get_num_shots(m) - 1; k >= 0; k--) {
      BULLET *mb = mart_get_bullet_at(m, k);

      if (GOD_MODE == 0 && !game->ship_exploding && 
          bullet_check_colision(mb, ship_get_x(game->ship), 
          ship_get_y(game->ship), ship_get_width(game->ship), 
          ship_get_height(game->ship))) {
       
        al_play_sample(game->samples[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        // Iniciar animacion de explosion de la propia nave (paralizando el juego)
        game->ship_exploding = true;
        game->ship_explosion_timer = SHIP_EXPLOSION_FRAMES;

        bullet_destroy(mart_extract_bullet_at(m, k));
        ship_decrease_life(game->ship, 1);
        continue;
      }

      for (int l = 0; l < NUM_BUNKERS * BUNKER_PARTS; l++) {
        if (!game->bunkers[l])
          continue;

        if (bullet_check_colision(mb, bunker_get_x(game->bunkers[l]),
                                  bunker_get_y(game->bunkers[l]),
                                  BUNKER_PART_WIDTH, BUNKER_PART_HEIGHT)) {

          int life = bunker_get_life(game->bunkers[l]) - 1;
          bunker_set_life(game->bunkers[l], life);
          bunker_set_source_x(game->bunkers[l], (BUNKER_LIFE - life));
          bullet_destroy(mart_extract_bullet_at(m, k));

          if (life <= 0) {
            bunker_destroy(game->bunkers[l]);
            game->bunkers[l] = NULL;
          }
          break;
        }
      }
    }
  }

  // Igual para balas huerfanas
  for (int i = game->num_orphan_bullets - 1; i >= 0; i--) {
    BULLET *ob = game->orphan_bullets[i];

    if (GOD_MODE == 0 && !game->ship_exploding && 
        bullet_check_colision(ob, ship_get_x(game->ship), 
        ship_get_y(game->ship), ship_get_width(game->ship), 
        ship_get_height(game->ship))) {

      al_play_sample(game->samples[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

      game->ship_exploding = true;
      game->ship_explosion_timer = SHIP_EXPLOSION_FRAMES;

      bullet_destroy(game_extract_orphan_bullet_at(game, i));
      ship_decrease_life(game->ship, 1);
      continue;
    }

    for (int l = 0; l < NUM_BUNKERS * BUNKER_PARTS; l++) {
      if (!game->bunkers[l])
        continue;

      if (bullet_check_colision(ob, bunker_get_x(game->bunkers[l]),
                                bunker_get_y(game->bunkers[l]), BUNKER_PART_WIDTH,
                                BUNKER_PART_HEIGHT)) {

        int life = bunker_get_life(game->bunkers[l]) - 1;
        bunker_set_life(game->bunkers[l], life);
        bunker_set_source_x(game->bunkers[l], (BUNKER_LIFE - life));
        bullet_destroy(game_extract_orphan_bullet_at(game, i));

        if (life <= 0) {
          bunker_destroy(game->bunkers[l]);
          game->bunkers[l] = NULL;
        }
        break;
      }
    }
  }

  // 3. Marcianos destruyen bunkers al superponerse (cuando descienden)
  for (int i = 0; i < game->num_enemies_alive && game->enemy[i] != NULL; i++) {
    int mx = mart_get_x(game->enemy[i]);
    int my = mart_get_y(game->enemy[i]);

    for (int j = 0; j < NUM_BUNKERS * BUNKER_PARTS; j++) {
      if (!game->bunkers[j]) continue;

      float bx = bunker_get_x(game->bunkers[j]);
      float by = bunker_get_y(game->bunkers[j]);

      if (mx < bx + BUNKER_PART_WIDTH && mx + MART_WIDTH > bx &&
          my < by + BUNKER_PART_HEIGHT && my + MART_HEIGHT > by) {
        bunker_destroy(game->bunkers[j]);
        game->bunkers[j] = NULL;
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

  // temporizador animaciones imagen enemy
  if (++game->enemy_animation_timer > MART_ANIMATION_SPEED) {

    // movimiento animacion enemigo 
    for (int i = 0; i < game->num_enemies_alive; i++) { 
      if (mart_get_source_x(game->enemy[i]) > 0) {
        mart_set_source_x(game->enemy[i], 0);
      } else {
        // La segunda imagen del tile para simular el movimiento
        mart_set_source_x(game->enemy[i], 1); 
      }

      // movimiento animacion bala enemigo
      if (mart_get_num_shots(game->enemy[i]) > 0) { 
        for (int j = 0; j < mart_get_num_shots(game->enemy[i]); j++) {
          BULLET *bullet = mart_get_bullet_at(game->enemy[i], j);

          if (bullet_get_source_x(bullet) > 0) {
            bullet_set_source_x(bullet, 0);
          } else {
            // La segunda imagen del tile para simular el movimiento
            bullet_set_source_x(bullet, 1); 
          }
        }
      }
    }

    // movimiento animacion bala huerfana enemigo
    for (int i = 0; i < game->num_orphan_bullets; i++) { 
      BULLET *bullet = game_get_orphan_bullet_at(game, i);

      if (bullet_get_source_x(bullet) > 0) {
        bullet_set_source_x(bullet, 0);
      } else {
        // La segunda imagen del tile para simular el movimiento
        bullet_set_source_x(bullet, 1);
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
  float current_mart_speed;

  if (!game) {
    return ERROR;
  }

  // Velocidad de paso constante: la "velocidad" percibida viene del timer dinámico en game_martians_update
  current_mart_speed = MART_BASE_SPEED;

  switch (game->events.type) {
    case (ALLEGRO_EVENT_DISPLAY_CLOSE):
      game->done = true;
      break;

    case (ALLEGRO_EVENT_TIMER):
      if (game->state != STATE_PLAYING) {
        if (al_key_down(key, ALLEGRO_KEY_ENTER)) {
          if (game->state == STATE_WIN) {
            game_next_level(game);   // Conserva puntuacion y vidas, nuevo nivel
          } else {
            game_full_reset(game);   // Reinicio completo tras game over
          }
        } else if (al_key_down(key, ALLEGRO_KEY_ESCAPE)) {
          game->done = true;
        }
        game->draw = true;
        break;
      }

      // Pausa (P) con deteccion de flanco para toggle correcto
      {
        bool p_is_down = al_key_down(key, ALLEGRO_KEY_P);
        if (p_is_down && !game->p_was_down) {
          game->paused = !game->paused;
        }
        game->p_was_down = p_is_down;
      }

      if (game->paused) {
        game->draw = true;
        break;
      }

      // ESC durante el juego -> salir
      if (al_key_down(key, ALLEGRO_KEY_ESCAPE)) {
        game->done = true;
        break;
      }

      if (game->ship_exploding) {
        game->ship_explosion_timer--;

        // Alternar entre los frames de explosion (indices 1 y 2 del bitmap)
        // Cambiamos de frame cada 6 ticks (~0.1s a 60FPS)
        int frame = (game->ship_explosion_timer / 6) % 2 + 1;
        ship_set_source_x(game->ship, frame);

        if (game->ship_explosion_timer <= 0) {
          game->ship_exploding = false;
          ship_set_source_x(game->ship, 0); // Reset a nave normal

          if (ship_get_life(game->ship) <= 0) {
            game->state = STATE_GAME_OVER;
          } else {
            // Reaparecer centrado
            ship_set_x(game->ship, SHIP_INIT_POS_X);
            ship_set_y(game->ship, SHIP_INIT_POS_Y);
          }
        }
        game->draw = true;
        break; // Paralizar el juego durante la explosion
      }

      if (al_key_down(key, ALLEGRO_KEY_LEFT)) {
        callback_left(game);
      } else if (al_key_down(key, ALLEGRO_KEY_RIGHT)) {
        callback_right(game);
      } else {
        ship_set_dir(game->ship, NO_DIR);
      }

      if (al_key_down(key, ALLEGRO_KEY_SPACE)) {
        if (ship_shoot(game->ship, game->ship_bullet_img) == OK) {
          al_play_sample(game->samples[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
      }

      if (ship_move_bullet(game->ship, SHIP_BULLET_SPEED) == ERROR) {
        return ERROR;
      }

      if (game_martians_update(game, current_mart_speed) == ERROR) {
        return ERROR;
      }

      // Logica del OVNI
      if (game->ufo == NULL) {
        if (rand() % UFO_SPAWN_CHANCE == 0) {
          int side = (rand() % 2 == 0 ? -1 : 1);
          game->ufo_dir = -side;
          float sx = (side == -1 ? (float)FRAME_WIDTH - UFO_WIDTH : (float)CANVAS_WIDTH);
          game->ufo = obj_create(game->ufo_img, 0, 0, UFO_WIDTH, UFO_HEIGHT, sx, UFO_INIT_POS_Y, false);
          if (game->ufo) {
            al_play_sample(game->samples[3], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
          }
        }
      } else {
        float ux = obj_get_x(game->ufo);
        if (ux < (float)FRAME_WIDTH - UFO_WIDTH - 5 || ux > (float)CANVAS_WIDTH + 5) {
          al_stop_samples();
          obj_destroy(game->ufo);
          game->ufo = NULL;
        } else {
          obj_set_x(game->ufo, ux + (game->ufo_dir * UFO_SPEED));
        }
      }

      if (game->num_enemies_alive <= 0) {
        game_save_highscore(game);
        game->state = STATE_WIN;
      }

      if (game_move_orphan_bullets(game, MART_BULLET_SPEED) == ERROR) {
        return ERROR;
      }

      if (game_colisions(game) == ERROR) {
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

// =========================================================================
// Functions: Rendering - Drawing Ships, Enemies, Bullets, and UI Elements
// =========================================================================

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

  ship_print(game->ship); // pintar nave

  for (int i = 0; i < ship_get_num_shots(game->ship); i++) { // pintar bala nave
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

  for (int i = 0; i < game->num_enemies_alive; i++) { // pintar enemy
    mart_print(game->enemy[i]);

    for (int j = 0; j < mart_get_num_shots(game->enemy[i]); j++) { // pintar bala marciano
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

  for (int i = game->num_objects - 1; i >= 0; i--) {
    OBJECT *object = game->objects[i];
    obj_print(object);
    obj_set_timer(object, OBJECT_TIMER);
    // Destruir objeto al completar un ciclo (20 frames)
    if (obj_get_time(object) == 0) {
      if (obj_destroy(game_extract_object_at(game, i)) == ERROR) {
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
  char buf[16];

  if (!game) {
    return ERROR;
  }

  // SCORE (izquierda)
  al_draw_text(game->font, al_map_rgb(255, 255, 255), FRAME_WIDTH + 10, 120, 0, "SCORE");
  sprintf(buf, "%d", game->total_score);
  al_draw_text(game->font, al_map_rgb(0, 255, 0), FRAME_WIDTH + 90, 120, 0, buf);

  // HI-SCORE y LEVEL (segunda linea)
  al_draw_text(game->font, al_map_rgb(255, 255, 255), FRAME_WIDTH + 10, 140, 0, "HI-SCORE");
  sprintf(buf, "%d", game->high_score);
  al_draw_text(game->font, al_map_rgb(0, 255, 0), FRAME_WIDTH + 120, 140, 0, buf);

  al_draw_text(game->font, al_map_rgb(255, 255, 255), CANVAS_WIDTH - 180, 140, 0, "LEVEL");
  sprintf(buf, "%d", game->level);
  al_draw_text(game->font, al_map_rgb(0, 255, 0), CANVAS_WIDTH - 110, 140, 0, buf);

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
  al_draw_text(game->font, al_map_rgb(255, 255, 255), CANVAS_WIDTH - 180, 120, 0, "LIVES");
  for (int i = 0, space_btw = 0; i < ship_get_life(game->ship);
       i++, space_btw += (ship_get_width(game->ship))) {
    al_draw_bitmap_region(ship_get_bitmap(game->ship),
        (ship_get_source_x(game->ship) * ship_get_width(game->ship)),
        (ship_get_source_y(game->ship) * ship_get_height(game->ship)),
        ship_get_width(game->ship), ship_get_height(game->ship),
        (CANVAS_WIDTH - 105) + space_btw, 120, 0);
  }

  return OK;
}

/**
 * @brief Draws a green horizontal line at the bottom of the screen to represent
 * the "ground."
 *
 * @param game Pointer to the GAME instance.
 * @return OK if rendering is successful, ERROR if game is NULL.
 */
STATUS game_print_floor(GAME *game) {
  ALLEGRO_COLOR green_color = al_map_rgb(0, 255, 0); // Color verde

  if (!game) {
    return ERROR;
  }

  // pintar linea verde suelo
  al_draw_line(FRAME_WIDTH + 10, CANVAS_HEIGTH, CANVAS_WIDTH - 15,
               CANVAS_HEIGTH, green_color, 2.0);

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
STATUS game_render(GAME *game) {
  if (!game) {
    return ERROR;
  }

  if (game->draw == true) {
    al_draw_bitmap(game->background, 0, 0, -10);
    // El frame se pintará al final para tapar lo que salga de los límites

    if (game_print_ship(game) == ERROR) {
      return ERROR;
    }

    if (game_print_enemies(game) == ERROR) {
      return ERROR;
    }

    for (int i = 0; i < NUM_BUNKERS * BUNKER_PARTS; i++) {
      if (game->bunkers[i] != NULL) {
        bunker_print(game->bunkers[i]);
      }
    }

    if (game->ufo != NULL) {
      obj_print(game->ufo);
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

    // Pintar el marco encima de todo para recortar
    al_draw_bitmap(game->frame, 0, 0, 0);

    // Overlay de pausa
    if (game->paused) {
      al_draw_text(game->font, al_map_rgb(255, 255, 0),
                   DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2,
                   ALLEGRO_ALIGN_CENTER, "PAUSED");
      al_draw_text(game->font, al_map_rgb(255, 255, 255),
                   DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 + 30,
                   ALLEGRO_ALIGN_CENTER, "PRESS P TO CONTINUE");
    }

    // Pantallas de fin de juego / nivel
    if (game->state == STATE_GAME_OVER) {
      char score_end[32];
      sprintf(score_end, "SCORE: %d", game->total_score);
      al_draw_text(game->font, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2,
                   DISPLAY_HEIGHT / 2 - 30, ALLEGRO_ALIGN_CENTER, "GAME OVER");
      al_draw_text(game->font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2,
                   DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, score_end);
      al_draw_text(game->font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2,
                   DISPLAY_HEIGHT / 2 + 30, ALLEGRO_ALIGN_CENTER,
                   "ENTER: PLAY AGAIN   ESC: EXIT");
    } else if (game->state == STATE_WIN) {
      char level_end[32];
      sprintf(level_end, "WAVE %d CLEARED!", game->level);
      al_draw_text(game->font, al_map_rgb(0, 255, 0), DISPLAY_WIDTH / 2,
                   DISPLAY_HEIGHT / 2 - 30, ALLEGRO_ALIGN_CENTER, level_end);
      al_draw_text(game->font, al_map_rgb(255, 255, 255), DISPLAY_WIDTH / 2,
                   DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER,
                   "ENTER: NEXT WAVE   ESC: EXIT");
    }

    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));

    game->draw = false;
  }

  return OK;
}