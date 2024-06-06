#include "leaderboard.hpp"

Leaderboard::Leaderboard(std::string username, int score) {
    this->username = username;
    this->score = score;
}

Leaderboard::~Leaderboard() {}

std::string Leaderboard::getUsername() const {
    return username;
}

int Leaderboard::getScore() const {
    return score;
}

void Leaderboard::saveScoreToJSON() {
    std::ofstream leaderboardFile;
    leaderboardFile.open("leaderboard.json", std::ios::app);
    leaderboardFile << "{\n";
    leaderboardFile << "  \"username\": \"" << username << "\",\n";
    leaderboardFile << "  \"score\": " << score << "\n";
    leaderboardFile << "}\n";
    leaderboardFile.close();
}