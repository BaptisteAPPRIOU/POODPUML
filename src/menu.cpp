#include "menu.hpp"

Menu::Menu() {
    loadTextures();
}

Menu::~Menu() {
    UnloadTexture(buttonTexture);
    UnloadTexture(buttonHoverTexture);
    UnloadTexture(logoTexture);
    UnloadTexture(backgroundTexture);
    delete startButton;
    delete leaderboardButton;
    delete creditsButton;
    delete optionsButton;
    delete quitButton;
    delete backButton;
}

void Menu::loadTextures() {
    buttonTexture = LoadTexture("assets/images/button.png");
    buttonHoverTexture = LoadTexture("assets/images/buttonHover.png");
    logoTexture = LoadTexture("assets/images/logo.png");
    backgroundTexture = LoadTexture("assets/images/backgr.png");

    startButton = new Button(760, 250, 400, 120, buttonTexture, buttonHoverTexture);
    leaderboardButton = new Button(760, 400, 400, 120, buttonTexture, buttonHoverTexture);
    creditsButton = new Button(760, 550, 400, 120, buttonTexture, buttonHoverTexture);
    optionsButton = new Button(760, 700, 400, 120, buttonTexture, buttonHoverTexture);
    quitButton = new Button(760, 850, 400, 120, buttonTexture, buttonHoverTexture);
    backButton = new Button(860, 850, 200, 80, buttonTexture, buttonHoverTexture);
}

void Menu::update() {
    Vector2 mousePoint = GetMousePosition();

    if (currentState == MENU) {
        if (startButton->isClicked(mousePoint)) {
            currentState = GAME;
        } else if (leaderboardButton->isClicked(mousePoint)) {
            currentState = LEADERBOARD;
        } else if (creditsButton->isClicked(mousePoint)) {
            currentState = CREDITS;
        } else if (optionsButton->isClicked(mousePoint)) {
            currentState = OPTIONS;
        } else if (quitButton->isClicked(mousePoint)) {
            CloseWindow();
        }
    } else if (currentState == LEADERBOARD || currentState == CREDITS || currentState == OPTIONS) {
        if (backButton->isClicked(mousePoint)) {
            currentState = MENU;
        }
    }
}

void Menu::draw() {
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawTexture(logoTexture, 50, 50, WHITE);

    if (currentState == MENU) {
        startButton->update(GetMousePosition());
        leaderboardButton->update(GetMousePosition());
        creditsButton->update(GetMousePosition());
        optionsButton->update(GetMousePosition());
        quitButton->update(GetMousePosition());

        DrawText("Start", startButton->bounds.x + 60, startButton->bounds.y + 40, 40, BLACK);
        DrawText("Leaderboard", leaderboardButton->bounds.x + 30, leaderboardButton->bounds.y + 40, 40, BLACK);
        DrawText("Credits", creditsButton->bounds.x + 60, creditsButton->bounds.y + 40, 40, BLACK);
        DrawText("Options", optionsButton->bounds.x + 60, optionsButton->bounds.y + 40, 40, BLACK);
        DrawText("Quit", quitButton->bounds.x + 70, quitButton->bounds.y + 40, 40, BLACK);
    } else if (currentState == LEADERBOARD) {
        backButton->update(GetMousePosition());
        DrawText("Leaderboard", 860, 100, 40, BLACK);
        DrawText("Player1: 1000", 860, 200, 30, BLACK);
        DrawText("Player2: 800", 860, 250, 30, BLACK);
        DrawText("Player3: 600", 860, 300, 30, BLACK);
        DrawText("Back", backButton->bounds.x + 60, backButton->bounds.y + 25, 30, BLACK);
    } else if (currentState == CREDITS) {
        backButton->update(GetMousePosition());
        DrawText("Credits", 860, 100, 40, BLACK);
        DrawText("Oussema FATNASSI", 860, 200, 30, BLACK);
        DrawText("Baptiste APPRIOU", 860, 250, 30, BLACK);
        DrawText("ALI Abakar Issa", 860, 300, 30, BLACK);
        DrawText("Back", backButton->bounds.x + 60, backButton->bounds.y + 25, 30, BLACK);
    } else if (currentState == OPTIONS) {
        backButton->update(GetMousePosition());
        DrawText("Options", 860, 100, 40, BLACK);
        // Additional options settings can be added here
        DrawText("Back", backButton->bounds.x + 60, backButton->bounds.y + 25, 30, BLACK);
    }
}

bool Menu::isGameStarted() {
    return currentState == GAME;
}
