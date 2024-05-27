#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>
#include "button.hpp"

class Menu {
public:
    Menu();
    ~Menu();

    enum MenuState {
        MENU,
        GAME,
        LEADERBOARD,
        CREDITS,
        OPTIONS
    };

    MenuState currentState = MENU;

    void loadTextures();
    void update();
    void draw();
    bool isGameStarted(); // New method to check if the game has started

private:
    Texture2D buttonTexture;
    Texture2D buttonHoverTexture;
    Texture2D logoTexture;
    Texture2D backgroundTexture;

    Button* startButton;
    Button* leaderboardButton;
    Button* creditsButton;
    Button* optionsButton;
    Button* quitButton;
    Button* backButton;
};

#endif // MENU_HPP
