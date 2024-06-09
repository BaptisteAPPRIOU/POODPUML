#ifndef MENU_HPP
#define MENU_HPP

class GameManager;
class UI;
enum GameState {
    MAIN_MENU,
    DIFFICULTY_MENU,
    LEADERBOARD,
    CREDITS,
    OPTIONS,
    GAME,
    GAME_OVER,
    GAME_WIN,
    QUIT
};

class Menu
{
    public:
        Menu();
        ~Menu();
        void setGameState(GameState state);
        void drawMenu();
        GameState getCurrentState();
        void setUI(UI* ui);
        void updateMenu();
        void setGameManager(GameManager* gameManager);
        void resetGameManager();
        void resetUI();
        GameState currentState;
        bool isGameStarted=false;
        GameManager* gameManager;
        UI* ui;

};
#endif // MENU_HPP