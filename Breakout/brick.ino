/**
 * @file brick.ino
 * @brief Implementation of brick initialization and collision handling.
 */

#include "brick.h"

void init_bricks(Brick bricks_array[]) {
  for (int8_t i = 0; i < BRICK_ROWS; i++) {
    for (int8_t j = 0; j < BRICK_COLUMNS; j++) {
      bricks_array[i * BRICK_COLUMNS + j].p.x = j * (BRICK_WIDTH + 1);
      bricks_array[i * BRICK_COLUMNS + j].p.y = i * (BRICK_HEIGHT + 1);
      bricks_array[i * BRICK_COLUMNS + j].alive = true;
    }
  }
}

bool ball_hits_brick(Ball ball, Brick brick) {
  return ball_hits_rectangle(ball, brick.p, BRICK_WIDTH, BRICK_HEIGHT);
}

void bounce_off_brick(Ball *ball_ptr, Brick brick) {
  Vector v_closest = v_closest_rect(ball_ptr->p, brick.p, BRICK_WIDTH, BRICK_HEIGHT);

  if (v_closest.x == brick.p.x || v_closest.x == (brick.p.x + BRICK_WIDTH)) {
    if (v_closest.y == brick.p.y || v_closest.y == (brick.p.y + BRICK_HEIGHT)) {
      // Corner hit: Reverse both directions
      ball_ptr->v.x *= -1;
      ball_ptr->v.y *= -1;
    } else {
      // Side hit: Reverse X
      ball_ptr->v.x *= -1;
    }
  } else {
    // Top/bottom hit: Reverse Y
    ball_ptr->v.y *= -1;
  }
}

void handle_bricks_collision(Ball *ball_ptr, Brick bricks_array[], int8_t *score) {
  for (int8_t i = 0; i < BRICK_ROWS * BRICK_COLUMNS; i++) {
    if (bricks_array[i].alive && ball_hits_brick(*ball_ptr, bricks_array[i])) {
      bricks_array[i].alive = false;
      (*score)++;
      bounce_off_brick(ball_ptr, bricks_array[i]);
      return;  // Handle one collision per frame to prevent multiples
    }
  }
}