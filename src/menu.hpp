#ifndef MENU_HPP
#define MENU_HPP
#include <string> // Add this line to include the <string> header file
using namespace std;

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
        void resetGameManager(string difficulty);
        void resetUI();
        GameState currentState;
        bool isGameStarted=false;
        GameManager* gameManager;
        UI* ui;
        void setFinalScore(int score);
        int getFinalScore();

    private:
        int finalScore;


};
#endif // MENU_HPP