#include <iostream>
#include "Player1.h" // Make sure to include your Player1 header file
int main() {
    fprintf(stderr, "Running Player1 tests...\n");
    Player1 player1;
    // Test initial health for player1
    if (player1.getHealth() == 100) {
        std::cout << "Player1 initial health test passed." << std::endl;
    } else {
        std::cout << "Player1 initial health test failed." << std::endl;
    }
    
    return 0;
}
