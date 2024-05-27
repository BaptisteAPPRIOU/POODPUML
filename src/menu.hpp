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
    void loadFont();  // New method to load the font
    void update();
    void draw();
    bool isGameStarted();

private:
    Texture2D buttonTexture;
    Texture2D buttonHoverTexture;
    Texture2D logoTexture;
    Texture2D backgroundTexture;
    Font customFont; // New font variable

    Button* startButton;
    Button* leaderboardButton;
    Button* creditsButton;
    Button* optionsButton;
    Button* quitButton;
    Button* backButton;
};

#endif // MENU_HPP
