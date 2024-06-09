#include "ui.hpp"
#include <iostream>

UI::UI(): username(""), finalScore(0){
    loadTextures();
    buttonTower1 = new Button(1420, 250, 400, 120, buttonTexture1, buttonHoverTexture1, "BASIC TOWER");
    buttonTower2 = new Button(1420, 420, 400, 120, buttonTexture2, buttonHoverTexture2, "NORMAL TOWER");
    buttonTower3 = new Button(1420, 600, 400, 120, buttonTexture3, buttonHoverTexture3, "SLOW TOWER");
    buttonTower4 = new Button(1420, 780, 400, 120, buttonTexture4, buttonHoverTexture4, "SPECIAL TOWER");
    buttonStart = new Button(1250, 200, 400, 120, buttonTexture1, buttonHoverTexture1, "START");
    buttonLeaderboard = new Button(1250, 350, 400, 120, buttonTexture2, buttonHoverTexture2, "LEADERBOARD");
    buttonCredits = new Button(1250, 500, 400, 120, buttonTexture3, buttonHoverTexture3, "CREDITS");
    buttonOptions = new Button(1250, 650, 400, 120, buttonTexture4, buttonHoverTexture4, "OPTIONS");
    buttonQuit = new Button(1250, 800, 400, 120, buttonTexture1, buttonHoverTexture1, "QUIT");
    buttonBackLeaderboard = new Button(700, 850, 400, 120, buttonTexture1, buttonHoverTexture1, "BACK");
    buttonBackCredits = new Button(700, 850, 400, 120, buttonTexture2, buttonHoverTexture2, "BACK");
    buttonBackOptions = new Button(700, 850, 400, 120, buttonTexture3, buttonHoverTexture3, "BACK");
    buttonEasy = new Button(700, 200, 400, 120, buttonTexture1, buttonHoverTexture1, "EASY");
    buttonMedium = new Button(700, 400, 400, 120, buttonTexture2, buttonHoverTexture2, "MEDIUM");
    buttonHard = new Button(700, 600, 400, 120, buttonTexture3, buttonHoverTexture3, "HARD");
    buttonBackDifficulty = new Button(700, 850, 400, 120, buttonTexture4, buttonHoverTexture4, "BACK");
    buttonBackGameOver = new Button(700, 850, 400, 120, buttonTexture1, buttonHoverTexture1, "BACK");
    buttonCloseGame = new Button(150, 50, 50, 50, buttonTexture2, buttonHoverTexture2, "X");
}

UI::~UI() {
    // Unload textures
    UnloadTexture(buttonTexture1);
    UnloadTexture(buttonHoverTexture1);
    UnloadTexture(buttonTexture2);
    UnloadTexture(buttonHoverTexture2);
    UnloadTexture(buttonTexture3);
    UnloadTexture(buttonHoverTexture3);
    UnloadTexture(buttonTexture4);
    UnloadTexture(buttonHoverTexture4);

    delete buttonTower1;
    delete buttonTower2;
    delete buttonTower3;
    delete buttonTower4;
    delete buttonStart;
    delete buttonLeaderboard;
    delete buttonCredits;
    delete buttonOptions;
    delete buttonQuit;
    delete buttonBackLeaderboard;
    delete buttonBackCredits;
    delete buttonBackOptions;
    delete buttonEasy;
    delete buttonMedium;
    delete buttonHard;
    delete buttonBackDifficulty;
    delete buttonBackGameOver;
    delete buttonCloseGame;
}

void UI::loadButtons() {
    loadTextures();
    buttonTower1 = new Button(1420, 250, 400, 120, buttonTexture1, buttonHoverTexture1, "BASIC TOWER");
    buttonTower2 = new Button(1420, 420, 400, 120, buttonTexture2, buttonHoverTexture2, "NORMAL TOWER");
    buttonTower3 = new Button(1420, 600, 400, 120, buttonTexture3, buttonHoverTexture3, "SLOW TOWER");
    buttonTower4 = new Button(1420, 780, 400, 120, buttonTexture4, buttonHoverTexture4, "SPECIAL TOWER");
    buttonCloseGame = new Button(150, 50, 50, 50, buttonTexture2, buttonHoverTexture2, "X");
}

