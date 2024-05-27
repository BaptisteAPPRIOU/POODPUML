#include "gameManager.hpp"
#include "pathLoader.hpp"
#include <cmath>
#include <iostream>
using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), enemy(nullptr), hoveringTower(nullptr), towers() {

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

    ui.addObserver(this);
    SetTargetFPS(60);
}

GameManager::~GameManager() {
    delete enemy;
    for (Tower* tower : towers) {
        delete tower;
    }
    CloseWindow();
}

void GameManager::update() {
    map.checkTileHover(camera);
    enemy->update();
    enemy->move(path);
    cout << "Enemy position: " << enemy->getEnemyPosition().x << ", " << enemy->getEnemyPosition().y << ", " << enemy->getEnemyPosition().z << endl;

    for (Tower* tower : towers) {
        // Check if enemy is in range for each tower
        if (tower->isEnemyInRange(enemy->getEnemyPosition())) {
            tower->onNotify(); // Notify the tower
        } else {
            tower->enemyInRange = false; // No enemy in range
        }
    }
    updateCamera();
    ui.updateButtons();
}

void GameManager::draw() {
    while (!WindowShouldClose()) {
        map.checkTileHover(camera);

        BeginDrawing();
            updateCamera();
            ClearBackground(RAYWHITE);

            BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
                BeginMode3D(camera);
                    enemy->move(path);
                    enemy->update();
                    if (isPlacingTower && hoveringTower) {
                        hoveringTower->hoverTower(map.getHoveredTilePosition());
                    }
                    else {
                        for (Tower* tower : towers) {
                            tower->update();
                        }
                    }
                    map.drawMap(path);
                    DrawGrid(100, 1.0f);
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
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    if (mouseX >= regionX && mouseX <= regionX + regionWidth &&
        mouseY >= regionY && mouseY <= regionY + regionHeight)
        {
            if (IsKeyDown(KEY_RIGHT)) camera.position.x += 1.0f;
            if (IsKeyDown(KEY_LEFT)) camera.position.x -= 1.0f;
            if (IsKeyDown(KEY_UP)) camera.position.y += 1.0f;
            if (IsKeyDown(KEY_DOWN)) camera.position.y -= 1.0f;
        }
}

void GameManager::onNotify() {
    cout << "Notification received: Tower creation" << endl;

    if (isPlacingTower && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector3 hoveredPosition = map.getHoveredTilePosition();

        if (map.isTileBuildable(Vector2{ hoveredPosition.x, hoveredPosition.z }, path)) {
            Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), hoveredPosition);
            towers.push_back(newTower);
            cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;
            isPlacingTower = false;
            hoveringTower = nullptr;
        } else {
            cout << "Cannot place tower on non-buildable tile." << endl;
        }
    }
    else {
        isPlacingTower = true;
        Vector3 initialHoverPosition = map.getHoveredTilePosition();
        hoveringTower = Tower::createTower(ui.getSelectedTowerType(), initialHoverPosition);
        std::cout << "Tower creation notified: " << ui.getSelectedTowerType() << std::endl;
    }
}