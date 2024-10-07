#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Projectile.h"
#include "Tank.h"
#include "raylib.h"

int main() {
  int windowHeight = 1080;
  int windowWidth = 1920;
  InitWindow(windowWidth, windowHeight, "Tank Trouble");
  Player1 player1;
  Player2 player2;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

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

    // check for input of both player 1 and 2, then draw them at the new
    // posiiton
    player1.moveInput();
    player1.draw();
    player2.moveInput();
    player2.draw();
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

  CloseWindow();
}
