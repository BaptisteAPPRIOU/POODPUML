#include "ui.hpp"
#include <iostream>

UI::UI(): username(""){                                                                                         // Constructor for the UI class
    loadTextures();
    buttonTower1 = new Button(1420, 250, 400, 120, basicTowerTexture, basicTowerHoverTexture, "BASIC TOWER");
    buttonTower2 = new Button(1420, 420, 400, 120, normalTowerTexture, normalTowerHoverTexture, "NORMAL TOWER");
    buttonTower3 = new Button(1420, 600, 400, 120, slowTowerTexture, slowTowerHoverTexture, "SLOW TOWER");
    buttonStart = new Button(1450, 200, 400, 120, buttonTexture1, buttonHoverTexture1, "START");
    buttonLeaderboard = new Button(1450, 350, 400, 120, buttonTexture2, buttonHoverTexture2, "LEADERBOARD");
    buttonCredits = new Button(1450, 500, 400, 120, buttonTexture3, buttonHoverTexture3, "CREDITS");
    buttonOptions = new Button(1450, 650, 400, 120, buttonTexture3, buttonHoverTexture3, "OPTIONS");
    buttonQuit = new Button(1450, 800, 400, 120, buttonTexture1, buttonHoverTexture1, "QUIT");
    buttonBackLeaderboard = new Button(700, 850, 400, 120, buttonTexture1, buttonHoverTexture1, "BACK");
    buttonBackCredits = new Button(700, 850, 400, 120, buttonTexture2, buttonHoverTexture2, "BACK");
    buttonBackOptions = new Button(700, 850, 400, 120, buttonTexture3, buttonHoverTexture3, "BACK");
    buttonEasy = new Button(700, 200, 400, 120, buttonTexture1, buttonHoverTexture1, "EASY");
    buttonMedium = new Button(700, 400, 400, 120, buttonTexture2, buttonHoverTexture2, "MEDIUM");
    buttonHard = new Button(700, 600, 400, 120, buttonTexture3, buttonHoverTexture3, "HARD");
    buttonBackDifficulty = new Button(700, 850, 400, 120, buttonTexture3, buttonHoverTexture3, "BACK");
    buttonBackGameOver = new Button(700, 850, 400, 120, buttonTexture1, buttonHoverTexture1, "BACK");
    buttonBackGameWin = new Button(700, 850, 400, 120, buttonTexture1, buttonHoverTexture1, "BACK");
    buttonCloseGame = new Button(150, 50, 50, 50, buttonTexture2, buttonHoverTexture2, "X");

    backgroundImage = LoadImage("assets/images/background.png");
    backgroundCredits = LoadImage("assets/images/backgroundCredits.png");
    backgroundLeaderboard = LoadImage("assets/images/backgroundLeaderboard.png");
    backgroundDifficulty = LoadImage("assets/images/backgroundDifficulty.png");
    backgroundGameOver = LoadImage("assets/images/backgroundGameOver.png");
    backgroundGameWin = LoadImage("assets/images/backgroundGameWin.png");
    backgroundOptions = LoadImage("assets/images/backgroundOptions.png");
    backgroundTexture = LoadTextureFromImage(backgroundImage);
    backgroundCreditsTexture = LoadTextureFromImage(backgroundCredits);
    backgroundLeaderboardTexture = LoadTextureFromImage(backgroundLeaderboard);
    backgroundDifficultyTexture = LoadTextureFromImage(backgroundDifficulty);
    backgroundGameOverTexture = LoadTextureFromImage(backgroundGameOver);
    backgroundGameWinTexture = LoadTextureFromImage(backgroundGameWin);
    backgroundOptionsTexture = LoadTextureFromImage(backgroundOptions);
}

