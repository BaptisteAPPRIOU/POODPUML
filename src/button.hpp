#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>
#include <string>

class Button {
public:
    Rectangle bounds;
    Texture2D texture;
    Texture2D hoverTexture;
    bool isHovered;

    Button();
    Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture);
    void Draw(Vector2 mousePoint);
    bool IsClicked(Vector2 mousePoint);
};

#endif // BUTTON_HPP
