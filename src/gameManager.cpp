#include "gameManager.hpp"
#include "basicEnemy.hpp"
#include "map.hpp"
#include <vector>
#include <raylib.h>
#include <cmath>
#include <iostream>

using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), enemy(nullptr) {

    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    map.loadModelsTextures();

    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = cameraFovy;
    camera.projection = CAMERA_PERSPECTIVE;

    path = {
        { -25.0f, -10.0f }, { -22.0f, -10.0f }, { -19.0f, -10.0f }, { -16.0f, -10.0f }, { -13.0f, -10.0f },
        { -10.0f, -10.0f }, { -10.0f, -7.0f }, { -10.0f, -4.0f }, { -10.0f, -1.0f }
    };

    map.drawMap(path);
    enemy = Enemy::createEnemy("basic", Vector3{ -25.0f, 0.0f, -10.0f });

    SetTargetFPS(60);
}

GameManager::~GameManager() {
    delete enemy;
    CloseWindow();
}

void GameManager::update() {
    map.checkTileHover(camera);
    enemy->update();
    enemy->move(path);
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
                    enemy->move(path);
                    enemy->update();
                    map.drawMap(path);
                    DrawGrid(100, 1.0f);
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);
        EndDrawing();
    }
}

void GameManager::updateCamera() {
    if (IsKeyDown(KEY_RIGHT)) camera.position.x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) camera.position.x -= 1.0f;
    if (IsKeyDown(KEY_UP)) camera.position.y += 1.0f;
    if (IsKeyDown(KEY_DOWN)) camera.position.y -= 1.0f;
}

