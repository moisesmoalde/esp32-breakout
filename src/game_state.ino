/**
 * @file game_state.ino
 * @brief Implementation of game state initialization and updates.
 */

#include "game_state.h"
#include "display.h"

void init_game(GameState *game_ptr) {
  game_ptr->lives = INIT_LIVES;
  game_ptr->score = INIT_SCORE;

  init_bricks(game_ptr->bricks_array);
  init_paddle(&game_ptr->paddle);
  init_ball(&game_ptr->ball, DISPLAY_WIDTH / 2, (DISPLAY_HEIGHT - PADDLE_HEIGHT) - 2 * BALL_RADIUS);
}

void update_elements(GameState *game_ptr, float dt) {
  paddle_update(&game_ptr->paddle, dt);
  ball_update(&game_ptr->ball, dt);
}

void handle_collisions(GameState *game_ptr) {
  handle_wall_collision(&game_ptr->ball, (game_ptr->paddle.p.x + PADDLE_WIDTH / 2), DISPLAY_WIDTH, DISPLAY_HEIGHT, &game_ptr->lives);
  handle_bricks_collision(&game_ptr->ball, game_ptr->bricks_array, &game_ptr->score);
  handle_paddle_collision(&game_ptr->ball, &game_ptr->paddle);
}

void update_game(GameState *game_ptr, float dt) {
  update_elements(game_ptr, dt);
  handle_collisions(game_ptr);
}