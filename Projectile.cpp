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
  radius = 7;
  xSpeed = speed * cos(direction);
  ySpeed = speed * sin(direction);
}

void Projectile::draw() { DrawCircle(xPos, yPos, radius, BLACK); };
void Projectile::update() {
  xPos = xPos + xSpeed;
  yPos = yPos + ySpeed;
  if (counter >= 120) {
    timeout = true;
  }
  counter++;
};

bool Projectile::getTimeOut() { return timeout; }

int Projectile::getX() { return xPos; }
int Projectile::getY() { return yPos; }
int Projectile::getRad() { return radius; }

void Projectile::relfectX() { xSpeed = xSpeed * -1; };
void Projectile::reflectY() { ySpeed = ySpeed * -1; };

void Projectile::upFrame() { framecount++; }
void Projectile ::reFrame() { framecount = 0; }
bool Projectile::calcFrame() {
  if (framecount > 10) {
    framecount = 0;
    return true;
  } else {
    return false;
  };
}