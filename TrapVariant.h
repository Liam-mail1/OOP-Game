// TrapVariant.h
#ifndef TRAPVARIANT_H
#define TRAPVARIANT_H

#include "TrapBase.h"
#include "raylib.h"

class TrapVariant : public TrapBase {
private:
    float xPos;
    float yPos;
    bool isExploded; // Add this member variable
    bool destroyed; // New variable to track if the barrel is destroyed
    float explosionTime; // Duration to display the explosion
    float explosionTimer; // Timer to manage explosion duration
    Texture2D barrelTexture; // Texture for barrel
    Texture2D explosionTexture; // Texture for explosion

public:
    TrapVariant();
    void explode(); // Declare the explode method
    TrapVariant(float x, float y);
    void draw();
    void update();
    void handleCollision(); // Handle player collision with the barrel
    bool isDestroyed() const { return destroyed; } // Getter for destroyed
    Rectangle getRectangle() const;

    // Declare trigger as a virtual function
    virtual void trigger() = 0;  // Pure virtual function
    virtual void update(float deltaTime) = 0;


    // Define a structure for the Barrel
    struct Barrel {
        float x;
        float y;
        Rectangle rect;        // Position and size
        bool isVisible;        // Visibility status
        bool isExploded;       // Explosion status
        float explosionTimer;  // Timer for explosion visibility

        // Constructor
        Barrel(float x, float y) 
            : rect{x, y, 64, 64},  // Set size as needed
              isVisible(true), 
              isExploded(false), 
              explosionTimer(0.0f) {}
    };
};

#endif
