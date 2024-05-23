#include "gameManager.hpp"
#include "basicEnemy.hpp"
#include "map.hpp"
#include "pathLoader.hpp"
#include "wave.hpp"
#include <vector>
#include <raylib.h>
#include <cmath>
#include <iostream>

using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), wave(nullptr) {

    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    map.loadModelsTextures();

    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = cameraFovy;
    camera.projection = CAMERA_PERSPECTIVE;

    path = loadPathFromJSON("assets/paths/pathMedium.json");

    map.drawMap(path);
    // enemies.push_back(Enemy::createEnemy("basic", Vector3{ -25.0f, 0.0f, -10.0f }));
    // enemies.push_back(Enemy::createEnemy("medium", Vector3{ -25.0f, 0.0f, -10.0f }));
    // enemies.push_back(Enemy::createEnemy("hard", Vector3{ -25.0f, 0.0f, -10.0f }));
    wave = new Wave("basic", Vector3{ -25.0f, 0.0f, -10.0f }, 10, path); // Crée une vague de 10 ennemis de type "basic"
    SetTargetFPS(60);
}

GameManager::~GameManager() {
    // for (auto enemy : enemies) {
    //     delete enemy;
    // }
    delete wave;
    CloseWindow();
}

void GameManager::update() {
    map.checkTileHover(camera);
    // for (auto enemy : enemies) {
    //     enemy->update();
    //     enemy->move(path);
    // }
    wave->update();
   updateCamera();
}

void GameManager::draw() {
    while (!WindowShouldClose()) {
        map.checkTileHover(camera);

        BeginDrawing();
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            if (mouseX >= regionX && mouseX <= regionX + regionWidth &&
                mouseY >= regionY && mouseY <= regionY + regionHeight) {
                updateCamera();
            }
            ClearBackground(RAYWHITE);

            BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
                BeginMode3D(camera);
                    // for (auto enemy : enemies) {
                    //     enemy->update();
                    //     enemy->move(path);
                    // }
                    wave->update();
                    map.drawMap(path);
                    DrawGrid(100, 1.0f);
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);

            DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);

        EndDrawing();
    }
}

void GameManager::updateCamera() {
    if (IsKeyDown(KEY_RIGHT)) camera.position.x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) camera.position.x -= 1.0f;
    if (IsKeyDown(KEY_UP)) camera.position.y += 1.0f;
    if (IsKeyDown(KEY_DOWN)) camera.position.y -= 1.0f;
}