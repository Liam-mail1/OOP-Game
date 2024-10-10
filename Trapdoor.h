// Trapdoor.h
#ifndef TRAPDOOR_H
#define TRAPDOOR_H

#include "TrapVariant.h"
#include "raylib.h"

class Trapdoor : public TrapVariant {
public:
    Trapdoor(int x, int y, Texture2D texture); // Constructor declaration

    void update(float deltaTime) override; // Update method declaration
    void draw(); // Draw method declaration
    void trigger() override; // Trigger method declaration
    void hit();
    Vector2 position; // Position of the trapdoor
    bool isActive; // Track whether the trapdoor is open or closed

private:
    Texture2D texture; // Texture for the trapdoor
};

#endif // TRAPDOOR_H
