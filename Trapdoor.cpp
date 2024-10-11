// Trapdoor.cpp
#include "Trapdoor.h"

// Constructor implementation
Trapdoor::Trapdoor(int x, int y, Texture2D texture) 
    : position({static_cast<float>(x), static_cast<float>(y)}), isActive(true), texture(texture) {
    // Ensure other initialization as needed
}
// Update method implementation
void Trapdoor::update(float deltaTime) {
    // Update logic for the trapdoor (if any)
}

// Draw method implementation
void Trapdoor::draw() {
    if (isActive) {
        DrawTexture(texture, position.x, position.y, WHITE); // Draw open trapdoor
    } else {
        // Draw closed trapdoor or an alternative
    }
}

// Trigger method implementation
void Trapdoor::trigger() {
    isActive = !isActive; // Toggle the state of the trapdoor
}

void Trapdoor::hit() {
    isActive = false; // Set active to false when hit
}
