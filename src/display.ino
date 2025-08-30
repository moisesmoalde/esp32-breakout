/**
 * @file display.ino
 * @brief Implementation of display functions using Adafruit SSD1306 library.
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "display.h"

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET);

// Heart bitmap for lives (16x16, stored in PROGMEM to save RAM)
const int HEART_HEIGHT = 16;
const int HEART_WIDTH = 16;
static const uint8_t PROGMEM heart_bmp[] = {
  0x00, 0x00, 0x3e, 0x7c, 0x7f, 0xfe, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0,
  0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00
};

void display_init() {
  Wire.begin();  // Initialize I2C
  Wire.setClock(400000);  // Fast mode

  if (!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    // Instead of infinite loop, could add retry logic here
    for (;;);
  }
  Wire.setClock(400000);  // Ensure fast mode post-init
}

void draw_ball(Ball ball) {
  display.fillCircle(ball.p.x, ball.p.y, ball.r, SSD1306_WHITE);
}

void draw_paddle(Paddle paddle) {
  display.fillRoundRect(paddle.p.x, paddle.p.y, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_RADIUS, SSD1306_WHITE);
}

void draw_bricks(Brick bricks_array[]) {
  for (int8_t i = 0; i < BRICK_ROWS * BRICK_COLUMNS; i++) {
    if (bricks_array[i].alive) {
      display.fillRect(bricks_array[i].p.x, bricks_array[i].p.y, BRICK_WIDTH, BRICK_HEIGHT, SSD1306_WHITE);
    }
  }
}

void draw_score_lives(GameState game) {
  for (int8_t i = 0; i < game.lives; i++) {
    display.drawBitmap(DISPLAY_WIDTH - HEART_WIDTH, DISPLAY_HEIGHT - (i + 1) * HEART_HEIGHT, heart_bmp, HEART_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
  }

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, DISPLAY_HEIGHT - PADDLE_HEIGHT - 8);
  display.cp437(true);
  display.println(game.score);
}

void draw_game(GameState game) {
  display.clearDisplay();

  draw_paddle(game.paddle);
  draw_ball(game.ball);
  draw_bricks(game.bricks_array);
  draw_score_lives(game);

  display.display();
}