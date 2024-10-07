#include "Player2.h"
#include "Tank.h"
#include "raylib.h"
#include <cmath>

Player2::Player2() : Tank() {
  image = LoadTexture("tankRed.png");
  frameWidth = image.width;
  frameHeight = image.height;
  xPos = 700;
  yPos = 700;
  speed = 5;

  sourceRec = {0, 0, (float)frameWidth, (float)frameHeight};

  origin = {(float)frameWidth - 395, (float)frameHeight - 275};

  destRec = {(float)this->xPos, (float)this->yPos, frameHeight * 1.0f,
             frameWidth * 1.0f};
}

void Player2::draw() {
  DrawTexturePro(image, sourceRec, destRec, origin, (float)direction * 180 / PI,
                 WHITE);
};

void Player2::moveInput() {
  if (IsKeyDown(KEY_A)) {
    direction = direction + 0.15;
  } else if (IsKeyDown(KEY_D)) {
    direction = direction - 0.15;
  }

  if (IsKeyDown(KEY_W)) {
    xPos = xPos + speed * cos(direction);
    yPos = yPos + speed * sin(direction);
  } else if (IsKeyDown(KEY_S)) {
    xPos = xPos - speed * cos(direction);
    yPos = yPos - speed * sin(direction);
  }
  destRec = {(float)this->xPos, (float)this->yPos, frameHeight * 0.2f,
             frameWidth * 0.1f};
}

void Player2::fire() {
  if (IsKeyPressed(KEY_SPACE)) {
    projectiles.push_back(Projectile(xPos, yPos, 3, direction));
  }
}

Player2::~Player2() { UnloadTexture(image); };