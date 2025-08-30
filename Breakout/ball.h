#ifndef INCLUDE_BALL
#define INCLUDE_BALL

const int BALL_RADIUS = 4;
const int BALL_MAX_SPEED = 50;

#include "utils.h"

/**
 * @struct Ball
 * @brief Represents a ball with position, velocity, radius, and mass.
 */
typedef struct {
  int16_t id;
  float r, m;
  Vector p, v;
} Ball;

/**
 * @brief Initializes a ball at given position with random velocity.
 * @param ball Pointer to Ball.
 * @param pos_x X position.
 * @param pos_y Y position.
 */
void init_ball(Ball *ball, float pos_x, float pos_y);

/**
 * @brief Handles ball collisions with walls and bottom (life loss).
 * @param b Pointer to Ball.
 * @param paddle_pos_x Paddle's center X for respawn.
 * @param width Screen width.
 * @param height Screen height.
 * @param lives Pointer to lives counter.
 */
void handle_wall_collision(Ball *b, float paddle_pos_x, int16_t width, int16_t height, int8_t *lives);

/**
 * @brief Updates ball position based on velocity and dt.
 * @param b Pointer to Ball.
 * @param dt Delta time.
 */
void ball_update(Ball *b, float dt);

/**
 * @brief Checks if ball collides with a rectangle.
 * @param ball Ball.
 * @param p_rect Rectangle position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return True if colliding.
 */
bool ball_hits_rectangle(Ball ball, Vector p_rect, int8_t width, int8_t height);

// Note: Multiple balls functions removed as unused; can be added back if needed.

#endif