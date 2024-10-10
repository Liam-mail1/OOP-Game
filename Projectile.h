#pragma once
#include "Entity.h"
#include "raylib.h"

class Projectile : public Entity {
private:
  double direction;
  int counter;
  bool timeout;
  int radius;
  float xSpeed;
  float ySpeed;
  int framecount;

public:
  Projectile();
  Projectile(int X, int Y, int Speed, double dire);
  void draw();
  void update();
  void selfDes();
  bool getTimeOut();
  int getX();
  int getY();
  int getRad();
  void relfectX();
  void reflectY();
  void upFrame();
  void reFrame();
  int getFrame();
  bool calcFrame();
};
