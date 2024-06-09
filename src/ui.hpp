#ifndef UI_HPP
#define UI_HPP

#include <raylib.h>
#include "button.hpp"
#include "map.hpp"
#include "observer.hpp"
#include "leaderboard.hpp"

class Menu;

class UI : public Subject {
public:
    UI();
    ~UI();
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
    Button* buttonTower4;
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
private:
    Texture2D buttonTexture1;
    Texture2D buttonHoverTexture1;
    Texture2D buttonTexture2;
    Texture2D buttonHoverTexture2;
    Texture2D buttonTexture3;
    Texture2D buttonHoverTexture3;
    Texture2D buttonTexture4;
    Texture2D buttonHoverTexture4;

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
