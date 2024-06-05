#ifndef UI_HPP
#define UI_HPP

#include <raylib.h>
#include "button.hpp"
#include "map.hpp"
#include "observer.hpp"

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
    void drawGameOver();
    void drawGameWin();

    void drawGameButtons(int money);
    void updateButtons(int money);
    void loadTextures();
    void loadButtons();
    bool isPlacingTower() const;
    string getSelectedTowerType() const;
    void resetPlacingTower();
    float getSelectedTowerFireRate() const;
    int getSelectedTowerCost() const;

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

    Menu* menu;
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
    bool buttonTower4Active;

    bool placingTower;
    string selectedTowerType;
    float selectedTowerFireRate;
    bool towerShopClicked;
    int selectedTowerCost;
};

#endif // UI_HPP
