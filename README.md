# ESP32 Breakout Game

A classic Breakout (Arkanoid-style) game implemented on an ESP32 microcontroller with an SSD1306 OLED display. The player controls a paddle via a potentiometer to bounce a ball and destroy bricks.

## Features
- Smooth gameplay using double buffering and ESP32's dual cores (one for updates, one for rendering).
- Potentiometer-controlled paddle with smoothing to reduce jitter.
- Collision detection for walls, paddle, and bricks.
- Score and lives tracking with heart icons.
- Random initial ball velocity.

## Hardware Requirements
- ESP32 board (e.g., ESP32 DevKit).
- SSD1306 OLED display (128x64 pixels, I2C address 0x3C).
- Potentiometer connected to GPIO 34 (ADC pin).
- Wiring:
  - OLED: SDA to GPIO 21, SCL to GPIO 22 (default I2C).
  - Potentiometer: Middle pin to GPIO 34, sides to 3.3V and GND.
  ![alt text](https://github.com/moisesmoalde/esp32-breakout/blob/main/wiring.png?raw=true)


## Software Dependencies
- Arduino IDE with ESP32 board support.
- Libraries:
  - Adafruit SSD1306 (for OLED).
  - Adafruit GFX (included with SSD1306).
  - Wire (built-in for I2C).

Install libraries via Arduino Library Manager.

## Setup and Installation
1. Clone this repository: `git clone https://github.com/moisesmoalde/esp32-breakout.git`
2. Open `Breakout.ino` in Arduino IDE.
3. Select your ESP32 board and port.
4. Upload the sketch.

## How to Play
- Turn the potentiometer to move the paddle left/right.
- Bounce the ball to destroy all bricks.
- Lose a life if the ball falls below the paddle.
- Game stops when lives reach 0 (add reset button for restart if desired).

## Code Structure
- `Breakout.ino`: Main setup and tasks for update/draw.
- `game_state.*`: Game state management.
- `display.*`: OLED rendering functions.
- `paddle.*`: Paddle control and collisions.
- `ball.*`: Ball physics and collisions.
- `brick.*`: Brick initialization and destruction.
- `utils.*`: Vector math utilities.

## TODO
- Add win condition (e.g., all bricks destroyed).
- Implement multiple levels or power-ups.
- Add sound effects (e.g., via buzzer).
- Optimize for lower power consumption.
- Unit tests for utilities.

## License
MIT License. Feel free to modify and share!

## Credits
Built with inspiration from classic arcade games. Uses Adafruit libraries for display.
