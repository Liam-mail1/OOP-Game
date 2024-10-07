#ifndef TANK_H
#define TANK_H
#include "Entity.h"

// tank class, parent class for both player 1 and 2, this is the abstract class
// and also the second of the
// three layers of inhereitance

class Tank : public Entity {

public:
  Tank(); // defalut constructor.

  // three pure virtual method used for overriden
  virtual void draw() = 0;
  virtual void moveInput() = 0;
  virtual void fire() = 0;

  // return values
  int getXpos();
  int getYpos();
  float getDire();

protected:
  int health;
  double direction;
};

#endif