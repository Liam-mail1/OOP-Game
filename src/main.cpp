#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Projectile.h"
#include "Tank.h"
#include "TrapBase.h"
#include "TrapVariant.h"
#include "WallSet.h"
#include "raylib.h"
#include "Trapdoor.h"
#include "MainMenu.h"
#include "AutoSave.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>


int main()
{
  const int TILE_SIZE = 128; // Each tile size in pixels
  const int windowWidth = 1920;
  const int windowHeight = 1080;
  InitWindow(windowWidth, windowHeight, "Tank Trouble");
  Player1 player1;
  Player2 player2;

  InitMainMenu();
  GameState currentState = MENU;

  // Load textures for the tiles and the barrel
  Texture2D grassTile = LoadTexture("assets/ground.png");
  Texture2D sandTile = LoadTexture("assets/sand.png");
  Texture2D barrelTexture = LoadTexture("assets/barrel.png");       // Add barrel texture
  Texture2D explosionTexture = LoadTexture("assets/explosion.png"); // Add explosion texture
  Texture2D trapdoorTexture = LoadTexture("assets/trapdoor.png");   // Load the trapdoor texture

  // Calculate rows and columns based on window size
  const int cols =
      (windowWidth + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up
  const int rows =
      (windowHeight + TILE_SIZE - 1) / TILE_SIZE; // Ensures rounding up

  // Initialize the map with a unique pattern
  int map[rows][cols];                       // Adjust the second dimension based on the maximum number of columns
  srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
  for (int y = 0; y < rows; ++y)
  {
    for (int x = 0; x < cols; ++x)
    {
      map[y][x] = (rand() % 2); // Randomly assign either grass (0) or sand (1)
    }
  }
  // Define barrel position and dimensions
  Rectangle barrel1Rect = {800, 600, 64, 64};  // First barrel
  Rectangle barrel2Rect = {1000, 200, 64, 64}; // Second barrel
  Rectangle barrel3Rect = {300, 400, 64, 64};  // Third barrel
  Rectangle barrel4Rect = {1500, 800, 64, 64}; // Fourth barrel
  Rectangle barrel5Rect = {600, 150, 64, 64};  // Fifth barrel
  Rectangle barrel6Rect = {200, 900, 64, 64};  // Sixth barrel
  Rectangle barrel7Rect = {1200, 500, 64, 64}; // Seventh barrel
  bool isBarrel1Exploded = false;
  bool isBarrel2Exploded = false;
  bool isBarrel3Exploded = false;
  bool isBarrel4Exploded = false;
  bool isBarrel5Exploded = false;
  bool isBarrel6Exploded = false;
  bool isBarrel7Exploded = false;

  float explosion1Timer = 0.0f;
  float explosion2Timer = 0.0f;
  float explosion3Timer = 0.0f;
  float explosion4Timer = 0.0f;
  float explosion5Timer = 0.0f;
  float explosion6Timer = 0.0f;
  float explosion7Timer = 0.0f;


  bool isBarrel1Visible = true;
  bool isBarrel2Visible = true;
  bool isBarrel3Visible = true;
  bool isBarrel4Visible = true;
  bool isBarrel5Visible = true;
  bool isBarrel6Visible = true; 
  bool isBarrel7Visible = true;

  // Create a trapdoor instance
  Trapdoor trapdoor1(500, 850, trapdoorTexture); // Location 1 BOTTOM ROW
  Trapdoor trapdoor2(400, 300, trapdoorTexture); // Location 2 MOST LEFT
  Trapdoor trapdoor3(700, 550, trapdoorTexture); // Location 3 MIDDLE 
  Trapdoor trapdoor4(1200, 200, trapdoorTexture); // Location 4 UPPER RIGHT
  Trapdoor trapdoor5(950, 800, trapdoorTexture); // Location 5 BOTTOM RIGHT

  WallSet WallSet(1);

  SetTargetFPS(60); // Set target FPS

  // Test initial health
  if (player1.getHealth() == 100)
  {
    std::cout << "Initial health test passed." << std::endl;
  }
  else
  {
    std::cout << "Initial health test failed." << std::endl;
  }

  // Simulate movement input
  player1.moveInput();

  // Test initial health
  if (player2.getHealth() == 100)
  {
    std::cout << "Initial health test passed." << std::endl;
  }
  else
  {
    std::cout << "Initial health test failed." << std::endl;
  }

  // Simulate movement input
  player2.moveInput();

  // Test trap spawning at a specific position
  if (trapdoor1.isActive)
  {
    std::cout << "Trapdoor spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Trapdoor spawn test failed." << std::endl;
  }
  if (trapdoor2.isActive)
  {
    std::cout << "Trapdoor spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Trapdoor spawn test failed." << std::endl;
  }
  if (trapdoor3.isActive)
  {
    std::cout << "Trapdoor spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Trapdoor spawn test failed." << std::endl;
  }
  if (trapdoor4.isActive)
  {
    std::cout << "Trapdoor spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Trapdoor spawn test failed." << std::endl;
  } 
  if (trapdoor5.isActive)
  {
    std::cout << "Trapdoor spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Trapdoor spawn test failed." << std::endl;
  }

  // Test barrel spawning at a specific position
  if (isBarrel1Visible)
  {
    std::cout << "Barrel 1 spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Barrel 1 spawn test failed." << std::endl;
  }

  if (isBarrel2Visible)
  {
    std::cout << "Barrel 2 spawn test passed." << std::endl;
  }
  else
  {
    std::cout << "Barrel 2 spawn test failed." << std::endl;
  }
  std::cout << "All tests executed." << std::endl;


  extern bool isNewGame;
  bool gameStarted = false;

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (currentState == MENU)
    {
      mainMenu(currentState);
    }
    else if (currentState == PLAYING){
      if (!gameStarted){ //only reloadgame at start
        if (isNewGame) {
          player1.score = 0;
          player2.score = 0;
          } else { 
            LoadScores(player1.score, player2.score);
            }
            gameStarted = true;
      }
    }
      // Draw tiles based on the predefined map
      for (int y = 0; y < rows; ++y)
      {
        for (int x = 0; x < cols; ++x)
        {
          if (map[y][x] == 0)
          {
            DrawTexture(grassTile, x * TILE_SIZE, y * TILE_SIZE, WHITE);
          }
          else
          {
            DrawTexture(sandTile, x * TILE_SIZE, y * TILE_SIZE, WHITE);
          }
        }
      }

      WallSet.draw(1);
      

      player1.fire(); // this command spawn a new projectile under player1

      // update(position) and draw all the projectile under player 1
      for (size_t i = 0; i < player1.projectiles.size(); i++)
      {
        auto &Projectile = player1.projectiles[i]; // Reference to the current projectile

        Projectile.upFrame(); // Update the projectile frame
        Projectile.update();  // Update the projectile position
        Projectile.draw();    // Draw the projectile

        // Check for collisions with walls
        for (int j = 0; j < WallSet.getWallcount(); j++)
        {
          if (CheckCollisionCircleRec(Vector2{(float)Projectile.getX(), (float)Projectile.getY()},
                                      Projectile.getRad(),
                                      Rectangle{
                                          (float)WallSet.getX(WallSet.getNum(), j),
                                          (float)WallSet.getY(WallSet.getNum(), j),
                                          (float)WallSet.getWidth(WallSet.getNum(), j),
                                          (float)WallSet.getLength(WallSet.getNum(), j),
                                      }))
          {
            // Reflect the projectile based on wall direction
            if (WallSet.getWallDIr(WallSet.getNum(), j) == 1 && Projectile.calcFrame())
            {
              Projectile.reflectY(); // Reflect on Y-axis
            }
            else if (Projectile.calcFrame())
            {
              Projectile.reflectX(); // Reflect on X-axis
            }
          }
        }

        // Check for collision with Player 2
        if (CheckCollisionRecs(Projectile.getCollisionRectangle(), player2.getCollisionRectangle()))
        {
          player2.takeDamage(30);      // Deal damage to Player 2
          Projectile.setTimeOut(true); // Mark projectile for destruction
        }

        // // Draw the collision rectangle for debugging purposes
        // Rectangle collisionBox = Projectile.getCollisionRectangle();
        // DrawRectangleLines(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, RED); // Draw the collision box in red
      }

      // Remove expired projectiles
      player1.projectiles.erase(std::remove_if(player1.projectiles.begin(), player1.projectiles.end(),
                                               [](const Projectile &p)
                                               { return p.isExpired(); }),
                                player1.projectiles.end());

      // same as about but for player 2
      player2.fire();
      for (size_t i = 0; i < player2.projectiles.size(); i++)
      {
        auto &Projectile = player2.projectiles[i]; // Reference to the current projectile

        Projectile.upFrame(); // Update the projectile frame
        Projectile.update();  // Update the projectile position
        Projectile.draw();    // Draw the projectile

        // Check for collisions with walls
        for (int j = 0; j < WallSet.getWallcount(); j++)
        {
          if (CheckCollisionCircleRec(Vector2{(float)Projectile.getX(), (float)Projectile.getY()},
                                      Projectile.getRad(),
                                      Rectangle{
                                          (float)WallSet.getX(WallSet.getNum(), j),
                                          (float)WallSet.getY(WallSet.getNum(), j),
                                          (float)WallSet.getWidth(WallSet.getNum(), j),
                                          (float)WallSet.getLength(WallSet.getNum(), j),
                                      }))
          {
            // Reflect the projectile based on wall direction
            if (WallSet.getWallDIr(WallSet.getNum(), j) == 1 && Projectile.calcFrame())
            {
              Projectile.reflectY(); // Reflect on Y-axis
            }
            else if (Projectile.calcFrame())
            {
              Projectile.reflectX(); // Reflect on X-axis
            }
          }
        }

        // Check for collision with Player 1
        if (CheckCollisionRecs(Projectile.getCollisionRectangle(), player1.getCollisionRectangle()))
        {
          player1.takeDamage(30);      // Deal damage to Player 1
          Projectile.setTimeOut(true); // Mark projectile for destruction
        }

        // // Draw the collision rectangle for debugging purposes
        // Rectangle collisionBox = Projectile.getCollisionRectangle();
        // Rectangle playerBox = player1.getCollisionRectangle();
        // DrawRectangleLines(collisionBox.x, collisionBox.y, collisionBox.width, collisionBox.height, RED); // Draw the collision box in red
        // DrawRectangleLines(playerBox.x, playerBox.y, playerBox.width, playerBox.height, PURPLE);          // Draw the collision box in red
      }

      // Remove expired projectiles
      player2.projectiles.erase(std::remove_if(player2.projectiles.begin(), player2.projectiles.end(),
                                               [](const Projectile &p)
                                               { return p.isExpired(); }),
                                player2.projectiles.end());

      // Draw first barrel
      if (isBarrel1Visible)
      {
        if (!isBarrel1Exploded)
        {
          DrawTexture(barrelTexture, barrel1Rect.x, barrel1Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel1Rect.x, barrel1Rect.y, WHITE);
          explosion1Timer += GetFrameTime();
          if (explosion1Timer >= 1.0f)
          {
            isBarrel1Visible = false;
            explosion1Timer = 0.0f;
          }
        }
      }
      // Draw second barrel
      if (isBarrel2Visible)
      {
        if (!isBarrel2Exploded)
        {
          DrawTexture(barrelTexture, barrel2Rect.x, barrel2Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel2Rect.x, barrel2Rect.y, WHITE);
          explosion2Timer += GetFrameTime();
          if (explosion2Timer >= 1.0f)
          {
            isBarrel2Visible = false;
            explosion2Timer = 0.0f;
          }
        }
      }

      // Draw third barrel
      if (isBarrel3Visible)
      {
        if (!isBarrel3Exploded)
        {
          DrawTexture(barrelTexture, barrel3Rect.x, barrel3Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel3Rect.x, barrel3Rect.y, WHITE);
          explosion3Timer += GetFrameTime();
          if (explosion3Timer >= 1.0f)
          {
            isBarrel3Visible = false;
            explosion3Timer = 0.0f;
          }
        }
      }

      // Draw fourth barrel
      if (isBarrel4Visible)
      {
        if (!isBarrel4Exploded)
        {
          DrawTexture(barrelTexture, barrel4Rect.x, barrel4Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel4Rect.x, barrel4Rect.y, WHITE);
          explosion4Timer += GetFrameTime();
          if (explosion4Timer >= 1.0f)
          {
            isBarrel4Visible = false;
            explosion4Timer = 0.0f;
          }
        }
      }


      // Draw fifth barrel
      if (isBarrel5Visible)
      {
        if (!isBarrel5Exploded)
        {
          DrawTexture(barrelTexture, barrel5Rect.x, barrel5Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel5Rect.x, barrel5Rect.y, WHITE);
          explosion5Timer += GetFrameTime();
          if (explosion5Timer >= 1.0f)
          {
            isBarrel5Visible = false;
            explosion5Timer = 0.0f;
          }
        }
      }
      
      // Draw sixth barrel
      if (isBarrel6Visible)
      {
        if (!isBarrel6Exploded)
        {
          DrawTexture(barrelTexture, barrel6Rect.x, barrel6Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel6Rect.x, barrel6Rect.y, WHITE);
          explosion6Timer += GetFrameTime();
          if (explosion6Timer >= 1.0f)
          {
            isBarrel6Visible = false;
            explosion6Timer = 0.0f;
          }
        }
      }

      // Draw seventh barrel
      if (isBarrel7Visible)
      {
        if (!isBarrel7Exploded)
        {
          DrawTexture(barrelTexture, barrel7Rect.x, barrel7Rect.y, WHITE);
        }
        else
        {
          DrawTexture(explosionTexture, barrel7Rect.x, barrel7Rect.y, WHITE);
          explosion7Timer += GetFrameTime();
          if (explosion7Timer >= 1.0f)
          {
            isBarrel7Visible = false;
            explosion7Timer = 0.0f;
          }
        }
      
      // Check for collision between player 1 and barrel
      Rectangle player1Rect = {
          player1.getX(), player1.getY(),
          player1.getFrameWidth() * 0.05f, // Use the getter to get width
          player1.getFrameHeight() * 0.05f // Use the getter to get height
      };

      if (CheckCollisionRecs(player1Rect, {trapdoor1.position.x, trapdoor1.position.y, 64, 64}) && trapdoor1.isActive)
      {
        player1.takeDamage(60);
        trapdoor1.hit(); // Call hit function when player 1 hits the trapdoor
      }
      if (CheckCollisionRecs(player1Rect, {trapdoor2.position.x, trapdoor2.position.y, 64, 64}) && trapdoor2.isActive)
      {
        player1.takeDamage(60);
        trapdoor2.hit(); // Call hit function when player 1 hits the trapdoor
      }
      if (CheckCollisionRecs(player1Rect, {trapdoor3.position.x, trapdoor3.position.y, 64, 64}) && trapdoor3.isActive)
      {
        player1.takeDamage(60);
        trapdoor3.hit(); // Call hit function when player 1 hits the trapdoor
      }
      if (CheckCollisionRecs(player1Rect, {trapdoor4.position.x, trapdoor4.position.y, 64, 64}) && trapdoor4.isActive)
      {
        player1.takeDamage(60);
        trapdoor4.hit(); // Call hit function when player 1 hits the trapdoor
      }
      if (CheckCollisionRecs(player1Rect, {trapdoor5.position.x, trapdoor5.position.y, 64, 64}) && trapdoor5.isActive)
      {
        player1.takeDamage(60);
        trapdoor5.hit(); // Call hit function when player 1 hits the trapdoor
      }

      if (!isBarrel1Exploded && CheckCollisionRecs(player1Rect, barrel1Rect))
      {
        player1.takeDamage(50);
        isBarrel1Exploded = true;
        explosion1Timer = 0.0f;
      }
      if (!isBarrel2Exploded && CheckCollisionRecs(player1Rect, barrel2Rect))
      {
        player1.takeDamage(50);
        isBarrel2Exploded = true;
        explosion2Timer = 0.0f;
      }
      if (!isBarrel3Exploded && CheckCollisionRecs(player1Rect, barrel3Rect))
      {
        player1.takeDamage(50);
        isBarrel3Exploded = true;
        explosion3Timer = 0.0f;
      }
      if (!isBarrel4Exploded && CheckCollisionRecs(player1Rect, barrel4Rect))
      {
        player1.takeDamage(50);
        isBarrel4Exploded = true;
        explosion4Timer = 0.0f;
      }
      if (!isBarrel5Exploded && CheckCollisionRecs(player1Rect, barrel5Rect))
      {
        player1.takeDamage(50);
        isBarrel5Exploded = true;
        explosion5Timer = 0.0f;
      }
      if (!isBarrel6Exploded && CheckCollisionRecs(player1Rect, barrel6Rect))
      {
        player1.takeDamage(50);
        isBarrel6Exploded = true;
        explosion6Timer = 0.0f;
      }
      if (!isBarrel7Exploded && CheckCollisionRecs(player1Rect, barrel7Rect))
      {
        player1.takeDamage(50);
        isBarrel7Exploded = true;
        explosion7Timer = 0.0f;
      }
      Rectangle player2Rect = {
          player2.getX(), player2.getY(),
          player2.getFrameWidth() * 0.05f, // Use the getter to get width
          player2.getFrameHeight() * 0.05f // Use the getter to get height
      };

      if (!isBarrel1Exploded && CheckCollisionRecs(player2Rect, barrel1Rect))
      {
        player2.takeDamage(50);
        isBarrel1Exploded = true;
        explosion1Timer = 0.0f;
      }
      if (!isBarrel2Exploded && CheckCollisionRecs(player2Rect, barrel2Rect))
      {
        player2.takeDamage(50);
        isBarrel2Exploded = true;
        explosion2Timer = 0.0f;
      }
      if (!isBarrel3Exploded && CheckCollisionRecs(player2Rect, barrel3Rect))
      {
        player2.takeDamage(50);
        isBarrel3Exploded = true;
        explosion3Timer = 0.0f;
      }
      if (!isBarrel4Exploded && CheckCollisionRecs(player2Rect, barrel4Rect))
      {
        player2.takeDamage(50);
        isBarrel4Exploded = true;
        explosion4Timer = 0.0f;
      }
      if (!isBarrel5Exploded && CheckCollisionRecs(player2Rect, barrel5Rect))
      {
        player2.takeDamage(50);
        isBarrel5Exploded = true;
        explosion5Timer = 0.0f;
      }
      if (!isBarrel6Exploded && CheckCollisionRecs(player2Rect, barrel6Rect))
      {
        player2.takeDamage(50);
        isBarrel6Exploded = true;
        explosion6Timer = 0.0f;
      }
      if (!isBarrel7Exploded && CheckCollisionRecs(player2Rect, barrel7Rect))
      {
        player2.takeDamage(50);
        isBarrel7Exploded = true;
        explosion7Timer = 0.0f;
      }

      if (CheckCollisionRecs(player2Rect, {trapdoor1.position.x, trapdoor1.position.y, 64, 64}) && trapdoor1.isActive)
      {
        player2.takeDamage(60);
        trapdoor1.hit(); // Call hit function when player 2 hits the trapdoor
      }
      if (CheckCollisionRecs(player2Rect, {trapdoor2.position.x, trapdoor2.position.y, 64, 64}) && trapdoor2.isActive)
      {
        player2.takeDamage(60);
        trapdoor2.hit(); // Call hit function when player 2 hits the trapdoor
      }
      if (CheckCollisionRecs(player2Rect, {trapdoor3.position.x, trapdoor3.position.y, 64, 64}) && trapdoor3.isActive)
      {
        player2.takeDamage(60);
        trapdoor3.hit(); // Call hit function when player 2 hits the trapdoor
      }
      if (CheckCollisionRecs(player2Rect, {trapdoor4.position.x, trapdoor4.position.y, 64, 64}) && trapdoor4.isActive)
      {
        player2.takeDamage(60);
        trapdoor4.hit(); // Call hit function when player 2 hits the trapdoor
      }
      if (CheckCollisionRecs(player2Rect, {trapdoor5.position.x, trapdoor5.position.y, 64, 64}) && trapdoor5.isActive)
      {
        player2.takeDamage(60);
        trapdoor5.hit(); // Call hit function when player 2 hits the trapdoor
      }
      
      // // Draw bounding boxes for debugging
      // DrawRectangleLines(player1Rect.x, player1Rect.y, player1Rect.width, player1Rect.height, RED);    // Player 1
      // DrawRectangleLines(player2Rect.x, player2Rect.y, player2Rect.width, player2Rect.height, BLUE);   // Player 2
      // DrawRectangleLines(barrel1Rect.x, barrel1Rect.y, barrel1Rect.width, barrel1Rect.height, GREEN);  // Barrel 1
      // DrawRectangleLines(barrel2Rect.x, barrel2Rect.y, barrel2Rect.width, barrel2Rect.height, YELLOW); // Barrel 2

      // After checking for damage and collisions
      if (player1.getHealth() <= 0)
      {
        player2.updateScore(); // Increment Player 2's score
        player1.reset();       // Reset Player 1 (reset health and position)
      }

      if (player2.getHealth() <= 0)
      {
        player1.updateScore(); // Increment Player 1's score
        player2.reset();       // Reset Player 2 (reset health and position)
      }

      if (player1.score >= 10 || player2.score >= 10)
      {
        // Set background color
        ClearBackground(DARKGRAY);

        // Determine which player wins
        const char *winnerText = (player1.score >= 10) ? "Player 1 Wins!" : "Player 2 Wins!";
        Color winColor = (player1.score >= 10) ? GREEN : BLUE;

        // Main game loop for the winning screen
        while (!WindowShouldClose())
        {
          float time = GetTime();

          // Draw background effects (pulsating circles)
          for (int i = 0; i < 10; i++)
          {
            DrawCircle(400, 300, 100 + i * 10, Fade(winColor, 0.2f)); // Pulsating effect
          }

          // Draw the winning message
          int textWidth = MeasureText(winnerText, 40);
          DrawText(winnerText, (GetScreenWidth() - textWidth) / 2, 200, 40, Fade(winColor, 1.0f - fmod(time, 2.0f))); // Center text

          // Instructions to restart or exit
          DrawText("Press ENTER to exit", 290, 300, 20, WHITE);

          // Begin drawing
          BeginDrawing();
          EndDrawing();

          // Check for exit condition
          if (IsKeyPressed(KEY_ENTER))
          {
            CloseWindow();
            break; // Exit the winning screen
          }
        }
      }

      // check for projectiles fired by player1, if timeout is ture then delete
      // that projectile
      for (auto it = player1.projectiles.begin();
           it != player1.projectiles.end();)
      {
        if (it->getTimeOut())
        {
          it = player1.projectiles.erase(it);
        }
        else
        {
          ++it;
        }
      }
      // same as above but for player 2.
      for (auto it = player2.projectiles.begin();
           it != player2.projectiles.end();)
      {
        if (it->getTimeOut())
        {
          it = player2.projectiles.erase(it);
        }
        else
        {
          ++it;
        }
      }

      player1.moveInput();
      player1.draw();
      float healthPercentagePlayer1 = static_cast<float>(player1.getHealth()) / 100.0f; 
      DrawRectangle(1700, 10, 200, 20, RED);                                            // Background health bar
      DrawRectangle(1700, 10, 200 * healthPercentagePlayer1, 20, GREEN);                // Current health
      // Draw health text using sprintf
      char healthTextPlayer1[50];
      sprintf(healthTextPlayer1, "Player 1 Health: %d", player1.getHealth());
      DrawText(healthTextPlayer1, 1700, 40, 20, DARKGRAY);

      player2.moveInput();
      player2.draw();

      float healthPercentagePlayer2 = static_cast<float>(player2.getHealth()) / 100.0f; 
      DrawRectangle(10, 10, 200, 20, RED);                                              // Background health bar
      DrawRectangle(10, 10, 200 * healthPercentagePlayer2, 20, GREEN);                  // Current health
      // Draw health text using sprintf
      char healthTextPlayer2[50];
      sprintf(healthTextPlayer2, "Player 2 Health: %d", player2.getHealth());
      DrawText(healthTextPlayer2, 10, 40, 20, DARKGRAY);

      // Update trapdoor
      trapdoor1.update(GetFrameTime());
      trapdoor1.draw(); // Draw the trapdoor
      trapdoor2.update(GetFrameTime());
      trapdoor2.draw(); // Draw the trapdoor
      trapdoor3.update(GetFrameTime());
      trapdoor3.draw(); // Draw the trapdoor
      trapdoor4.update(GetFrameTime());
      trapdoor4.draw(); // Draw the trapdoor
      trapdoor5.update(GetFrameTime());
      trapdoor5.draw(); // Draw the trapdoor

      DrawText(TextFormat("Player 1 Score: %d", player1.score), 860, 10, 20, BLACK);
      DrawText(TextFormat("Player 2 Score: %d", player2.score), 860, 40, 20, BLACK);
    }
    else if (currentState == EXIT)
    {
      break;
    }
    EndDrawing();
  }

  // Unload textures
  UnloadTexture(grassTile);
  UnloadTexture(sandTile);
  UnloadTexture(barrelTexture);
  UnloadTexture(explosionTexture);
  UnloadTexture(trapdoorTexture);

  CloseWindow();

  return 0;
}