#ifndef UI_HPP
#define UI_HPP

#include <raylib.h>
#include "button.hpp"
#include "map.hpp"
#include "observer.hpp"
#include "leaderboard.hpp"

class Menu;                                                             // Forward declaration of the Menu class

class UI : public Subject {                                             // UI class inherits from Subject       
public:                                                                 // Public members
    UI();                                                               // Constructor     
    ~UI();                                                              // Destructor     
    void drawGame();
    void drawMainMenu();
    void drawDifficultyMenu();
    void drawLeaderboard();
    void drawCredits();
    void drawOptions();
    void drawGameOver(int finalScore);
    void drawGameWin(int finalScore);

    void drawGameButtons(int money);
    void updateButtons(int money);
    void loadTextures();
    void loadButtons();
    bool isPlacingTower() const;
    string getSelectedTowerType() const;
    void resetPlacingTower();
    float getSelectedTowerFireRate() const;
    int getSelectedTowerCost() const;
    void drawInputTextBox();

    Button* buttonTower1;
    Button* buttonTower2;
    Button* buttonTower3;
    Button* buttonStart;
    Button* buttonLeaderboard;
    Button* buttonCredits;
    Button* buttonOptions;
    Button* buttonQuit;
    Button* buttonBackLeaderboard;
    Button* buttonBackCredits;
    Button* buttonBackOptions;
    Button* buttonEasy;
    Button* buttonMedium;
    Button* buttonHard;
    Button* buttonBackDifficulty;
    Button* buttonBackGameOver;
    Button* buttonBackGameWin;
    Button* buttonCloseGame;

    Menu* menu;
    Leaderboard leaderboard;

private:                                                                // Private members      
    Texture2D buttonTexture1;
    Texture2D buttonHoverTexture1;
    Texture2D buttonTexture2;
    Texture2D buttonHoverTexture2;
    Texture2D buttonTexture3;
    Texture2D buttonHoverTexture3;
    Texture2D backgroundTexture;
    Texture2D backgroundCreditsTexture;
    Texture2D backgroundLeaderboardTexture;
    Texture2D backgroundDifficultyTexture;
    Texture2D basicTowerTexture;
    Texture2D basicTowerHoverTexture;
    Texture2D normalTowerTexture;
    Texture2D normalTowerHoverTexture;
    Texture2D slowTowerTexture;
    Texture2D slowTowerHoverTexture;


    Image backgroundCredits;
    Image backgroundImage;
    Image backgroundLeaderboard;
    Image backgroundDifficulty;

    bool buttonTower1Active;
    bool buttonTower2Active;
    bool buttonTower3Active;

    bool placingTower;
    string selectedTowerType;
    float selectedTowerFireRate;
    bool towerShopClicked;
    int selectedTowerCost;

    std::string username;
};

#endif // UI_HPP
