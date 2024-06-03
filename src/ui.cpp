#include "ui.hpp"
#include <iostream>

UI::UI(){}

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
    buttonTower1 = new Button(1420, 250, 400, 120, buttonTexture1, buttonHoverTexture1);
    buttonTower2 = new Button(1420, 420, 400, 120, buttonTexture2, buttonHoverTexture2);
    buttonTower3 = new Button(1420, 600, 400, 120, buttonTexture3, buttonHoverTexture3);
    buttonTower4 = new Button(1420, 780, 400, 120, buttonTexture4, buttonHoverTexture4);
}

void UI::drawGameButtons() {
    buttonTower1->update(GetMousePosition());
    buttonTower2->update(GetMousePosition());
    buttonTower3->update(GetMousePosition());
    buttonTower4->update(GetMousePosition());

    DrawText("BASIC TOWER", 1450, 285, 30, BLACK);
    DrawText("NORMAL TOWER", 1450, 455, 30, BLACK);
    DrawText("SLOW TOWER", 1450, 635, 30, BLACK);


    DrawText("SCORE", 500, 950, 30, BLACK);
    
    DrawText("MONEY", 800, 950, 30, BLACK);

    DrawText("LIVES", 1100, 950, 30, BLACK);
}

void UI::updateButtons() {

    Vector2 mousePoint = GetMousePosition();
    if (buttonTower1->isClicked(mousePoint)) {
        std::cout << "Button 1 clicked" << std::endl;
        selectedTowerType = "basic";
        // selectedTowerFireRate = 1.3f;
        std::cout << "Selected Tower Fire Rate: " << selectedTowerFireRate << std::endl; // Add this line
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }

    else if (buttonTower2->isClicked(mousePoint)) {
        std::cout << "Button 2 clicked" << std::endl;
        selectedTowerType = "normal";
        // selectedTowerFireRate = 2.0f;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    else if (buttonTower3->isClicked(mousePoint)) {
        std::cout << "Button 3 clicked" << std::endl;
        selectedTowerType = "slow";
        // selectedTowerFireRate = 0.0f;
        placingTower = true;
        towerShopClicked = true;
        notify(EventType::TOWER_CREATION);
    }
    if (buttonTower4->isClicked(mousePoint)) {
        std::cout << "Button 4 clicked" << std::endl;
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