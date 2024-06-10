#ifndef MENU_HPP
#define MENU_HPP
#include <string> 
using namespace std;

class GameManager;                                                  // Forward declaration of GameManager class
class UI;                                                           // Forward declaration of UI class     

enum GameState {                                                    // Enum class for the game state            
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

class Menu                                                          // Menu class         
{
    public:
        Menu();                                                     // Constructor    
        ~Menu();                                                    // Destructor 
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

};
#endif // MENU_HPP