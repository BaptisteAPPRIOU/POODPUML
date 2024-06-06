#include <raylib.h>
#include <iostream>
#include "gameManager.hpp"
#include "menu.hpp"

int main() {
    InitWindow(1920, 1080, "Tower Defense Game");
    InitAudioDevice(); // Initialize audio device
    SetTargetFPS(60);

    GameManager gameManager;
    Menu menu;

    while (!WindowShouldClose()) {
        if (!menu.isGameStarted()) {
            menu.update();
            BeginDrawing();
            ClearBackground(RAYWHITE);
            menu.draw();
            EndDrawing();
        } else {
            gameManager.update();
            gameManager.draw();
        }
    }

    CloseAudioDevice(); // Close audio device
    return 0;
}

// Visual Leak Detector pour tester les fuites de mémoire