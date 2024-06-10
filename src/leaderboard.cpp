#include "leaderboard.hpp"
#include <filesystem>
#include <algorithm>
#include <sstream>

Leaderboard::Leaderboard() : score(0) {}                                                        // Constructor

Leaderboard::~Leaderboard() {}                                                                  // Destructor          

void Leaderboard::setScore(int score)                                                           // Function to set the score as score
{
    this->score = score;
}

void Leaderboard::setUsername(const std::string& username)                                      // Function to set the username as username           
{
    this->username = username;
}

void Leaderboard::saveToTxt() const                                                             // Function to save the username and score to the txt file
{
    std::string srcPath = "src/";                                                               // Concatenate the path with the file name
    std::string filePath = srcPath + "leaderboard.txt";

    std::ofstream file(filePath, std::ios::app);                                                // Open the file in append mode
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

void Leaderboard::reorderLeaderboard()                                                          // Function to reorder the leaderboard in descending order        
{
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
                leaderboardData.push_back({username, score});                                   // Push the username and score to the vector       
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open leaderboard file for reading." << std::endl;
        return;
    }

    std::sort(leaderboardData.begin(), leaderboardData.end(),                                   // Sort the leaderboard data in descending order      
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::ofstream outFile(filePath);                                                            // Open the file in write mode and write the sorted leaderboard data         
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

std::vector<std::pair<std::string, int>> Leaderboard::loadFromTxt() const {                     // Function to load the username and score from the txt file
    std::vector<std::pair<std::string, int>> leaderboardData;

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
