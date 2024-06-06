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

    menu.setUI(&ui);
    ui.menu = &menu;

    while (!WindowShouldClose()) {
        if (!menu.isGameStarted) {
            menu.updateMenu();
            menu.drawMenu();
        } else {
            if (!menu.gameManager) {
                menu.resetGameManager();
            }
            menu.gameManager->update();
            menu.gameManager->draw();

            if (menu.gameManager->isGameOver) {
                menu.setGameState(GAME_OVER);
                ui.drawGameOver();
                ui.updateGameOver();
                menu.isGameStarted = false;
            }
            if(menu.gameManager->closeGame) {
                menu.setGameState(MAIN_MENU);
                menu.isGameStarted = false;
                menu.resetGameManager();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
