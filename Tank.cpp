#include "Tank.h"
#include <cmath>

Tank::Tank() : Entity(), health(1), direction(0.0){};

float Tank::getDire() { return direction; };
int Tank::getXpos() { return xPos; };
int Tank::getYpos() { return yPos; };