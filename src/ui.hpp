#ifndef UI_HPP
#define UI_HPP

#include <raylib.h>
#include "button.hpp"
#include "map.hpp"

class UI {
public:
    UI(int screenWidth, int screenHeight);
    ~UI();

    void DrawMenu();
    void UpdateButtons();

private:
    int screenWidth;
    int screenHeight;

    Texture2D buttonTexture1;
    Texture2D buttonHoverTexture1;
    Texture2D buttonTexture2;
    Texture2D buttonHoverTexture2;
    Texture2D buttonTexture3;
    Texture2D buttonHoverTexture3;
    Texture2D buttonTexture4;
    Texture2D buttonHoverTexture4;

    Button* button1;
    Button* button2;
    Button* button3;
    Button* button4;
};

#endif // UI_HPP
