#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Leaderboard                                                                   // Leaderboard class                            
{
public:                                                                             // Public members            
    Leaderboard();                                                                  // Constructor        
    ~Leaderboard();                                                                 // Destructor    

    void setScore(int score);
    void setUsername(const std::string& username);

    void saveToTxt() const;
    void reorderLeaderboard();
    std::vector<std::pair<std::string, int>> loadFromTxt() const;

private:                                                                            // Private members  
    std::string username;
    int score;
};

#endif // LEADERBOARD_HPP
