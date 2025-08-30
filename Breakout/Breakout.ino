/**
 * @file Breakout.ino
 * @brief Main entry point for the Breakout game on ESP32 with OLED display.
 * 
 * This file sets up the game using double buffering for smooth updates and rendering.
 * It creates two tasks: one for updating game logic (on core 0) and one for drawing (on core 1).
 * Synchronization is handled via FreeRTOS task notifications.
 */

#include "game_state.h"
#include "display.h"

/* Double buffer:
 * Maintain two game states:
 *   - frontBuffer: Read-only for rendering by draw task.
 *   - backBuffer: Updated by update task.
 * Swap pointers atomically after each update to avoid tearing.
 */
GameState game_A, game_B;
GameState *front_buff = &game_A;
GameState *back_buff = &game_B;

unsigned long now, last;

TaskHandle_t draw_handle, update_handle;

/**
 * @brief Update task: Handles game logic updates on back buffer.
 * 
 * Waits for draw task to finish, copies front to back, updates, then swaps buffers.
 * Notifies draw task when a new frame is ready.
 */
void update_task(void *param) {
  while (true) {
    // Wait for draw task to signal completion
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Copy front state to back before updating
    *back_buff = *front_buff;

    // Calculate delta time (dt) in seconds
    now = millis();
    float dt = (now - last) / 1000.0;
    last = now;
    Serial.printf("FPS: %f\n", 1 / dt);

    // Update game logic on back buffer
    update_game(back_buff, dt);

    // Atomic buffer swap
    GameState *tmp = front_buff;
    front_buff = back_buff;
    back_buff = tmp;

    // Notify draw task that new frame is ready
    xTaskNotifyGive(draw_handle);
  }
}

/**
 * @brief Draw task: Renders the front buffer to the display.
 * 
 * Waits for update task to signal, draws the game, then notifies update task.
 */
void draw_task(void *param) {
  while (true) {
    // Wait for update task to signal frame ready
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    draw_game(*front_buff);

    // Notify update task that drawing is complete
    xTaskNotifyGive(update_handle);
  }
}

/**
 * @brief Arduino setup function: Initializes hardware and tasks.
 */
void setup() {
  Serial.begin(115200);

  // Seed random for better ball velocity randomness
  randomSeed(analogRead(35));  // Use an unused pin for noise

  display_init();
  init_game(front_buff);
  last = millis();

  // Create tasks pinned to specific cores
  xTaskCreatePinnedToCore(update_task, "UpdateTask", 4096, NULL, 1, &update_handle, 0);  // Core 0 for updates
  xTaskCreatePinnedToCore(draw_task, "DrawTask", 4096, NULL, 1, &draw_handle, 1);        // Core 1 for drawing

  // Initial notifications to start tasks
  xTaskNotifyGive(draw_handle);   // First frame ready for draw
  xTaskNotifyGive(update_handle); // Draw ready for initial update
}

/**
 * @brief Arduino loop function: Empty as tasks handle everything.
 */
void loop() {
  // No-op: All logic in tasks
}