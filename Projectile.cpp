#include "Projectile.h"
#include <cmath>

Projectile::Projectile() : Entity(), direction(0), counter(0), timeout(false), radius(7), xSpeed(0), ySpeed(0), framecount(0), xPos(0), yPos(0), speed(0), active(true) {}


Projectile::Projectile(int X, int Y, int Speed, double dire)
    : Entity(), direction(dire), counter(0), timeout(false), radius(7), xPos(X), yPos(Y), speed(Speed), active(true) {
    xSpeed = speed * cos(direction); // Ensure direction is in radians
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
  DrawCircle(xPos, yPos, radius, BLACK); // Ensure this matches the position
  Rectangle collisionBox = getCollisionRectangle();
  DrawRectangleLines(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, RED); // Draw collision box
};

bool Projectile::getTimeOut() { return timeout; }

int Projectile::getRad() { return radius; }

void Projectile::reflectX() { xSpeed = xSpeed * -1; };
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
Rectangle Projectile::getCollisionRectangle() const {
    return Rectangle{
        xPos - radius, // Adjust for the radius
        yPos - radius,
        radius * 2,    // Width is double the radius
        radius * 2     // Height is double the radius
    };
}

