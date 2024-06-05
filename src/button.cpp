#include "button.hpp"
#include <iostream>
using namespace std;

Button::Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture, const char* text)      // Constructor
    : bounds{ x, y, width, height }, texture(texture), hoverTexture(hoverTexture), text(text), isHovered(false) {}

void Button::update(Vector2 mousePoint) {                                                                   // Update function  
    if (CheckCollisionPointRec(mousePoint, bounds)) {
        isHovered = true;
    } else {
        isHovered = false;
    }
}

bool Button::isClicked(Vector2 mousePoint) {                                                                // Function to check if the button is clicked
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

Button::~Button() {                                                                                         // Destructor
    UnloadTexture(texture);
    UnloadTexture(hoverTexture);
}

void Button::drawButton() {                                                                                 // Function to draw the button
    update(GetMousePosition());

    if (isHovered) {
        DrawTexture(hoverTexture, bounds.x, bounds.y, WHITE);
    } else {
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    }
    const char* buttonText = text.c_str();
    int fontSize = 20;  // Assuming a font size of 20
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize;  // The text height is usually approximately equal to the font size

    int textSizeX = (bounds.width - textWidth) / 2;
    int textSizeY = (bounds.height - textHeight) / 2;

    DrawText(buttonText, bounds.x + textSizeX, bounds.y + textSizeY, fontSize, BLACK);
}
