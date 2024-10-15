#include "MainMenu.h"
#include "raylib.h"

Texture2D backgroundTexture;

void InitMainMenu() {
    backgroundTexture = LoadTexture("assets/background.png");
}

void UnloadMainMenu() {
    UnloadTexture(backgroundTexture);
}

void mainMenu(GameState &currentState) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(backgroundTexture, 0, 0, WHITE);
    
    DrawText("MAIN MENU!", 200, 250, 65, YELLOW);
    DrawText("Press any key to Start", 400, 850, 50, BLUE);
    DrawText("Press [ESC] to Exit", 400, 950, 50, RED);

    if (GetKeyPressed() != 0) {
        currentState = PLAYING;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = EXIT;
    }

    EndDrawing();
}
