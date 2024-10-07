#ifndef ENTITY_H
#define ENTITY_H

// base entity class, nothing special here
#include "raylib.h"
class Entity {
protected:
  int xPos, yPos;
  int speed;

public:
  Entity(int xPosition, int yPosition, int speed);
  Entity();
};
#endif
