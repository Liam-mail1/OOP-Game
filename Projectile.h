#pragma once
#include "Entity.h"
#include "raylib.h"

class Projectile : public Entity {
private:
  double direction;
  int counter;
  bool timeout;

public:
  Projectile();
  Projectile(int X, int Y, int Speed, double dire);
  void draw();
  void update();
  void selfDes();
  bool getTimeOut();
};
