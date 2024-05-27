#include "menu.hpp"

Menu::Menu() {
    loadTextures();
    loadFont();  // Load the font
}

Menu::~Menu() {
    UnloadTexture(buttonTexture);
    UnloadTexture(buttonHoverTexture);
    UnloadTexture(logoTexture);
    UnloadTexture(backgroundTexture);
    UnloadFont(customFont);  // Unload the font
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
    backgroundTexture = LoadTexture("assets/images/background.png");

    startButton = new Button(760, 250, 400, 120, buttonTexture, buttonHoverTexture);
    leaderboardButton = new Button(760, 400, 400, 120, buttonTexture, buttonHoverTexture);
    creditsButton = new Button(760, 550, 400, 120, buttonTexture, buttonHoverTexture);
    optionsButton = new Button(760, 700, 400, 120, buttonTexture, buttonHoverTexture);
    quitButton = new Button(760, 850, 400, 120, buttonTexture, buttonHoverTexture);
    backButton = new Button(860, 850, 200, 80, buttonTexture, buttonHoverTexture);
}

void Menu::loadFont() {
    customFont = LoadFont("assets/fonts/AmericanTypewriterRegular.ttf");
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

        DrawTextEx(customFont, "Start", {startButton->bounds.x + 110, startButton->bounds.y + 40}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Leaderboard", {leaderboardButton->bounds.x + 55, leaderboardButton->bounds.y + 40}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Credits", {creditsButton->bounds.x + 90, creditsButton->bounds.y + 40}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Options", {optionsButton->bounds.x + 90, optionsButton->bounds.y + 40}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Quit", {quitButton->bounds.x + 110, quitButton->bounds.y + 40}, customFont.baseSize, 2, BLACK);
    } else if (currentState == LEADERBOARD) {
        backButton->update(GetMousePosition());
        DrawTextEx(customFont, "Leaderboard", {860, 100}, customFont.baseSize, 2,  WHITE);
        DrawTextEx(customFont, "Player1: 1000", {860, 200}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Player2: 800", {860, 250}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Player3: 600", {860, 300}, customFont.baseSize, 2, BLACK);
        DrawTextEx(customFont, "Back", {backButton->bounds.x + 110, backButton->bounds.y + 35}, customFont.baseSize, 2, BLACK);
    } else if (currentState == CREDITS) {
        backButton->update(GetMousePosition());
        DrawTextEx(customFont, "Credits", {860, 100}, customFont.baseSize, 2, WHITE);
        DrawTextEx(customFont, "Oussema FATNASSI", {860, 200}, customFont.baseSize, 2,  WHITE);
        DrawTextEx(customFont, "Baptiste APPRIOU", {860, 250}, customFont.baseSize, 2,  WHITE);
        DrawTextEx(customFont, "Ali ABAKAR ISSA", {860, 300}, customFont.baseSize, 2,  WHITE);
        DrawTextEx(customFont, "Back", {backButton->bounds.x + 110, backButton->bounds.y + 35}, customFont.baseSize, 2, BLACK);
    } else if (currentState == OPTIONS) {
        backButton->update(GetMousePosition());
        DrawTextEx(customFont, "Options", {860, 100}, customFont.baseSize, 2,  WHITE);
        // Additional options settings can be added here
        DrawTextEx(customFont, "Back", {backButton->bounds.x + 110, backButton->bounds.y + 35}, customFont.baseSize, 2, BLACK);
    }
}

bool Menu::isGameStarted() {
    return currentState == GAME;
}
