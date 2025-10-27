/**
 * @file config.h
 * @brief Configuration file for defining constants and resources in the Space Invaders game.
 *
 * This file contains the necessary paths to resources and constants
 * such as screen dimensions, game object properties, and gameplay parameters.
 * These constants are referenced throughout the codebase to ensure
 * uniform configuration and easy adjustments.
 */

#ifndef CONFIG_H
#define CONFIG_H

// Resource Paths for Game Assets
#define BACKGROUND_IMG_RSC "resources/images/background.bmp"
#define FRAME_IMG_RSC "resources/images/frame.bmp"
#define SHIP_IMG_RSC "resources/images/ship.bmp"
#define MARTIAN_IMG_RSC "resources/images/martians.bmp"
#define SHIP_BULLET_IMG_RSC "resources/images/ship_bullet.bmp"
#define MART_BULLET_IMG_RSC "resources/images/martian_bullet.bmp"
#define EXPLOSION_IMG_RSC "resources/images/martian_explosion.bmp"
#define FONT_RSC  "resources/fonts/space_invaders.ttf"

// Points Configuration for Different Martian Types
#define POINTS_01 30 ///< Points awarded for hitting the first type of martian
#define POINTS_02 20 ///< Points awarded for hitting the second type of martian
#define POINTS_03 10 ///< Points awarded for hitting the third type of martian

// Display Configuration
// IMPORTANTE: El juego está diseñado para 600x600. Otros tamaños se ven mal.
// En macOS Retina se verá pequeño, pero es la única forma correcta sin modificar código.
#define DISPLAY_HEIGHT 600 ///< Height of the game display window
#define DISPLAY_WIDTH 600 ///< Width of the game display window

// Frame and Canvas Dimensions
#define FRAME_WIDTH 40 ///< Width of the display frame (side borders)
#define FRAME_WIDTH_SUP 60 ///< Width of the upper display frame

#define CANVAS_HEIGTH DISPLAY_HEIGHT - FRAME_WIDTH_SUP ///< Height of the playable canvas area
#define CANVAS_WIDTH DISPLAY_WIDTH - FRAME_WIDTH ///< Width of the playable canvas area

// Gameplay Modes
#define GOD_MODE 0  ///< Toggle for invincibility mode (0 = off, 1 = on)

// SHIP CONFIGURATION
#define SHIP_INIT_POS_X DISPLAY_WIDTH / 2 ///< Initial X-coordinate for the ship
#define SHIP_INIT_POS_Y DISPLAY_HEIGHT - 90 ///< Initial Y-coordinate for the ship

#define SHIP_SPEED 6 ///< Ship movement speed
#define SHIP_BULLET_SPEED 15 ///< Speed of the ship's bullets

#define SHIP_TIMER 3 ///< Timer interval for ship's shooting cooldown

#define SHIP_LIFE 3 ///< Initial lives for the ship

// MARTIANS CONFIGURATION
#define MAX_ENEMIES 55 ///< Maximum number of enemies
#define NUM_ENEMY_X 11 ///< Number of martians per row
#define NUM_ENEMY_Y 5 ///< Number of martians per column

#define SPACE_BTW_MARTIANS_X 32 ///< Horizontal space between martians
#define SPACE_BTW_MARTIANS_Y 27 ///< Vertical space between martians

#define MART_INIT_POS_X 130 //500 ///< Initial X-coordinate for martians formation
#define MART_INIT_POS_Y 170 //100 ///< Initial Y-coordinate for martians formation


#define MART_SPEED 5 ///< Speed of the martian's movement
#define MART_BULLET_SPEED 5 ///< Speed of the martian's bullets

#define MART_MOVE_TIMER 20 ///< Timer interval for martian movement
#define MART_SHOOT_FREQ 75 ///< Frequency at which martians can shoot
#define MART_ANIMATION_SPEED 25 ///< Speed of the martian animation cycle

// BULLETS CONFIGURATION
#define MAX_ORP_BULLETS 20 ///< Maximum number of orphan bullets (bullets not associated with any ship or martian)

// OBJECT CONFIGURATION
#define OBJECT_TIMER 5 ///< Default timer value for objects (used in animations and expiration timing)
#define MAX_OBJECTS 55 ///< Maximum number of objects allowed in the game (e.g., explosions)

#define EXPLOSION_WIDTH 41 ///< Width of the explosion sprite
#define EXPLOSION_HEIGHT 34 ///< Height of the explosion sprite

#endif /* CONFIG_H */
