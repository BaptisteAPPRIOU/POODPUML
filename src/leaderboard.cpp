#include "leaderboard.hpp"
#include <filesystem> // Include the filesystem header for path manipulation

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

void Leaderboard::displayLeaderboard()
{
    // Get the path to the src directory
    std::string srcPath = "src/";

    // Concatenate the path with the file name
    std::string filePath = srcPath + "leaderboard.txt";

    // Open the file using the full or relative path
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        int rank = 1;
        std::cout << "Leaderboard:\n";
        while (std::getline(file, line))
        {
            std::cout << rank << ". " << line << '\n';
            ++rank;
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to open leaderboard file for reading." << std::endl;
    }
}
