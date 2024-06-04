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
        OPTIONS,
        GAME_OVER,
        QUIT
    };

    MenuState currentState = MENU;

    void loadTextures();
    void loadFont();
    void update();
    void draw();
    bool isGameStarted();
    void setGameState(MenuState state);
    void drawGameOverMenu();

private:
    Texture2D buttonTexture;
    Texture2D buttonHoverTexture;
    Texture2D logoTexture;
    Texture2D backgroundTexture;
    Font customFont;
    Music backgroundMusic; // New variable for background music
    bool isMusicOn = true; // New variable to track music state

    Button* startButton;
    Button* leaderboardButton;
    Button* creditsButton;
    Button* optionsButton;
    Button* quitButton;
    Button* backButton;
    Button* musicToggleButton; // New button for toggling music
};

#endif // MENU_HPP
