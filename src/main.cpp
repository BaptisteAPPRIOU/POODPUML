#include <raylib.h>
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"
#include "gameManager.hpp"

int main() {
    InitWindow(1920, 1080, "Tower Defense Game");
    SetTargetFPS(60);

    Menu menu;                                                                      // Create a menu object
    UI ui;                                                                          // Create a UI object  

    menu.setUI(&ui);                                                                // Set the UI of the menu    
    ui.menu = &menu;                                                                // Set the menu of the UI

    while (!WindowShouldClose()) {
        if (!menu.isGameStarted) {                                                  // If the game is not started     
            menu.updateMenu();
            menu.drawMenu();
        } else {
            if (!menu.gameManager) {
                menu.resetGameManager("closed");
                menu.resetUI();
            }
            menu.gameManager->update();
            menu.gameManager->draw();

            if (menu.gameManager->isGameOver) {
                menu.setGameState(GAME_OVER);
                menu.isGameStarted = false;
            }
            if (menu.gameManager->isGameWin) {
                menu.setGameState(GAME_WIN);
                menu.isGameStarted = false;
            }
            if(menu.gameManager->closeGame) {
                menu.setGameState(MAIN_MENU);
                menu.isGameStarted = false;
                menu.resetGameManager("closed");
                menu.resetUI();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}