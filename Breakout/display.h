#ifndef INCLUDE_DISPLAY
#define INCLUDE_DISPLAY

const int16_t DISPLAY_WIDTH = 128;   // OLED display width in pixels
const int16_t DISPLAY_HEIGHT = 64;   // OLED display height in pixels
const int16_t DISPLAY_TOP_HEIGHT = 16;  // Top section for bricks
const int OLED_RESET = -1;           // Reset pin (-1 for shared reset)
const uint8_t DISPLAY_ADDRESS = 0x3C;

#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include "game_state.h"

/**
 * @brief Initializes the OLED display.
 */
void display_init();

/**
 * @brief Draws the ball on the display.
 * @param ball The Ball to draw.
 */
void draw_ball(Ball ball);

/**
 * @brief Draws the paddle on the display.
 * @param paddle The Paddle to draw.
 */
void draw_paddle(Paddle paddle);

/**
 * @brief Draws all bricks on the display.
 * @param bricks_array Array of Bricks.
 */
void draw_bricks(Brick bricks_array[]);

/**
 * @brief Draws score and lives on the display.
 * @param game The GameState containing score and lives.
 */
void draw_score_lives(GameState game);

/**
 * @brief Draws the entire game state on the display.
 * @param game The GameState to render.
 */
void draw_game(GameState game);

#endif