void UI::loadTextures() {
    buttonTexture1 = LoadTexture("assets/images/button.png");
    buttonHoverTexture1 = LoadTexture("assets/images/buttonHover.png");
    buttonTexture2 = LoadTexture("assets/images/button.png");
    buttonHoverTexture2 = LoadTexture("assets/images/buttonHover.png");
    buttonTexture3 = LoadTexture("assets/images/button.png");
    buttonHoverTexture3 = LoadTexture("assets/images/buttonHover.png");
    buttonTexture4 = LoadTexture("assets/images/button.png");
    buttonHoverTexture4 = LoadTexture("assets/images/buttonHover.png");
}

void UI::drawGameButtons(int money) {
    buttonTower1Active = money >= 200; // Basic tower cost
    buttonTower2Active = money >= 400; // Normal tower cost
    buttonTower3Active = money >= 500; // Slow tower cost

    buttonTower1->update(GetMousePosition());
    buttonTower2->update(GetMousePosition());
    buttonTower3->update(GetMousePosition());
    buttonTower4->update(GetMousePosition());
    buttonCloseGame->update(GetMousePosition());
    buttonTower1->drawButton();
    buttonTower2->drawButton();
    buttonTower3->drawButton();
    buttonTower4->drawButton();
    buttonCloseGame->drawButton();

    if(buttonTower1Active) DrawText("COST: 200", 1450, 315, 20, BLACK);
    if(buttonTower2Active) DrawText("COST: 400", 1450, 485, 20, BLACK);
    if(buttonTower3Active) DrawText("COST: 500", 1450, 665, 20, BLACK);

    DrawText("SCORE", 500, 950, 30, BLACK);
    DrawText("MONEY", 800, 950, 30, BLACK);
    DrawText("LIVES", 1100, 950, 30, BLACK);

    if (!buttonTower1Active) DrawText("NOT ENOUGH MONEY", 1450, 320, 20, RED);
    if (!buttonTower2Active) DrawText("NOT ENOUGH MONEY", 1450, 490, 20, RED);
    if (!buttonTower3Active) DrawText("NOT ENOUGH MONEY", 1450, 670, 20, RED);
}


void UI::updateButtons(int money) {

    Vector2 mousePoint = GetMousePosition();
    if (buttonTower1->isClicked(mousePoint)) {
        std::cout << "Button 1 clicked" << std::endl;
        selectedTowerType = "basic";
        selectedTowerCost = 200;
        // selectedTowerFireRate = 1.3f;
        std::cout << "Selected Tower Fire Rate: " << selectedTowerFireRate << std::endl; // Add this line
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }

    else if (buttonTower2->isClicked(mousePoint)) {
        std::cout << "Button 2 clicked" << std::endl;
        selectedTowerType = "normal";
        selectedTowerCost = 400;
        // selectedTowerFireRate = 2.0f;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    else if (buttonTower3->isClicked(mousePoint)) {
        std::cout << "Button 3 clicked" << std::endl;
        selectedTowerType = "slow";
        selectedTowerCost = 500;
        // selectedTowerFireRate = 0.0f;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    if (buttonTower4->isClicked(mousePoint)) {
        std::cout << "Button 4 clicked" << std::endl;
    }
    if (buttonCloseGame->isClicked(mousePoint)) {
        std::cout << "Close Game clicked" << std::endl;
        notify(EventType::GAME_CLOSE);
    }
}

bool UI::isPlacingTower() const {
    return placingTower;
}

string UI::getSelectedTowerType() const {
    if (towerShopClicked) {
        return selectedTowerType;
    }
    return "";
}

void UI::resetPlacingTower() {
    placingTower = false;
    selectedTowerType.clear();
}

float UI::getSelectedTowerFireRate() const {
    return selectedTowerFireRate;
}

int UI::getSelectedTowerCost() const {
    return selectedTowerCost;
}

void UI::drawGame() {
    drawGameButtons(500);
}

void UI::drawCredits(){
    buttonBackCredits->update(GetMousePosition());
    buttonBackCredits->drawButton();
    DrawText("CREDITS", 700, 100, 50, BLACK);
    DrawText("Developed by: ", 700, 200, 30, BLACK);
    DrawText("John Doe", 700, 250, 30, BLACK);
    DrawText("Jane Doe", 700, 300, 30, BLACK);
    DrawText("Special thanks to: ", 700, 400, 30, BLACK);
    DrawText("Raylib", 700, 450, 30, BLACK);
    DrawText("Google", 700, 500, 30, BLACK);
}

