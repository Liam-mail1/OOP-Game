#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

extern bool isNewGame; 
 
enum GameState {
    MENU,
    PLAYING,
    EXIT
};

void mainMenu(GameState &currentState);
void InitMainMenu();
void UnloadMainMenu();

#endif
