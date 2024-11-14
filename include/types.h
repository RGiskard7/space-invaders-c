#ifndef TYPES_H
#define	TYPES_H

#include <time.h>

/**
 * @brief Enumeration for directional movement within the game.
 * 
 * Directions are used to manage movement for the ship and martians,
 * specifying possible directions as DOWN, LEFT, RIGHT, UP, and NO_DIR
 * for cases where no movement is currently happening.
 */
enum {
    DOWN, ///< Move downwards
    LEFT, ///< Move leftwards
    RIGHT, ///< Move rightwards
    UP, ///< Move upwards
    NO_DIR ///< No movement
};

/**
 * @brief Enumeration for status return values.
 * 
 * Defines standard return values for functions throughout the game
 * code, allowing for consistent status checking with OK for success
 * and ERROR for failure.
 */
typedef enum {
    OK, ///< Operation was successful
    ERROR ///< Operation encountered an error
} STATUS;

#endif	/* TYPES_H */