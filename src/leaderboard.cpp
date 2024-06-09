#include "leaderboard.hpp"
#include <filesystem>
#include <vector>
#include <algorithm>
#include <sstream>

Leaderboard::Leaderboard() : score(0) {}

Leaderboard::~Leaderboard() {}

void Leaderboard::setScore(int score)
{
    this->score = score;
}

void Leaderboard::setUsername(const std::string& username)
{
    this->username = username;
}

void Leaderboard::saveToTxt() const
{
    // Get the path to the src directory
    std::string srcPath = "src/";

    // Concatenate the path with the file name
    std::string filePath = srcPath + "leaderboard.txt";

    // Open the file using the full or relative path
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open())
    {
        file << username << " " << score << std::endl;
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open leaderboard file for writing." << std::endl;
    }
}

void Leaderboard::reorderLeaderboard()
{
    // Read usernames and scores from the file
    std::vector<std::pair<std::string, int>> leaderboardData;
    std::string srcPath = "src/";
    std::string filePath = srcPath + "leaderboard.txt";
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string username;
            int score;
            if (iss >> username >> score)
            {
                leaderboardData.push_back({username, score});
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open leaderboard file for reading." << std::endl;
        return;
    }

    // Sort leaderboard data based on scores (in descending order)
    std::sort(leaderboardData.begin(), leaderboardData.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Write the sorted leaderboard data back to the file
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        for (const auto& entry : leaderboardData)
        {
            outFile << entry.first << " " << entry.second << std::endl;
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open leaderboard file for writing." << std::endl;
    }
}

std::vector<std::pair<std::string, int>> Leaderboard::loadFromTxt() const {
    std::vector<std::pair<std::string, int>> leaderboardData;

    // Read usernames and scores from the file
    std::string srcPath = "src/";
    std::string filePath = srcPath + "leaderboard.txt";
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username;
            int score;
            if (iss >> username >> score) {
                leaderboardData.push_back({username, score});
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open leaderboard file for reading." << std::endl;
    }

    return leaderboardData;
}
