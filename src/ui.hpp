#ifndef UI_HPP
#define UI_HPP

#include <raylib.h>
#include "button.hpp"
#include "map.hpp"

class UI {
public:
    UI();
    ~UI();

    void drawGameButtons();
    void updateButtons();
    void loadTextures();
    bool isPlacingTower() const;
    const string& getSelectedTowerType() const;
    void resetPlacingTower();

private:
    Texture2D buttonTexture1;
    Texture2D buttonHoverTexture1;
    Texture2D buttonTexture2;
    Texture2D buttonHoverTexture2;
    Texture2D buttonTexture3;
    Texture2D buttonHoverTexture3;
    Texture2D buttonTexture4;
    Texture2D buttonHoverTexture4;

    Button* buttonTower1;
    Button* buttonTower2;
    Button* buttonTower3;
    Button* buttonTower4;

    bool placingTower;
    string selectedTowerType;
};

#endif // UI_HPP