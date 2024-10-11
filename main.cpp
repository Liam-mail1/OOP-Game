#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Projectile.h"
#include "Tank.h"
#include "TrapBase.h"
#include "TrapVariant.h"
#include "WallSet.h"
#include "raylib.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;
#include <iostream>

int main() {
  const int TILE_SIZE = 128; // Each tile size in pixels
  const int windowWidth = 1920;
  const int windowHeight = 1080;
  InitWindow(windowWidth, windowHeight, "Tank Trouble");
  Player1 player1;
  Player2 player2;

  // Load textures for the tiles and the barrel
  Texture2D grassTile = LoadTexture("ground.png");
  Texture2D sandTile = LoadTexture("sand.png");
  Texture2D barrelTexture = LoadTexture("barrel.png"); // Add barrel texture
  Texture2D explosionTexture =
      LoadTexture("explosion.png"); // Add explosion texture

  // Calculate rows and columns based on window size
  const int cols =
      (windowWidth + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up
  const int rows =
      (windowHeight + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up

  // Initialize the map with a unique pattern
  int map[rows][cols]; // Adjust the second dimension based on the maximum
                       // number of columns
  srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      map[y][x] = (rand() % 2); // Randomly assign either grass (0) or sand (1)
    }
  }
  // Define barrel position and dimensions
  Rectangle barrelRect = {800, 600, 64, 64}; // Adjust the dimensions as needed
  bool isExploded = false;     // To check if the barrel has exploded
  float explosionTimer = 0.0f; // Timer for explosion visibility
  bool isBarrelVisible = true; // To check if the barrel is still visible

  WallSet WallSet(1);

  SetTargetFPS(60); // Set target FPS

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw tiles based on the predefined map
    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < cols; ++x) {
        if (map[y][x] == 0) {
          DrawTexture(grassTile, x * TILE_SIZE, y * TILE_SIZE, WHITE);
        } else {
          DrawTexture(sandTile, x * TILE_SIZE, y * TILE_SIZE, WHITE);
        }
      }
    }

    WallSet.draw(1);

    player1.fire(); // this command spawn a new projectile under player1

    // update(position) and draw all the projectile under player 1
    for (auto &Projectile : player1.projectiles) {
      Projectile.upFrame();
      for (int i = 0; i < WallSet.getWallcount(); i++) {
        if (CheckCollisionCircleRec(
                Vector2{(float)Projectile.getX(), (float)Projectile.getY()},
                Projectile.getRad(),
                Rectangle{
                    (float)WallSet.getX(WallSet.getNum(), i),
                    (float)WallSet.getY(WallSet.getNum(), i),
                    (float)WallSet.getWidth(WallSet.getNum(), i),
                    (float)WallSet.getLength(WallSet.getNum(), i),
                })) {
          if (WallSet.getWallDIr(WallSet.getNum(), i) == 1 &&
              Projectile.calcFrame()) {
            Projectile.reflectY();
          } else if (Projectile.calcFrame()) {
            Projectile.relfectX();
          }
        }
      };

      Projectile.update();
      Projectile.draw();
    }

    // same as about but for player 2
    player2.fire();
    for (auto &Projectile : player2.projectiles) {
      Projectile.upFrame();
      for (int i = 0; i < WallSet.getWallcount(); i++) {
        if (CheckCollisionCircleRec(
                Vector2{(float)Projectile.getX(), (float)Projectile.getY()},
                Projectile.getRad(),
                Rectangle{
                    (float)WallSet.getX(WallSet.getNum(), i),
                    (float)WallSet.getY(WallSet.getNum(), i),
                    (float)WallSet.getWidth(WallSet.getNum(), i),
                    (float)WallSet.getLength(WallSet.getNum(), i),
                })) {
          if (WallSet.getWallDIr(WallSet.getNum(), i) == 1 &&
              Projectile.calcFrame()) {
            Projectile.reflectY();
          } else if (Projectile.calcFrame()) {
            Projectile.relfectX();
          }
        }
      };

      Projectile.update();
      Projectile.draw();
    }
    // Draw the barrel
    if (isBarrelVisible) {
      if (!isExploded) { // Draw the barrel only if it hasn't exploded
        DrawTexture(barrelTexture, barrelRect.x, barrelRect.y, WHITE);
      } else { // If exploded, draw the explosion
        DrawTexture(explosionTexture, barrelRect.x, barrelRect.y, WHITE);
        explosionTimer += GetFrameTime(); // Update the timer
        if (explosionTimer >= 1.0f) {     // Hide the explosion after 1 second
          isBarrelVisible = false;        // Set barrel visibility to false
          explosionTimer = 0.0f;          // Reset the explosion timer
        }
      }
    }

    // Check for collision between player 1 and barrel
    Rectangle player1Rect = {
        player1.getX(), player1.getY(),
        player1.getFrameWidth(), // Use the getter to get width
        player1.getFrameHeight() // Use the getter to get height
    };

    if (!isExploded && CheckCollisionRecs(player1Rect, barrelRect)) {
      isExploded = true;     // Trigger explosion
      explosionTimer = 0.0f; // Reset the explosion timer
    }

    Rectangle player2Rect = {
        player2.getX(), player2.getY(),
        player2.getFrameWidth(), // Use the getter to get width
        player2.getFrameHeight() // Use the getter to get height
    };

    if (!isExploded && CheckCollisionRecs(player2Rect, barrelRect)) {
      isExploded = true;     // Trigger explosion
      explosionTimer = 0.0f; // Reset the explosion timer
    }

    // Process input and draw players

    // check for projectiles fired by player1, if timeout is ture then delete
    // that projectile
    for (auto it = player1.projectiles.begin();
         it != player1.projectiles.end();) {
      if (it->getTimeOut()) {
        it = player1.projectiles.erase(it);
      } else {
        ++it;
      }
    }
    // same as above but for player 2.
    for (auto it = player2.projectiles.begin();
         it != player2.projectiles.end();) {
      if (it->getTimeOut()) {
        it = player2.projectiles.erase(it);
      } else {
        ++it;
      }
    }

    player1.moveInput();
    player1.draw();
    player2.moveInput();
    player2.draw();

    EndDrawing();
  }

  // Unload textures
  UnloadTexture(grassTile);
  UnloadTexture(sandTile);
  UnloadTexture(barrelTexture);
  UnloadTexture(explosionTexture);
  CloseWindow();
}
