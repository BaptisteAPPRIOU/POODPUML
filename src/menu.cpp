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
    if(ui == nullptr) {
        return;
    }
    
    Vector2 mousePoint = GetMousePosition();  
    if (ui->buttonStart->isClicked(mousePoint)) {
        currentState = GAME;
        ui->drawGame();
    }
    else if (ui->buttonLeaderboard->isClicked(mousePoint)) {
        currentState = LEADERBOARD;
        ui->drawLeaderboard();
    }
    else if (ui->buttonCredits->isClicked(mousePoint)) {
        currentState = CREDITS;
        ui->drawCredits();
    }
    else if (ui->buttonOptions->isClicked(mousePoint)) {
        currentState = OPTIONS;
        ui->drawOptions();
    }
    else if (ui->buttonQuit->isClicked(mousePoint)) {
        currentState = QUIT;
    }
    else if (ui->buttonBackLeaderboard->isClicked(mousePoint)) {
        currentState = MAIN_MENU;
        ui->drawMainMenu();
    }
    else if (ui->buttonBackCredits->isClicked(mousePoint)) {
        currentState = MAIN_MENU;
        ui->drawMainMenu();
    }
    else if (ui->buttonBackOptions->isClicked(mousePoint)) {
        currentState = MAIN_MENU;
        ui->drawMainMenu();
    }
}