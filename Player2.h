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
};

#endif