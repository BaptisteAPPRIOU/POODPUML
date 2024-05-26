#include <raylib.h>
#include "menu.hpp"

int main() {
    InitWindow(1920, 1080, "Game");
    SetTargetFPS(60);

    Menu menu;

    while (!WindowShouldClose()) {
        menu.update();
        menu.draw();
    }

    return 0;
}
