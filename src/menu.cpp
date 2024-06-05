#include "menu.hpp"
#include "ui.hpp"

Menu::Menu() {
    ui = nullptr;
    currentState = MAIN_MENU;
}

Menu::~Menu() {
    ui = nullptr;
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
            break;
        case GAME_OVER:
            ui->drawGameOver();
            break;
        case GAME_WIN:
            ui->drawGameWin();
            break;
        case QUIT:
            break;
            CloseWindow();
    }
}

void Menu::updateMenu() {
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
            // Add any game-specific update logic here
            break;
        case GAME_OVER:
            // Add game over update logic here
            break;
        case GAME_WIN:
            // Add game win update logic here
            break;
        case DIFFICULTY_MENU:
            if (ui->buttonBackDifficulty->isClicked(mousePoint)) {
                currentState = MAIN_MENU;
            } else if (ui->buttonEasy->isClicked(mousePoint)) {
                currentState = GAME;
            } else if (ui->buttonMedium->isClicked(mousePoint)) {
                currentState = GAME;
            } else if (ui->buttonHard->isClicked(mousePoint)) {
                currentState = GAME;
            break;
        case QUIT:
            CloseWindow();
            break;
        }
    }
}