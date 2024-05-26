#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>
#include "button.hpp"
#include "ui.hpp"

class Menu {
public:
    Menu();
    ~Menu();

    void update();
    void draw();

    enum MenuState { MAIN, LEADERBOARD, CREDITS, GAME, QUIT };
    MenuState currentState;

private:
    void drawMainMenu();
    void updateMainMenu();
    void drawLeaderboard();
    void updateLeaderboard();
    void drawCredits();
    void updateCredits();

    Texture2D background;
    Texture2D logo;
    Button* startButton;
    Button* leaderboardButton;
    Button* creditsButton;
    Button* optionsButton;
    Button* quitButton;
    Button* backButton;
    Texture2D buttonTexture;
    Texture2D buttonHoverTexture;

    UI* ui;
};

#endif // MENU_HPP
