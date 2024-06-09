#include "leaderboard.hpp"

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
    std::ofstream file("leaderboard.txt", std::ios::app);
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
    std::ifstream file("leaderboard.txt");
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
