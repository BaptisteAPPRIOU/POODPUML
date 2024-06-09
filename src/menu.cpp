#include "menu.hpp"
#include "gameManager.hpp"
#include "ui.hpp"
#include <iostream>
#include <string>
using namespace std;

Menu::Menu() {                                                                  // Constructor for the Menu class
    ui = nullptr;
    gameManager = nullptr;
    currentState = MAIN_MENU;
    isGameStarted = false;
}

Menu::~Menu() {                                                                 // Destructor for the Menu class
    delete ui;
    delete gameManager;
}

void Menu::setGameState(GameState state) {                                      // Set the game state     
    currentState = state;
}

GameState Menu::getCurrentState() {                                             // Get the current game state        
    return currentState;
}

void Menu::setUI(UI* ui) {                                                      // Set the UI of the menu     
    this->ui = ui;
}

void Menu::setGameManager(GameManager* gameManager) {                           // Set the game manager of the menu    
    this->gameManager = gameManager;
}

void Menu::resetGameManager(string difficulty) {                                // Reset the game manager   
    CloseWindow();
    delete gameManager;
    gameManager = new GameManager();
}

void Menu::resetUI() {                                                          // Reset the UI
    ui = new UI();
}

void Menu::drawMenu(){                                                          // Draw the menu based on the current game state
    if(ui == nullptr) {
        return;
    }
    switch (currentState) {
        case MAIN_MENU:
            ui->drawMainMenu();
            break;
        case DIFFICULTY_MENU:
            ui->drawDifficultyMenu();
            break;
        case LEADERBOARD:
            ui->drawLeaderboard();
            break;
        case CREDITS:
            ui->drawCredits();
            break;
        case OPTIONS:
            ui->drawOptions();
            break;
        case GAME:
            ui->drawGame();
            isGameStarted = true;
            break;
        case GAME_OVER:
            ui->drawGameOver(gameManager->getScore());
            break;
        case GAME_WIN:
            ui->drawGameWin(gameManager->getScore());
            break;
        case QUIT:
            break;
            CloseWindow();
    }
}

void Menu::updateMenu() {                                                       // Update the menu based on the current game state         
    getCurrentState();
    if (ui == nullptr) {
        return;
    }

    Vector2 mousePoint = GetMousePosition();

    switch (currentState) {                                                     // Switch statement to check the current game state
        case MAIN_MENU:
            if (ui->buttonStart->isClicked(mousePoint)) {
                currentState = DIFFICULTY_MENU;
            } else if (ui->buttonLeaderboard->isClicked(mousePoint)) {
                currentState = LEADERBOARD;
            } else if (ui->buttonCredits->isClicked(mousePoint)) {
                currentState = CREDITS;
            } else if (ui->buttonOptions->isClicked(mousePoint)) {
                currentState = OPTIONS;
            } else if (ui->buttonQuit->isClicked(mousePoint)) {
                currentState = QUIT;
            }
            break;
        case LEADERBOARD:
            if (ui->buttonBackLeaderboard->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            }
            break;
        case CREDITS:
            if (ui->buttonBackCredits->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            }
            break;
        case OPTIONS:
            if (ui->buttonBackOptions->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            }
            break;
        case GAME:
            if(ui->buttonCloseGame->isClicked(mousePoint)){
                currentState = MAIN_MENU;
                isGameStarted = false;
            }
            break;
        case GAME_OVER:
            if (ui->buttonBackGameOver->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
                isGameStarted = false;
                resetGameManager("easy");
                resetUI();
            }
            break;
        case GAME_WIN:
            if (ui->buttonBackGameWin->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
                isGameStarted = false;
                resetGameManager("easy");
                resetUI();
            }
            break;
        case DIFFICULTY_MENU:
            if (ui->buttonBackDifficulty->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            } else if (ui->buttonEasy->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager("easy");
                resetUI();
            } else if (ui->buttonMedium->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager("medium");
                resetUI();
            } else if (ui->buttonHard->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager("hard");
                resetUI();
            break;
        case QUIT:
            CloseWindow();
            break;
        }
    }
}