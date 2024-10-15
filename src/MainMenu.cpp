#include "MainMenu.h"
#include "raylib.h"
#include "AutoSave.h"
#include "Player1.h"
#include "Player2.h"

Texture2D backgroundTexture;

bool isNewGame = false;

extern Player1 player1;
extern Player2 player2;

void InitMainMenu() {
    backgroundTexture = LoadTexture("background.png");
}

void UnloadMainMenu() {
    UnloadTexture(backgroundTexture);
}

void mainMenu(GameState &currentState) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(backgroundTexture, 0, 0, WHITE);

    int lastScore1, lastScore2;
    LoadScores(lastScore1, lastScore2); 
    
    DrawText(TextFormat("Player1 last Score: %i", lastScore1), 200, 160, 40, BLACK);
    DrawText(TextFormat("Player2 last Score: %i", lastScore2), 200, 200, 40, BLACK);
    DrawText("MAIN MENU!", 200, 250, 65, YELLOW);
    DrawText("Press [ENTER] to start a new game", 400, 850, 50, BLUE);
    DrawText("Press any key to continue the game", 400, 900, 50, BLUE);
    DrawText("Press [ESC] to Exit", 400, 960, 50, RED);

    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = EXIT;
    }

    int keyPressed = GetKeyPressed();
    if (keyPressed != 0) {
        if (keyPressed == KEY_ENTER) {
            isNewGame = true;
        } else {
            isNewGame = false;
        }
        currentState = PLAYING;
    }

    EndDrawing();

}
