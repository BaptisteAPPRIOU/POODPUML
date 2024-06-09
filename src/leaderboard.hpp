#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <fstream>
#include <iostream>

class Leaderboard
{
public:
    Leaderboard();
    ~Leaderboard();

    void setScore(int score);
    void setUsername(const std::string& username);

    void saveToTxt() const;
    void reorderLeaderboard();
    static void displayLeaderboard();
    std::vector<std::pair<std::string, int>> loadFromTxt() const;

private:
    std::string username;
    int score;
};

#endif // LEADERBOARD_HPP
