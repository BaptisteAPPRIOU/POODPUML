#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <raylib.h>
#include <string>

class Button {                                                                                          // Class for the button
public:                                                                                                 // Public members
    Rectangle bounds;
    Texture2D texture;
    Texture2D hoverTexture;
    std::string text;
    bool isHovered;

    Button(float x, float y, float width, float height, Texture2D texture, Texture2D hoverTexture, const char* text );     // Constructor
    void drawButton();                                                                                   // Function to draw the button
    void update(Vector2 mousePoint);                                                                    
    bool isClicked(Vector2 mousePoint);
    void setText(const char* text);
    ~Button();                                                                                          // Destructor
};

#endif // BUTTON_HPP
