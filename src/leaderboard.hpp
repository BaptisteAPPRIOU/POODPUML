#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <fstream>

class Leaderboard
{
    public:
        Leaderboard(std::string username, int score);
        ~Leaderboard();

        std::string getUsername() const;
        int getScore() const;
        void saveScoreToJSON();
        
    private:
        std::string username;
        int score;
};

#endif // LEADERBOARD_HPP