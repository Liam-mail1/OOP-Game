#include "Player1.h"
#include "Tank.h"
#include "raylib.h"
#include <cmath>
#include <iostream>

Player1::Player1() : Tank(), health(100), direction(0.0f), speed(5.0f) {
  // load texture, and read its dimensions
  image = LoadTexture("tankTexture.png");
  frameWidth = image.width;
  frameHeight = image.height;
  // Check if the texture was loaded correctly
    if (image.width <= 0 || image.height <= 0) {
        std::cerr << "Error loading texture! Check the file path." << std::endl;
        // You might want to set default values here
    } else {
        frameWidth = image.width;
        frameHeight = image.height;

        // Log initialized values
        std::cout << "Initialized Player1 with health: " << health
                  << ", direction: " << direction << ", speed: " << speed
                  << ", texture width: " << frameWidth
                  << ", texture height: " << frameHeight << std::endl;
    }

  // spwan location, where the tank first appera
  xPos = startingX;
  yPos = startingY;
  sourceRec = {0, 0, (float)frameWidth, (float)frameHeight};
  origin = {(float)frameWidth / 2, (float)frameHeight / 2};
  destRec = {(float)this->xPos, (float)this->yPos, (float)frameWidth, (float)frameHeight};
}

void Player1::draw() { // draw the tank with its texture inside of that
  float scaleFactor = 0.15f;
  // Calculate the scaled size
  float scaledWidth = frameWidth * scaleFactor;
  float scaledHeight = frameHeight * scaleFactor;
  // Update destRec to reflect the new size
  destRec = {(float)this->xPos, (float)this->yPos, scaledWidth, scaledHeight};
  origin = {scaledWidth / 2, scaledHeight / 2};
  DrawTexturePro(image, sourceRec, destRec, origin, (float)direction * 180 / PI, WHITE);

};

void Player1::moveInput() {

  // check for movement input
  // the direction is a float, treated as the radiant of player's face direction
  if (IsKeyDown(KEY_RIGHT)) {
        direction += 0.1;
    } else if (IsKeyDown(KEY_LEFT)) {
        direction -= 0.1;
    }

  // update the player's location according to the previous movement input
  if (IsKeyDown(KEY_UP)) {
        xPos += speed * cos(direction);
        yPos += speed * sin(direction);
    } else if (IsKeyDown(KEY_DOWN)) {
        xPos -= speed * cos(direction);
        yPos -= speed * sin(direction);
    }
}

void Player1::fire() { // spwan a projectile
  if (IsKeyPressed(KEY_ENTER)) {
        float offset = 20.0f;
        // Calculate the position in front of the player
        float projectileX = getX() + cos(direction) * offset;
        float projectileY = getY() + sin(direction) * offset;

        // Create the projectile and add it to the projectiles vector
        Projectile newProjectile(static_cast<int>(projectileX), static_cast<int>(projectileY), speed, direction);
        projectiles.push_back(newProjectile);
    }
}

void Player1::reset() {
  health = initialHealth; // Reset health
  xPos = startingX;   
  yPos = startingY;
}

Player1::~Player1() {
    if (image.id > 0) {
        UnloadTexture(image);
    }
}

