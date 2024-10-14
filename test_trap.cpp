#include <iostream>
#include "Trapdoor.h" // Include your Trapdoor header file

void runTrapTests() {
    Texture2D trapdoorTexture = LoadTexture("trapdoor.png");
    Trapdoor trapdoor(400, 400, trapdoorTexture);; // Create a trapdoor instance
    bool isBarrel1Visible = true; // Simulate barrel visibility
    bool isBarrel2Visible = false; // Simulate barrel visibility

    // Test trap spawning at a specific position
    if (trapdoor.isActive) {
        std::cout << "Trapdoor spawn test passed." << std::endl;
    } else {
        std::cout << "Trapdoor spawn test failed." << std::endl;
    }

    // Test barrel spawning visibility
    if (isBarrel1Visible) {
        std::cout << "Barrel 1 spawn test passed." << std::endl;
    } else {
        std::cout << "Barrel 1 spawn test failed." << std::endl;
    }

    if (isBarrel2Visible) {
        std::cout << "Barrel 2 spawn test passed." << std::endl;
    } else {
        std::cout << "Barrel 2 spawn test failed." << std::endl;
    }

    std::cout << "All Trap tests executed." << std::endl;
}

int main() {
    runTrapTests();
    return 0;
}
