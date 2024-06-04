#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>
#include <string>

class Button {                                                                                          // Class for the button
public:                                                                                                 // Public members
    Rectangle bounds;
    Texture2D texture;
    Texture2D hoverTexture;
    bool isHovered;

    Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture);     // Constructor
    void update(Vector2 mousePoint);                                                                    
    bool isClicked(Vector2 mousePoint);
    ~Button();                                                                                          // Destructor
};

#endif // BUTTON_HPP