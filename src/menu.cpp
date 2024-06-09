#include "menu.hpp"
#include "gameManager.hpp"
#include "ui.hpp"
#include <iostream>

Menu::Menu() {
    ui = nullptr;
    gameManager = nullptr;
    currentState = MAIN_MENU;
    isGameStarted = false;
}

Menu::~Menu() {
    delete ui;
    delete gameManager;
}

void Menu::setGameState(GameState state) {
    currentState = state;
}

GameState Menu::getCurrentState() {
    return currentState;
}
void Menu::setUI(UI* ui) {
    this->ui = ui;
}

void Menu::setGameManager(GameManager* gameManager) {
    this->gameManager = gameManager;
}

void Menu::resetGameManager() {
    // CloseWindow();
    delete gameManager;
    gameManager = new GameManager();
}

void Menu::resetUI() {
    ui = new UI();
}

void Menu::drawMenu(){
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

void Menu::updateMenu() {
    getCurrentState();
    if (ui == nullptr) {
        return;
    }

    Vector2 mousePoint = GetMousePosition();

    switch (currentState) {
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
                resetGameManager();
                resetUI();
            }
            break;
        case GAME_WIN:
            if (ui->buttonBackGameWin->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
                isGameStarted = false;
                resetGameManager();
                resetUI();
            }

            break;
        case DIFFICULTY_MENU:
            if (ui->buttonBackDifficulty->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            } else if (ui->buttonEasy->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager();
                resetUI();
            } else if (ui->buttonMedium->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager();
                resetUI();
            } else if (ui->buttonHard->isClicked(mousePoint)) {
                currentState = GAME;
                resetGameManager();
                resetUI();
            break;
        case QUIT:
            CloseWindow();
            break;
        }
    }
}