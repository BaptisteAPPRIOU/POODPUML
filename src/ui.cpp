#include "ui.hpp"
#include <iostream>

UI::UI(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    
    buttonTexture1 = LoadTexture("assets/images/button.png");
    buttonHoverTexture1 = LoadTexture("assets/button1_hover.png");
    buttonTexture2 = LoadTexture("assets/images/button.png");
    buttonHoverTexture2 = LoadTexture("assets/button2_hover.png");
    buttonTexture3 = LoadTexture("assets/images/button.png");
    buttonHoverTexture3 = LoadTexture("assets/button3_hover.png");
    buttonTexture4 = LoadTexture("assets/images/button.png");
    buttonHoverTexture4 = LoadTexture("assets/button4_hover.png");

    // Calculate vertical positions to center the buttons
    int buttonWidth = 300;
    int buttonHeight = 50;
    int buttonSpacing = 50;
    int totalHeight = 4 * buttonHeight + 3 * buttonSpacing;
    int startY = (screenHeight - totalHeight) / 2;

    // Create buttons
    button1 = new Button(1550, startY, buttonWidth, buttonHeight, buttonTexture1, buttonHoverTexture1);
    button2 = new Button(1550, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight, buttonTexture2, buttonHoverTexture2);
    button3 = new Button(1550, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, buttonTexture3, buttonHoverTexture3);
    button4 = new Button(1550, startY + 3 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, buttonTexture4, buttonHoverTexture4);
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

    delete button1;
    delete button2;
    delete button3;
    delete button4;
}

void UI::DrawMenu() {
    Vector2 mousePoint = GetMousePosition();

    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
        DrawFPS(10, 10);

        // Draw buttons
        button1->Draw(mousePoint);
        button2->Draw(mousePoint);
        button3->Draw(mousePoint);
        button4->Draw(mousePoint);
    EndDrawing();
}

void UI::UpdateButtons() {
    Vector2 mousePoint = GetMousePosition();

    if (button1->IsClicked(mousePoint)) {
        std::cout << "Button 1 clicked" << std::endl;
    }
    if (button2->IsClicked(mousePoint)) {
        std::cout << "Button 2 clicked" << std::endl;
    }
    if (button3->IsClicked(mousePoint)) {
        std::cout << "Button 3 clicked" << std::endl;
    }
    if (button4->IsClicked(mousePoint)) {
        std::cout << "Button 4 clicked" << std::endl;
    }
}
