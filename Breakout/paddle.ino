/**
 * @file paddle.ino
 * @brief Implementation of paddle initialization, update, and collision handling.
 */

#include "paddle.h"
#include "display.h"

void init_paddle(Paddle *paddle_ptr) {
  paddle_ptr->p.x = PADDLE_INIT_X;
  paddle_ptr->p.y = (DISPLAY_HEIGHT - PADDLE_HEIGHT);

  analogReadResolution(POT_ADC_BITS);  // Set ADC resolution
}

void paddle_update(Paddle *paddle_ptr, float dt) {
  // Read potentiometer (0-4095)
  int pot_value = analogRead(POT_PIN);
  const int min_value = 1 << (POT_ADC_BITS - 2);  // 1024
  const int max_value = (3 * min_value) - 1;      // 3071

  // Clamp value for sensitivity
  if (pot_value < min_value) pot_value = min_value;
  if (pot_value > max_value) pot_value = max_value;

  // Map to paddle X position
  float paddle_x = map(pot_value, min_value, max_value, 0, DISPLAY_WIDTH - PADDLE_WIDTH);

  // Smooth with weighted average to reduce jitter
  static float smoothed_x = PADDLE_INIT_X;
  smoothed_x = smoothed_x * (1 - SENSITIVITY) + paddle_x * SENSITIVITY;
  paddle_ptr->p.x = smoothed_x;

  // Ensure paddle stays within bounds (improvement)
  if (paddle_ptr->p.x < 0) paddle_ptr->p.x = 0;
  if (paddle_ptr->p.x > DISPLAY_WIDTH - PADDLE_WIDTH) paddle_ptr->p.x = DISPLAY_WIDTH - PADDLE_WIDTH;
}

bool ball_hits_paddle(Ball ball, Paddle paddle) {
  return ball_hits_rectangle(ball, paddle.p, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void bounce_off_paddle(Ball *ball_ptr, Paddle *paddle_ptr) {
  // Find closest point on paddle
  Vector v_closest = v_closest_rect(ball_ptr->p, paddle_ptr->p, PADDLE_WIDTH, PADDLE_HEIGHT);

  // Calculate relative hit position (-1 to +1)
  float relative_pos = 2 * (v_closest.x - (paddle_ptr->p.x + PADDLE_WIDTH / 2)) / PADDLE_WIDTH;

  // Adjust X velocity for control
  ball_ptr->v.x = CONTROL_FACTOR * relative_pos;

  // Adjust Y velocity to maintain speed, bounce upward
  ball_ptr->v.y = -sqrt(BALL_MAX_SPEED * BALL_MAX_SPEED - ball_ptr->v.x * ball_ptr->v.x);

  // Prevent sticking: Move ball above paddle
  ball_ptr->p.y = paddle_ptr->p.y - ball_ptr->r;
}

void handle_paddle_collision(Ball *ball_ptr, Paddle *paddle_ptr) {
  if (ball_hits_paddle(*ball_ptr, *paddle_ptr)) {
    bounce_off_paddle(ball_ptr, paddle_ptr);
  }
}