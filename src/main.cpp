#include <raylib.h>
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"
#include "gameManager.hpp"

int main() {
    InitWindow(1920, 1080, "Tower Defense Game");
    SetTargetFPS(60);

    Menu menu;
    UI ui;
    GameManager gameManager;
    ui.menu = &menu;
    menu.setUI(&ui);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!menu.isGameStarted) {
            menu.updateMenu();
            menu.drawMenu();
        } else {
            gameManager.update();
            gameManager.draw();

            if (gameManager.isGameOver) {
                menu.setGameState(GAME_OVER);
                menu.isGameStarted = false;  
            }
            if (gameManager.closeGame) {
                menu.setGameState(MAIN_MENU);
                menu.isGameStarted = false;  
            }
        }

        EndDrawing();
    }
    CloseWindow(); 
    return 0;
}
