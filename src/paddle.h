#ifndef INCLUDE_PADDLE
#define INCLUDE_PADDLE

const int POT_PIN = 34;
const int POT_ADC_BITS = 12;  // ESP32 ADC resolution

const int PADDLE_HEIGHT = 6;
const int PADDLE_WIDTH = 24;
const int PADDLE_RADIUS = 2;
const int PADDLE_INIT_X = 52;  // Centered: (DISPLAY_WIDTH - PADDLE_WIDTH) / 2
const float SENSITIVITY = 0.4;  // For smoothing paddle movement
const float CONTROL_FACTOR = 30;  // For ball bounce control

#include "ball.h"

/**
 * @struct Paddle
 * @brief Represents the player's paddle with position.
 */
typedef struct {
  Vector p;
} Paddle;

/**
 * @brief Initializes the paddle at starting position.
 * @param paddle_ptr Pointer to Paddle.
 */
void init_paddle(Paddle *paddle_ptr);

/**
 * @brief Updates paddle position based on potentiometer input.
 * @param paddle_ptr Pointer to Paddle.
 * @param dt Delta time (unused here but for consistency).
 */
void paddle_update(Paddle *paddle_ptr, float dt);

/**
 * @brief Checks if ball collides with paddle.
 * @param ball The Ball.
 * @param paddle The Paddle.
 * @return True if colliding.
 */
bool ball_hits_paddle(Ball ball, Paddle paddle);

/**
 * @brief Bounces ball off paddle, adjusting velocity based on hit position.
 * @param ball_ptr Pointer to Ball.
 * @param paddle_ptr Pointer to Paddle.
 */
void bounce_off_paddle(Ball *ball_ptr, Paddle *paddle_ptr);

/**
 * @brief Handles paddle-ball collision if detected.
 * @param ball_ptr Pointer to Ball.
 * @param paddle_ptr Pointer to Paddle.
 */
void handle_paddle_collision(Ball *ball_ptr, Paddle *paddle_ptr);

#endif