#include "Projectile.h"
#include <cmath>

Projectile::Projectile() : Entity(){};

Projectile::Projectile(int X, int Y, int Speed, double dire) {
  direction = dire;
  xPos = X;
  yPos = Y;
  speed = Speed;
  counter = 0;
  timeout = false;
}

void Projectile::draw() { DrawCircle(xPos, yPos, 7, BLACK); };
void Projectile::update() {
  xPos = xPos + speed * cos(direction);
  yPos = yPos + speed * sin(direction);
  if (counter >= 120) {
    timeout = true;
  }
  counter++;
};

bool Projectile::getTimeOut() { return timeout; }