UI::~UI() {                                                                                                     // Destructor for the UI class
    UnloadTexture(buttonTexture1);
    UnloadTexture(buttonHoverTexture1);
    UnloadTexture(buttonTexture2);
    UnloadTexture(buttonHoverTexture2);
    UnloadTexture(buttonTexture3);
    UnloadTexture(buttonHoverTexture3);
    UnloadTexture(basicTowerTexture);
    UnloadTexture(basicTowerHoverTexture);
    UnloadTexture(normalTowerTexture);
    UnloadTexture(normalTowerHoverTexture);
    UnloadTexture(slowTowerTexture);
    UnloadTexture(slowTowerHoverTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(backgroundCreditsTexture);
    UnloadTexture(backgroundLeaderboardTexture);
    UnloadTexture(backgroundDifficultyTexture);
    UnloadTexture(backgroundGameOverTexture);
    UnloadTexture(backgroundGameWinTexture);
    UnloadImage(backgroundImage);
    UnloadImage(backgroundCredits);
    UnloadImage(backgroundLeaderboard);
    UnloadImage(backgroundDifficulty);
    UnloadImage(backgroundGameOver);
    UnloadImage(backgroundGameWin);

    delete buttonTower1;
    delete buttonTower2;
    delete buttonTower3;
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
    delete buttonBackGameWin;
}

void UI::loadButtons() {                                                                                        // Function to load the buttons
    loadTextures();
    buttonTower1 = new Button(1420, 250, 400, 120, basicTowerTexture, basicTowerHoverTexture, "BASIC TOWER");
    buttonTower2 = new Button(1420, 420, 400, 120, normalTowerTexture, normalTowerHoverTexture, "NORMAL TOWER");
    buttonTower3 = new Button(1420, 600, 400, 120, slowTowerTexture, slowTowerHoverTexture, "SLOW TOWER");
    buttonCloseGame = new Button(1850, 50, 50, 50, buttonTexture2, buttonHoverTexture2, "X");
}

void UI::loadTextures() {                                                                                       // Function to load the textures
    buttonTexture1 = LoadTexture("assets/images/button.png");
    buttonHoverTexture1 = LoadTexture("assets/images/buttonHover.png");
    buttonTexture2 = LoadTexture("assets/images/button.png");
    buttonHoverTexture2 = LoadTexture("assets/images/buttonHover.png");
    buttonTexture3 = LoadTexture("assets/images/button.png");
    buttonHoverTexture3 = LoadTexture("assets/images/buttonHover.png");
    basicTowerTexture = LoadTexture("assets/images/basicTowerButton.png");
    basicTowerHoverTexture = LoadTexture("assets/images/basicTowerButtonHover.png");
    normalTowerTexture = LoadTexture("assets/images/normalTowerButton.png");
    normalTowerHoverTexture = LoadTexture("assets/images/normalTowerButtonHover.png");
    slowTowerTexture = LoadTexture("assets/images/slowTowerButton.png");
    slowTowerHoverTexture = LoadTexture("assets/images/slowTowerButtonHover.png");
}

void UI::drawGameButtons(int money) {                                                                           // Function to draw the game buttons
    buttonTower1Active = money >= 200; 
    buttonTower2Active = money >= 400; 
    buttonTower3Active = money >= 500; 

    buttonTower1->update(GetMousePosition());
    buttonTower2->update(GetMousePosition());
    buttonTower3->update(GetMousePosition());
    buttonCloseGame->update(GetMousePosition());
    buttonTower1->drawButton();
    buttonTower2->drawButton();
    buttonTower3->drawButton();
    buttonCloseGame->drawButton();

    if(buttonTower1Active) DrawText("COST: 200", 1450, 325, 20, BLACK);
    if(buttonTower2Active) DrawText("COST: 400", 1450, 495, 20, BLACK);
    if(buttonTower3Active) DrawText("COST: 500", 1450, 675, 20, BLACK);

    if (!buttonTower1Active) DrawText("NOT ENOUGH MONEY", 1450, 340, 20, RED);
    if (!buttonTower2Active) DrawText("NOT ENOUGH MONEY", 1450, 510, 20, RED);
    if (!buttonTower3Active) DrawText("NOT ENOUGH MONEY", 1450, 690, 20, RED);
}

void UI::updateButtons(int money) {                                                                             // Function to update the buttons based on the money
    Vector2 mousePoint = GetMousePosition();
    if (buttonTower1->isClicked(mousePoint)) {
        selectedTowerType = "basic";
        selectedTowerCost = 200;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    else if (buttonTower2->isClicked(mousePoint)) {
        selectedTowerType = "normal";
        selectedTowerCost = 400;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    else if (buttonTower3->isClicked(mousePoint)) {
        selectedTowerType = "slow";
        selectedTowerCost = 500;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    if (buttonCloseGame->isClicked(mousePoint)) {
        std::cout << "Close Game clicked" << std::endl;
        notify(EventType::GAME_CLOSE);
    }
}

bool UI::isPlacingTower() const {                                                                               // Function to check if a tower is being placed
    return placingTower;
}

string UI::getSelectedTowerType() const {                                                                       // Function to get the selected tower type
    if (towerShopClicked) {
        return selectedTowerType;
    }
    return "";
}

void UI::resetPlacingTower() {                                                                                  // Function to reset the placing tower
    placingTower = false;
    selectedTowerType.clear();
}

float UI::getSelectedTowerFireRate() const {                                                                    // Function to get the selected tower fire rate             
    return selectedTowerFireRate;
}

int UI::getSelectedTowerCost() const {                                                                          // Function to get the selected tower cost
    return selectedTowerCost;
}

void UI::drawGame() {                                                                                           // Function to draw the game               
    drawGameButtons(500);
}

void UI::drawCredits(){                                                                                         // Function to draw the credits
    DrawTexture(backgroundCreditsTexture, 0, 0, WHITE);
    buttonBackCredits->update(GetMousePosition());
    buttonBackCredits->drawButton();
    DrawText("Developed by: ", 300, 100, 30, BLACK);
    DrawText("Oussema FATNASSI", 800, 140, 30, BLACK);
    DrawText("Baptiste APPRIOU", 300, 140, 30, BLACK);
    DrawText("Ali ABAKAR ISSA", 1300, 140, 30, BLACK);
    DrawText("Graphics by: ", 300, 200, 30, BLACK);
    DrawText("Oussema FATNASSI", 800, 200, 30, BLACK);
}

void UI::drawLeaderboard(){                                                                                     // Function to draw the leaderboard
    DrawTexture(backgroundLeaderboardTexture, 0, 0, WHITE);
    buttonBackLeaderboard->update(GetMousePosition());
    buttonBackLeaderboard->drawButton();
    
    Leaderboard leaderboard; 

    std::vector<std::pair<std::string, int>> leaderboardData = leaderboard.loadFromTxt();                       // Load the leaderboard data from the file
    int yPosition = 200;
    int rank = 1;
    int scoreXPosition = 900; 
    int maxEntries = std::min(10, static_cast<int>(leaderboardData.size()));                                    // Display top 10 entries
    for (int i = 0; i < maxEntries; ++i) {
        const auto& entry = leaderboardData[i];
        std::string entryText = TextFormat("%d. %-20s", rank++, entry.first.c_str());
        DrawText(entryText.c_str(), 700, yPosition, 30, BLACK);
        DrawText(TextFormat("%d", entry.second), scoreXPosition, yPosition, 30, BLACK); 
        yPosition += 50; 
    }
}

void UI::drawMainMenu(){                                                                                        // Function to draw the main menu                   
    DrawTexture(backgroundTexture, 0, 0, WHITE);
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
}

void UI::drawDifficultyMenu(){                                                                                  // Function to draw the difficulty menu
    DrawTexture(backgroundDifficultyTexture, 0, 0, WHITE);
    buttonEasy->update(GetMousePosition());
    buttonMedium->update(GetMousePosition());
    buttonHard->update(GetMousePosition());
    buttonBackDifficulty->update(GetMousePosition());
    buttonEasy->drawButton();
    buttonMedium->drawButton();
    buttonHard->drawButton();
    buttonBackDifficulty->drawButton();
}

void UI::drawOptions(){                                                                                         // Function to draw the options
    DrawTexture(backgroundOptionsTexture, 0, 0, WHITE);
    buttonBackOptions->update(GetMousePosition());
    buttonBackOptions->drawButton();
    DrawText("OPTIONS", 700, 100, 50, BLACK);
    DrawText("SOUND", 700, 200, 30, BLACK);
    DrawText("MUSIC", 700, 250, 30, BLACK);
}

void UI::drawGameOver(int finalScore){                                                                          // Function to draw the game over screen                 
    DrawTexture(backgroundGameOverTexture, 0, 0, WHITE);
    DrawText("ENTER YOUR USERNAME AND PRESS ENTER:", 700, 300, 30, BLACK);
    
    drawInputTextBox();
    DrawText(TextFormat("SCORE: %d", finalScore), 700, 500, 30, BLACK);

    buttonBackGameOver->update(GetMousePosition());
    buttonBackGameOver->drawButton();

    if(IsKeyPressed(KEY_ENTER)){
        leaderboard.setScore(finalScore);
        leaderboard.setUsername(username);
        leaderboard.saveToTxt();
        leaderboard.reorderLeaderboard();
    }
}

void UI::drawGameWin(int finalScore){                                                                           // Function to draw the game win screen                
    DrawTexture(backgroundGameWinTexture, 0, 0, WHITE);
    DrawText("ENTER YOUR USERNAME AND PRESS ENTER:", 700, 300, 30, BLACK);
    
    drawInputTextBox();
    DrawText(TextFormat("SCORE: %d", finalScore), 700, 500, 30, BLACK);

    buttonBackGameWin->update(GetMousePosition());
    buttonBackGameWin->drawButton();

    if(IsKeyPressed(KEY_ENTER)){
        leaderboard.setScore(finalScore);
        leaderboard.setUsername(username);
        leaderboard.saveToTxt();
        leaderboard.reorderLeaderboard();
    }
}

void UI::drawInputTextBox() {                                                                                   // Function to draw the input text box             
    int textBoxWidth = 500;
    int textBoxHeight = 40;
    int textBoxX = (GetScreenWidth() - textBoxWidth) / 2;
    int textBoxY = 400;
    DrawRectangle(textBoxX, textBoxY, textBoxWidth, textBoxHeight, WHITE);

    DrawText(username.c_str(), textBoxX + 5, textBoxY + 5, 20, BLACK);                                          // Draw the updated username input string

    int key = GetCharPressed();                                                                                 // Get the key pressed by the user               
    if (key > 0 && key != 127) {
        username += (char)key;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && username.size() > 0) {
        username.pop_back();
    }
    std::cout << "Current username: " << username << std::endl;
}
