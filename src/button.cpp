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

void Button::drawButton() {                                                                                 // Function to draw the button with centered text
    update(GetMousePosition());

    Rectangle sourceRect = {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    Rectangle destRect = {bounds.x, bounds.y, bounds.width, bounds.height};
    Vector2 origin = {0, 0};

    if (isHovered) {
        DrawTexturePro(hoverTexture, sourceRect, destRect, origin, 0.0f, WHITE);
    } else {
        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
    }

    const char* buttonText = text.c_str();
    int fontSize = 20;  
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize;  
    int textSizeX = (bounds.width - textWidth) / 2;
    int textSizeY = (bounds.height - textHeight) / 2;

    DrawText(buttonText, bounds.x + textSizeX, bounds.y + textSizeY, fontSize, BLACK);
}

