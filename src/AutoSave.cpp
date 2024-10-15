#include "AutoSave.h"
#include <fstream>
#include <iostream>

const std::string scoreFilePath = "score.txt"; // Use relative path, can change to absolute if necessary

void SaveScores(int player1Score, int player2Score) {
    std::ofstream file(scoreFilePath);
    if (file.is_open()) {
        file << player1Score << std::endl;
        file << player2Score << std::endl;
        file.close();
        std::cout << "Scores saved successfully!" << std::endl;  // Add feedback for successful save
    } else {
        std::cerr << "Error: Unable to open file for saving scores!" << std::endl;
    }
}

void LoadScores(int &player1Score, int &player2Score) {
    std::ifstream file(scoreFilePath);
    if (file.is_open()) {
        file >> player1Score;
        file >> player2Score;
        file.close();
        std::cout << "Scores loaded successfully!" << std::endl;  // Add feedback for successful load
    } else {
        player1Score = 0;
        player2Score = 0;
        std::cerr << "Error: Unable to open file for loading scores, initializing scores to 0." << std::endl;
    }
}