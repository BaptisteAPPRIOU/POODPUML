#include "gameManager.hpp"
#include "basicEnemy.hpp"
#include "map.hpp"
#include "pathLoader.hpp"
#include <vector>
#include <raylib.h>
#include <cmath>
#include <iostream>

using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), enemy(nullptr), hoveringTower(nullptr) {

    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    map.loadModelsTextures();
    ui.loadTextures();

    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = cameraFovy;
    camera.projection = CAMERA_PERSPECTIVE;

    path = loadPathFromJSON("assets/paths/pathMedium.json");

    map.drawMap(path);
    enemy = Enemy::createEnemy("basic", Vector3{ -25.0f, 0.0f, -10.0f });
    tower = Tower::createTower("basic", Vector3{ -22.0f, 0.0f, 2.0f });

    SetTargetFPS(60);
    
}

GameManager::~GameManager() {
    delete enemy;
    delete hoveringTower;
    CloseWindow();
}

void GameManager::update() {
    map.checkTileHover(camera);
    enemy->update();
    enemy->move(path);
    tower->update();
    updateCamera();
    ui.updateButtons();

   if (ui.isPlacingTower()) {
        if (hoveringTower == nullptr) {
            hoveringTower = Tower::createTower(ui.getSelectedTowerType(), Vector3{0.0f, 0.0f, 0.0f});
        }

        Vector3 mousePosition = GetMouseRayHit(camera, GetMousePosition());
        hoveringTower->towerPosition = mousePosition;

        if (map.isTileHovered) {
            hoveringTower->towerPosition = map.getHoveredTilePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (map.isTileBuildable(Vector2{hoveringTower->towerPosition.x, hoveringTower->towerPosition.z}, path)) {
                    placeTower(hoveringTower->towerPosition);
                    delete hoveringTower;
                    hoveringTower = nullptr;
                    ui.resetPlacingTower();
                }
            }
        }
    }
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
                    tower->update();
                    map.drawMap(path);
                    DrawGrid(100, 1.0f);

                    if (hoveringTower != nullptr) {
                        hoveringTower->update();
                    }
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);

            DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);
            ui.drawGameButtons();
            ui.updateButtons();

        EndDrawing();
    }
}

void GameManager::updateCamera() {
    if (IsKeyDown(KEY_RIGHT)) camera.position.x += 1.0f;
    if (IsKeyDown(KEY_LEFT)) camera.position.x -= 1.0f;
    if (IsKeyDown(KEY_UP)) camera.position.y += 1.0f;
    if (IsKeyDown(KEY_DOWN)) camera.position.y -= 1.0f;
}

void GameManager::placeTower(Vector3 position) {
    Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), position);
}

Vector3 GameManager::GetMouseRayHit(Camera camera, Vector2 mousePosition) {
    Ray ray = GetMouseRay(mousePosition, camera);
    RayCollision collision = GetRayCollisionBox(ray, towerBoundingBox); // Assume boundingBox defines the valid area for tower placement

    if (collision.hit) {
        return collision.point;
    }
    return {0.0f, 0.0f, 0.0f}; // Default or invalid position
}
