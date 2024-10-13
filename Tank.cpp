#include "Tank.h"
#include <cmath>

Tank::Tank() : Entity(), health(1), direction(0.0){};

Tank::Tank(int xPosition, int yPosition, int speedValue) : Entity(xPosition, yPosition, speedValue) {}

float Tank::getDire() { return direction; };
int Tank::getXpos() { return xPos; };
int Tank::getYpos() { return yPos; };