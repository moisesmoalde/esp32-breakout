/**
 * @file ball.ino
 * @brief Implementation of ball initialization, update, and collisions.
 */

#include "ball.h"

void init_ball(Ball *ball, float pos_x, float pos_y) {
  ball->r = BALL_RADIUS;
  ball->p.x = pos_x;
  ball->p.y = pos_y;
  ball->m = ball->r * ball->r;  // Mass proportional to area

  // Random X velocity, ensure non-zero
  ball->v.x = random(10, BALL_MAX_SPEED);  // Bias away from zero
  if (random(0, 2)) ball->v.x *= -1;       // Random direction
  ball->v.y = sqrt(BALL_MAX_SPEED * BALL_MAX_SPEED - ball->v.x * ball->v.x);  // Maintain speed
}

void handle_wall_collision(Ball *b, float paddle_pos_x, int16_t width, int16_t height, int8_t *lives) {
  // Left/right walls
  if ((b->p.x - b->r <= 0 && b->v.x < 0) || (b->p.x + b->r >= width && b->v.x > 0)) {
    b->v.x *= -1;
  }

  // Top wall
  if (b->p.y - b->r <= 0 && b->v.y < 0) {
    b->v.y *= -1;
  }

  // Bottom: Lose life and respawn
  if (b->p.y + b->r >= height && b->v.y > 0) {
    (*lives)--;

    if (*lives <= 0) {
      b->v.x = 0;
      b->v.y = 0;  // Game over: Stop ball
    } else {
      init_ball(b, paddle_pos_x, height - PADDLE_HEIGHT - 3 * BALL_RADIUS);  // Respawn above paddle
    }
  }
}

void ball_update(Ball *b, float dt) {
  b->p.x += b->v.x * dt;
  b->p.y += b->v.y * dt;
}

bool ball_hits_rectangle(Ball ball, Vector p_rect, int8_t width, int8_t height) {
  Vector v_closest = v_closest_rect(ball.p, p_rect, width, height);
  return dist_sq(ball.p, v_closest) <= ball.r * ball.r;
}