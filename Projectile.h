#pragma once
#include "Entity.h"
#include "raylib.h"

class Projectile : public Entity {
private:
  double direction;
  int counter;
  bool timeout;
  float radius;
  float xSpeed;
  float ySpeed;
  int framecount;
  float xPos;
  float yPos;
  int speed = 10;
  bool active;

public:
  Projectile();
  ~Projectile() {};
  Projectile(int X, int Y, int Speed, double dire);
  void draw();
  void update();
  void selfDes();
  bool getTimeOut();
  int getX() const { return static_cast<int>(xPos); } // Get X position
  int getY() const { return static_cast<int>(yPos); } // Get Y position
  int getRad();
  void reflectX();
  void reflectY();
  void upFrame();
  void reFrame();
  int getFrame();
  bool calcFrame();
  void setTimeOut(bool value) { timeout = value; }
  Rectangle getCollisionRectangle() const;
  // Function to check if the projectile is expired
  bool isExpired() const {
    return !active; // Returns true if the projectile is no longer active
  }

  void setPosition(float x, float y) {
        xPos = x; // Update X position
        yPos = y; // Update Y position
  }
  
};
