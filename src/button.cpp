#include "button.hpp"

Button::Button() 
    : bounds{ 0, 0, 0, 0 }, texture{ 0 }, hoverTexture{ 0 }, isHovered(false) {}

Button::Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture)
    : bounds{ x, y, width, height }, texture(texture), hoverTexture(hoverTexture), isHovered(false) {}

void Button::Draw(Vector2 mousePoint) {
    if (CheckCollisionPointRec(mousePoint, bounds)) {
        isHovered = true;
        DrawTexture(hoverTexture, bounds.x, bounds.y, WHITE);
    } else {
        isHovered = false;
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    }
}

bool Button::IsClicked(Vector2 mousePoint) {
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
