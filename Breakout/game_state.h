#ifndef INCLUDE_GAME_STATE
#define INCLUDE_GAME_STATE

#include "brick.h"
#include "ball.h"
#include "paddle.h"

const int8_t INIT_LIVES = 3;
const int8_t INIT_SCORE = 0;

/**
 * @struct GameState
 * @brief Represents the entire game state, including lives, score, and game objects.
 */
typedef struct {
  int8_t lives, score;
  Paddle paddle;
  Ball ball;
  Brick bricks_array[BRICK_ROWS * BRICK_COLUMNS];
} GameState;

/**
 * @brief Initializes the game state with default values.
 * @param game_ptr Pointer to the GameState to initialize.
 */
void init_game(GameState *game_ptr);

/**
 * @brief Updates game elements (paddle and ball) based on delta time.
 * @param game_ptr Pointer to the GameState.
 * @param dt Delta time in seconds.
 */
void update_elements(GameState *game_ptr, float dt);

/**
 * @brief Handles all collisions in the game.
 * @param game_ptr Pointer to the GameState.
 */
void handle_collisions(GameState *game_ptr);

/**
 * @brief Main update function: Updates elements and handles collisions.
 * @param game_ptr Pointer to the GameState.
 * @param dt Delta time in seconds.
 */
void update_game(GameState *game_ptr, float dt);

#endif