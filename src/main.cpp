#include <raylib.h>
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"

int main() {
    InitWindow(1920, 1080, "Tower Defense Game");
    SetTargetFPS(60);

    Color darkGreen = Color{20, 160, 133, 255}; 
    Menu menu;
    UI ui;
    ui.menu = &menu;
    menu.setUI(&ui);

    while (!WindowShouldClose()) {
        menu.updateMenu();
        BeginDrawing();
        ClearBackground(darkGreen);
        ui.drawMainMenu();
        EndDrawing();
    }
    return 0;
}