#ifndef PLAYER1_H
#define PLAYER1_H
#include "Projectile.h"
#include "Tank.h"
#include <vector>

class Player1 : public Tank {
private:
  // all of these members are from raylib and are used for loading texture
  int frameWidth;
  int frameHeight;
  Texture2D image;
  Vector2 origin;
  Rectangle sourceRec;
  Rectangle destRec;

public:
  std::vector<Projectile>
      projectiles; // a vector used to store all the projectiles fired

  Player1();
  ~Player1();

  void moveInput(); // check for input, and then update its position
  void fire();      // spwan a projectile, stored in vector "projectiles"
  void draw();      // draw the tank at corrspounding location
};

#endif