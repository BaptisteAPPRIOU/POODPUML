#include "gameManager.hpp"
#include "pathBuilder.hpp"
#include <iostream>
using namespace std;

int main() {
    GameManager gameManager;

    while(!WindowShouldClose()) {
        gameManager.update();
        gameManager.draw();
    }
    return 0;
}