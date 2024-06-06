#ifndef MENU_HPP
#define MENU_HPP

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

        GameState currentState;
        bool isGameStarted=false;

    private:
        UI* ui;


};
#endif // MENU_HPP