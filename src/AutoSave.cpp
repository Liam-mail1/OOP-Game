#include "AutoSave.h"
#include <fstream>

void SaveScores(int player1Score, int player2Score) {
    std::ofstream file("score.txt");
    if (file.is_open()) {
        file << player1Score << std::endl;
        file << player2Score << std::endl;
        file.close();
    }
}
  
void LoadScores(int &player1Score, int &player2Score) {
    std::ifstream file("score.txt");
    if (file.is_open()) {
        file >> player1Score;
        file >> player2Score;
        file.close();
    } else {
        player1Score = 0;
        player2Score = 0;
    }
}