#include "menu.hpp"
#include <iostream>

Menu::Menu() {
    background = LoadTexture("assets/images/background.png");
    logo = LoadTexture("assets/images/logo.png");
    buttonTexture = LoadTexture("assets/images/button.png");
    buttonHoverTexture = LoadTexture("assets/images/buttonHover.png");

    
    float buttonWidth = 200;
    float buttonHeight = 50;
    float centerX = GetScreenWidth() / 2.0f - buttonWidth / 2.0f;

    startButton = new Button(centerX, 200, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);
    leaderboardButton = new Button(centerX, 300, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);
    creditsButton = new Button(centerX, 400, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);
    optionsButton = new Button(centerX, 500, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);
    quitButton = new Button(centerX, 600, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);
    backButton = new Button(centerX, 700, buttonWidth, buttonHeight, buttonTexture, buttonHoverTexture);

    currentState = MAIN;

    ui = new UI();
    ui->loadTextures();
}

Menu::~Menu() {
    UnloadTexture(background);
    UnloadTexture(logo);
    UnloadTexture(buttonTexture);
    UnloadTexture(buttonHoverTexture);

    delete startButton;
    delete leaderboardButton;
    delete creditsButton;
    delete optionsButton;
    delete quitButton;
    delete backButton;

    delete ui;
}

void Menu::update() {
    switch (currentState) {
        case MAIN:
            updateMainMenu();
            break;
        case LEADERBOARD:
            updateLeaderboard();
            break;
        case CREDITS:
            updateCredits();
            break;
        case GAME:
            ui->updateButtons();
            break;
        case QUIT:
            CloseWindow();
            break;
    }
}

void Menu::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentState) {
        case MAIN:
            drawMainMenu();
            break;
        case LEADERBOARD:
            drawLeaderboard();
            break;
        case CREDITS:
            drawCredits();
            break;
        case GAME:
            ui->drawGameButtons();
            break;
        case QUIT:
            // No need to draw anything
            break;
    }

    EndDrawing();
}

void Menu::drawMainMenu() {
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(logo, 10, 10, WHITE); 

    startButton->update(GetMousePosition());
    leaderboardButton->update(GetMousePosition());
    creditsButton->update(GetMousePosition());
    optionsButton->update(GetMousePosition());
    quitButton->update(GetMousePosition());


    DrawText("Start", startButton->bounds.x + 50, startButton->bounds.y + 15, 20, BLACK);
    DrawText("Leaderboard", leaderboardButton->bounds.x + 20, leaderboardButton->bounds.y + 15, 20, BLACK);
    DrawText("Credits", creditsButton->bounds.x + 45, creditsButton->bounds.y + 15, 20, BLACK);
    DrawText("Options", optionsButton->bounds.x + 45, optionsButton->bounds.y + 15, 20, BLACK);
    DrawText("Quit", quitButton->bounds.x + 60, quitButton->bounds.y + 15, 20, BLACK);
}

void Menu::updateMainMenu() {
    Vector2 mousePoint = GetMousePosition();

    if (startButton->isClicked(mousePoint)) {
        currentState = GAME;
    }
    if (leaderboardButton->isClicked(mousePoint)) {
        currentState = LEADERBOARD;
    }
    if (creditsButton->isClicked(mousePoint)) {
        currentState = CREDITS;
    }
    if (quitButton->isClicked(mousePoint)) {
        currentState = QUIT;
    }
}

void Menu::drawLeaderboard() {
    DrawText("Leaderboard", 100, 100, 30, BLACK);
    backButton->update(GetMousePosition());
    DrawText("Back", backButton->bounds.x + 65, backButton->bounds.y + 15, 20, BLACK);
}

void Menu::updateLeaderboard() {
    if (backButton->isClicked(GetMousePosition())) {
        currentState = MAIN;
    }
}

void Menu::drawCredits() {
    DrawText("Credits", 100, 100, 30, BLACK);
    DrawText("Person 1", 100, 200, 20, BLACK);
    DrawText("Person 2", 100, 250, 20, BLACK);
    DrawText("Person 3", 100, 300, 20, BLACK);
    backButton->update(GetMousePosition());
    DrawText("Back", backButton->bounds.x + 65, backButton->bounds.y + 15, 20, BLACK);
}

void Menu::updateCredits() {
    if (backButton->isClicked(GetMousePosition())) {
        currentState = MAIN;
    }
}
