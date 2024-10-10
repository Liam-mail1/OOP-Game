#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Projectile.h"
#include "Tank.h"
#include "raylib.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "TrapBase.h"
#include "TrapVariant.h"
#include "Trapdoor.h" 
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
    Texture2D explosionTexture = LoadTexture("explosion.png"); // Add explosion texture
    Texture2D trapdoorTexture = LoadTexture("trapdoor.png"); // Load the trapdoor texture


    // Calculate rows and columns based on window size
    const int cols = (windowWidth + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up
    const int rows = (windowHeight + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up

    // Initialize the map with a unique pattern
    int map[rows][cols]; // Adjust the second dimension based on the maximum number of columns
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            map[y][x] = (rand() % 2); // Randomly assign either grass (0) or sand (1)
        }
    }
    // Define barrel position and dimensions
    Rectangle barrel1Rect = {800, 600, 64, 64}; // Adjust the dimensions as needed
    Rectangle barrel2Rect = {1000, 200, 64, 64}; // Second barrel (different position)
    bool isBarrel1Exploded = false;
    bool isBarrel2Exploded = false;

    float explosion1Timer = 0.0f;
    float explosion2Timer = 0.0f;

    bool isBarrel1Visible = true;
    bool isBarrel2Visible = true;

    // Create a trapdoor instance
    Trapdoor trapdoor(400, 400, trapdoorTexture); // Set trapdoor position and texture

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

        player1.fire(); // this command spawn a new projectile under player1

        // update(position) and draw all the projectile under player 1
        for (auto &Projectile : player1.projectiles) {
        Projectile.update();
        Projectile.draw();
        }

         // same as about but for player 2
        player2.fire();
        for (auto &Projectile : player2.projectiles) {
        Projectile.update();
        Projectile.draw();
        }
        // Draw first barrel
        if (isBarrel1Visible) {
            if (!isBarrel1Exploded) {
                DrawTexture(barrelTexture, barrel1Rect.x, barrel1Rect.y, WHITE);
            } else {
                DrawTexture(explosionTexture, barrel1Rect.x, barrel1Rect.y, WHITE);
                explosion1Timer += GetFrameTime();
                if (explosion1Timer >= 1.0f) {
                    isBarrel1Visible = false;
                    explosion1Timer = 0.0f;
                }
            }
        }

         // Draw second barrel
        if (isBarrel2Visible) {
            if (!isBarrel2Exploded) {
                DrawTexture(barrelTexture, barrel2Rect.x, barrel2Rect.y, WHITE);
            } else {
                DrawTexture(explosionTexture, barrel2Rect.x, barrel2Rect.y, WHITE);
                explosion2Timer += GetFrameTime();
                if (explosion2Timer >= 1.0f) {
                    isBarrel2Visible = false;
                    explosion2Timer = 0.0f;
                }
            }
        }

      // Check for collision between player 1 and barrel
        Rectangle player1Rect = {
            player1.getX(),
            player1.getY(),
            player1.getFrameWidth() * 0.1f,  // Use the getter to get width
            player1.getFrameHeight() * 0.1f   // Use the getter to get height
        };

        if (CheckCollisionRecs(player1Rect, {trapdoor.position.x, trapdoor.position.y, 64, 64}) && trapdoor.isActive) {
        trapdoor.hit(); // Call hit function when player 1 hits the trapdoor
        }
        

        if (!isBarrel1Exploded && CheckCollisionRecs(player1Rect, barrel1Rect)) {
            isBarrel1Exploded = true;
            explosion1Timer = 0.0f;
        }

        if (!isBarrel2Exploded && CheckCollisionRecs(player1Rect, barrel2Rect)) {
            isBarrel2Exploded = true;
            explosion2Timer = 0.0f;
        }

        Rectangle player2Rect = {
            player2.getX(),
            player2.getY(),
            player2.getFrameWidth() * 0.1f,  // Use the getter to get width
            player2.getFrameHeight() * 0.1f   // Use the getter to get height
        };

         if (!isBarrel1Exploded && CheckCollisionRecs(player2Rect, barrel1Rect)) {
            isBarrel1Exploded = true;
            explosion1Timer = 0.0f;
        }

        if (!isBarrel2Exploded && CheckCollisionRecs(player2Rect, barrel2Rect)) {
            isBarrel2Exploded = true;
            explosion2Timer = 0.0f;
        }

        if (CheckCollisionRecs(player2Rect, {trapdoor.position.x, trapdoor.position.y, 64, 64}) && trapdoor.isActive) {
        trapdoor.hit(); // Call hit function when player 2 hits the trapdoor
        }

        // // Draw bounding boxes for debugging
        // DrawRectangleLines(player1Rect.x, player1Rect.y, player1Rect.width, player1Rect.height, RED); // Player 1
        // DrawRectangleLines(player2Rect.x, player2Rect.y, player2Rect.width, player2Rect.height, BLUE); // Player 2
        // DrawRectangleLines(barrel1Rect.x, barrel1Rect.y, barrel1Rect.width, barrel1Rect.height, GREEN); // Barrel 1
        // DrawRectangleLines(barrel2Rect.x, barrel2Rect.y, barrel2Rect.width, barrel2Rect.height, YELLOW); // Barrel 2


        // Process input and draw players
        
        player1.moveInput();
        player1.draw();
        player2.moveInput();
        player2.draw();

        // Update trapdoor
        trapdoor.update(GetFrameTime());
        trapdoor.draw(); // Draw the trapdoor

        EndDrawing();
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
        }

    // Unload textures
    UnloadTexture(grassTile);
    UnloadTexture(sandTile);
    UnloadTexture(barrelTexture);
    UnloadTexture(explosionTexture);
    UnloadTexture(trapdoorTexture); 
    CloseWindow();
}