void UI::drawLeaderboard(){
    buttonBackLeaderboard->update(GetMousePosition());
    buttonBackLeaderboard->drawButton();
    DrawText("LEADERBOARD", 700, 100, 50, BLACK);
    DrawText("1. John Doe - 1000", 700, 200, 30, BLACK);
    DrawText("2. Jane Doe - 900", 700, 250, 30, BLACK);
    DrawText("3. John Doe - 800", 700, 300, 30, BLACK);
    DrawText("4. Jane Doe - 700", 700, 350, 30, BLACK);
    DrawText("5. John Doe - 600", 700, 400, 30, BLACK);
    DrawText("6. Jane Doe - 500", 700, 450, 30, BLACK);
    DrawText("7. John Doe - 400", 700, 500, 30, BLACK);
    DrawText("8. Jane Doe - 300", 700, 550, 30, BLACK);
    DrawText("9. John Doe - 200", 700, 600, 30, BLACK);
    DrawText("10. Jane Doe - 100", 700, 650, 30, BLACK);
}

void UI::drawMainMenu(){
    buttonStart->update(GetMousePosition());
    buttonLeaderboard->update(GetMousePosition());
    buttonCredits->update(GetMousePosition());
    buttonOptions->update(GetMousePosition());
    buttonQuit->update(GetMousePosition());
    buttonStart->drawButton();
    buttonLeaderboard->drawButton();
    buttonCredits->drawButton();
    buttonOptions->drawButton();
    buttonQuit->drawButton();
    DrawText("TOWER DEFENSE", 700, 100, 50, BLACK);
}

void UI::drawDifficultyMenu(){
    buttonEasy->update(GetMousePosition());
    buttonMedium->update(GetMousePosition());
    buttonHard->update(GetMousePosition());
    buttonBackDifficulty->update(GetMousePosition());
    buttonEasy->drawButton();
    buttonMedium->drawButton();
    buttonHard->drawButton();
    buttonBackDifficulty->drawButton();
}

void UI::drawOptions(){
    buttonBackOptions->update(GetMousePosition());
    buttonBackOptions->drawButton();
    DrawText("OPTIONS", 700, 100, 50, BLACK);
    DrawText("SOUND", 700, 200, 30, BLACK);
    DrawText("MUSIC", 700, 250, 30, BLACK);
}

void UI::drawGameOver(int finalScore){
    ClearBackground(RAYWHITE);
    DrawText("GAME OVER", 700, 100, 50, BLACK);
    DrawText("YOU LOSE", 700, 200, 30, BLACK);
    DrawText("ENTER YOUR USERNAME:", 700, 300, 30, BLACK);
    
    drawInputTextBox();
    DrawText(TextFormat("SCORE: %d", finalScore), 700, 400, 30, BLACK);

    // Draw the buttons
    buttonBackGameOver->update(GetMousePosition());
    buttonBackGameOver->drawButton();
    Leaderboard leaderboard;

    if(buttonBackGameOver->isClicked(GetMousePosition())){
        leaderboard.setUsername(username);
        std::cout<<"Username entered: "<<username<<std::endl;
    }
}

void UI::drawGameWin(){
    DrawText("GAME WIN", 700, 100, 50, BLACK);
    DrawText("YOU WIN", 700, 200, 30, BLACK);
}

void UI::drawInputTextBox() {
    // Input box for username
    int textBoxWidth = 500;
    int textBoxHeight = 40;
    int textBoxX = (GetScreenWidth() - textBoxWidth) / 2;
    int textBoxY = 500;
    DrawRectangle(textBoxX, textBoxY, textBoxWidth, textBoxHeight, LIGHTGRAY);

    // Draw the updated username input string
    DrawText(username.c_str(), textBoxX + 5, textBoxY + 5, 20, BLACK);

    // Get input from user
    int key = GetCharPressed();
    if (key > 0 && key != 127) {
        username += (char)key;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && username.size() > 0) {
        username.pop_back();
    }
    // if(IsKeyPressed(KEY_ENTER)){
    //     std::cout<<"Username entered: "<<username<<std::endl;
    // }

}
