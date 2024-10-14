#include "Player2.h"
#include "Tank.h"
#include "raylib.h"
#include <cmath>

Player2::Player2() : Tank(), health(100), direction(0.0f), speed(5.0f) {
  image = LoadTexture("tankRed.png");
  frameWidth = image.width;
  frameHeight = image.height;
  xPos = startingX; 
  yPos = startingY;

  // create a rectangle, used to resize and rotate the texture in game
  sourceRec = {0, 0, (float)frameWidth, (float)frameHeight};
  origin = {(float)frameWidth / 2, (float)frameHeight / 2};
  destRec = {(float)this->xPos, (float)this->yPos, (float)frameWidth, (float)frameHeight};
}

void Player2::draw() {
  float scaleFactor = 0.2f;
  // Calculate the scaled size
  float scaledWidth = frameWidth * scaleFactor;
  float scaledHeight = frameHeight * scaleFactor;
  // Update destRec to reflect the new size
  destRec = {(float)this->xPos, (float)this->yPos, scaledWidth, scaledHeight};
  origin = {scaledWidth / 2, scaledHeight / 2};
  DrawTexturePro(image, sourceRec, destRec, origin, (float)direction * 180 / PI, WHITE);
};

void Player2::moveInput() {
  if (IsKeyDown(KEY_A)) {
    direction = direction - 0.1;
  } else if (IsKeyDown(KEY_D)) {
    direction = direction + 0.1;
  }

  if (IsKeyDown(KEY_W)) {
    xPos += speed * cos(direction);
    yPos += speed * sin(direction);
  } else if (IsKeyDown(KEY_S)) {
    xPos -= speed * cos(direction);
    yPos -= speed * sin(direction);
  }
  destRec = {(float)this->xPos, (float)this->yPos, (float)frameWidth, (float)frameHeight}; 
}

void Player2::fire() {
  if (IsKeyPressed(KEY_SPACE)) {
        float offset = 20.0f;
        // Calculate the position in front of the player
        float projectileX = getX() + cos(direction) * offset;
        float projectileY = getY() + sin(direction) * offset;

        // Create the projectile and add it to the projectiles vector
        Projectile newProjectile(static_cast<int>(projectileX), static_cast<int>(projectileY), speed, direction);
        projectiles.push_back(newProjectile);
    }
}

void Player2::reset() {
  health = initialHealth; // Reset health
  xPos = startingX;
  yPos = startingY;
}



Player2::~Player2() { UnloadTexture(image); };