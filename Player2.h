#ifndef PLAYER2_H
#define PLAYER2_H
#include "Projectile.h"
#include "Tank.h"
#include <vector>

// player 2 is very similar to player 1

class Player2 : public Tank {
private:
  int frameWidth;
  int frameHeight;
  Texture2D image;
  Vector2 origin;
  Rectangle sourceRec;
  Rectangle destRec;

public:
  std::vector<Projectile> projectiles;
  Player2();
  ~Player2();
  void moveInput();
  void fire();
  void draw();

  // Getter methods to access private members
  float getFrameWidth() const { return static_cast<float>(frameWidth); }
  float getFrameHeight() const { return static_cast<float>(frameHeight); }
  float getX() const { return static_cast<float>(xPos); } 
  float getY() const { return static_cast<float>(yPos); }

  Rectangle getCollisionRectangle() const {
    return { static_cast<float>(xPos), static_cast<float>(yPos),
             static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
  }
};

#endif