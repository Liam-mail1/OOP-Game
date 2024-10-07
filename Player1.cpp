#include "Player1.h"
#include "Tank.h"
#include "raylib.h"
#include <cmath>

Player1::Player1() : Tank() {
  // load texture, and read its dimensions
  image = LoadTexture("tankTexture.png");
  frameWidth = image.width;
  frameHeight = image.height;

  // spwan location, where the tank first appera
  xPos = 1200;
  yPos = 900;
  // health
  health = 2;

  // create a rectangle, used to resize and rotate the texture in game
  sourceRec = {0, 0, (float)frameWidth, (float)frameHeight};
  origin = {(float)frameWidth - 565, (float)frameHeight - 375};
  destRec = {(float)this->xPos, (float)this->yPos, frameHeight * 1.0f,
             frameWidth * 1.0f};
}

void Player1::draw() { // draw the tank with its texture inside of that
                       // rectangle
  DrawTexturePro(image, sourceRec, destRec, origin, (float)direction * 180 / PI,
                 WHITE);
};

void Player1::moveInput() {

  // check for movement input
  // the direction is a float, treated as the radiant of player's face direction
  if (IsKeyDown(KEY_RIGHT)) {
    direction = direction + 0.1;
  } else if (IsKeyDown(KEY_LEFT)) {
    direction = direction - 0.1;
  }

  // update the player's location according to the previous movement input
  if (IsKeyDown(KEY_UP)) {
    xPos = xPos + speed * cos(direction);
    yPos = yPos + speed * sin(direction);
  } else if (IsKeyDown(KEY_DOWN)) {
    xPos = xPos - speed * cos(direction);
    yPos = yPos - speed * sin(direction);
  }
  // move the rectangle to the new locatiopn
  destRec = {(float)this->xPos, (float)this->yPos, frameHeight * 0.2f,
             frameWidth * 0.1f};
}

void Player1::fire() { // spwan a projectile
  if (IsKeyPressed(KEY_KP_1)) {
    projectiles.push_back(Projectile(xPos, yPos, 3, direction));
  }
}

Player1::~Player1() { UnloadTexture(image); };