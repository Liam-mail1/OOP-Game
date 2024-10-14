#ifndef PLAYER1_H
#define PLAYER1_H
#include "Projectile.h"
#include "Tank.h"
#include <vector>

class Player1 : public Tank {
private:
  // all of these members are from raylib and are used for loading texture
  int frameWidth;
  int frameHeight;
  Texture2D image;

  int health;
  float direction;
  float speed;

  // Rectangle and origin for drawing and rotation
  Rectangle sourceRec;
  Rectangle destRec;
  Vector2 origin; 
  

public:
  std::vector<Projectile>
      projectiles; // a vector used to store all the projectiles fired

  Player1();
  ~Player1();

  void moveInput(); // check for input, and then update its position
  void fire();      // spwan a projectile, stored in vector "projectiles"
  void draw();      // draw the tank at corrspounding location

  // Getter methods to access private members
  float getFrameWidth() const { return static_cast<float>(frameWidth); }
  float getFrameHeight() const { return static_cast<float>(frameHeight); }
  float getX() const { return static_cast<float>(xPos); } 
  float getY() const { return static_cast<float>(yPos); }

  Rectangle getCollisionRectangle() const {
    float scaledWidth = frameWidth * 0.05f; 
    float scaledHeight = frameHeight * 0.05f;
    return { static_cast<float>(xPos), static_cast<float>(yPos),
             scaledWidth, scaledHeight };
  }

  // Getter for health
  int getHealth() const {
      return health;
  }

  // Function to reduce health when hit
  void takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
      // Handle player death
      health = 0;
      // Add logic for player death, respawn, etc.
    }
  }

  int score = 0;
  void updateScore() { score++; }
  void reset();
  const int initialHealth = 100;
  float startingX = 1000.0f;
  float startingY = 1000.0f;


};

#endif