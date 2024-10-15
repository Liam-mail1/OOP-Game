#include "Entity.h"

Entity::Entity(int xPosition, int yPosition, int Speed)
    : xPos(xPosition), yPos(yPosition), speed(Speed){};

Entity::Entity() {
  xPos = 1000;
  yPos = 1000;
  speed = 3;
};
