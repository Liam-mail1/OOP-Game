// TrapVariant.cpp
#include "TrapVariant.h"

TrapVariant::TrapVariant() {}

TrapVariant::TrapVariant(float x, float y) : TrapBase(x, y), destroyed(false), explosionTime(1.0f), explosionTimer(0.0f) {
    barrelTexture = LoadTexture("barrel.png");
    explosionTexture = LoadTexture("explosion.png");
}

void TrapVariant::draw() {
    if (destroyed) {
        // Draw the explosion texture if it is still within the explosion time
        if (explosionTimer > 0) {

            DrawTexture(explosionTexture, xPos, yPos, WHITE); // Draw explosion at barrel position
        }
    } else {
        // Draw the barrel only if it hasn't been destroyed
        DrawTexture(barrelTexture, xPos, yPos, WHITE);
    }
}


void TrapVariant::update() {
    if (destroyed) {
        explosionTimer -= GetFrameTime(); // Decrease timer based on frame time
        if (explosionTimer <= 0) {
            // Stop showing the explosion and set to destroyed state
            destroyed = true;
        }
    }
}

void TrapVariant::handleCollision() {
    destroyed = true; // Set the barrel as destroyed when it is hit
    explosionTimer = explosionTime; // Reset the explosion timer
}

void TrapVariant::explode() {
    isExploded = true; // Change the state to exploded
    explosionTimer = 0.0f; // Reset the timer if necessary
}


