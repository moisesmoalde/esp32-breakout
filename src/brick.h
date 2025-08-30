#ifndef INCLUDE_BRICK
#define INCLUDE_BRICK

const int BRICK_HEIGHT = 7;
const int BRICK_WIDTH = 15;
const int BRICK_ROWS = 2;    // Fits top yellow section
const int BRICK_COLUMNS = 8; // Fits screen width

#include "ball.h"

/**
 * @struct Brick
 * @brief Represents a brick with position and alive status.
 */
typedef struct {
  Vector p;
  bool alive;
} Brick;

/**
 * @brief Initializes the array of bricks.
 * @param bricks_array Array to initialize.
 */
void init_bricks(Brick bricks_array[]);

/**
 * @brief Checks if ball collides with a brick.
 * @param ball Ball.
 * @param brick Brick.
 * @return True if colliding.
 */
bool ball_hits_brick(Ball ball, Brick brick);

/**
 * @brief Bounces ball off brick, adjusting velocity based on hit side.
 * @param ball_ptr Pointer to Ball.
 * @param brick Brick.
 */
void bounce_off_brick(Ball *ball_ptr, Brick brick);

/**
 * @brief Handles collisions with all bricks, updates score.
 * @param ball_ptr Pointer to Ball.
 * @param bricks_array Array of Bricks.
 * @param score Pointer to score.
 */
void handle_bricks_collision(Ball *ball_ptr, Brick bricks_array[], int8_t *score);

#endif