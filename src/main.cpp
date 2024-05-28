#include <raylib.h>
#include <iostream>
#include "gameManager.hpp"

using namespace std;

int main() {
    GameManager gameManager;

    while(!WindowShouldClose()) {
        gameManager.update();
        gameManager.draw();
    }
    return 0;
}