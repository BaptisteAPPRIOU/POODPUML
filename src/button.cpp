#include "button.hpp"

Button::Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture)                                                   // Constructor
    : bounds{ x, y, width, height }, texture(texture), hoverTexture(hoverTexture), isHovered(false) {}

void Button::update(Vector2 mousePoint) {                                                                                                               
    if (CheckCollisionPointRec(mousePoint, bounds)) {
        isHovered = true;
        DrawTexture(hoverTexture, bounds.x, bounds.y, WHITE);
    } else {
        isHovered = false;
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    }
}

bool Button::isClicked(Vector2 mousePoint) {
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
