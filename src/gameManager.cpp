#include "gameManager.hpp"
#include "pathLoader.hpp"
#include <vector>
#include <raylib.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), enemy(nullptr), hoveringTower(nullptr), towers(), projectiles(), startTime(GetTime()) {

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
    createEnemies(numEnemies, waveNumber);

    // Initialiser les temps d'apparition
    for (int i = 0; i < static_cast<int>(enemies.size()); ++i) {
        spawnTimes.push_back(i * 2.0f); // Chaque ennemi apparaît avec un intervalle de 2 secondes
    }

    ui.addObserver(this);
    map.addObserver(this);
    SetTargetFPS(60);
}

GameManager::~GameManager() {
    for (auto enemy : enemies) {
        delete enemy;
    }
    CloseWindow();
}

void GameManager::createEnemies(int numEnemies2, int waveNumber2) {
    for (int i = 0; i < numEnemies2; i++) {
        string enemyType;
        if (waveNumber2 < 21) {
            enemyType = "basic";
        } else {
            int randomType = rand() % 3; // Generate a random number between 0 and 2
            switch (randomType) {
                case 0:
                    enemyType = "basic";
                    break;
                case 1:
                    enemyType = "medium";
                    break;
                case 2:
                    enemyType = "hard";
                    break;
            }
        }
        // Créer les ennemis mais ne pas les ajouter immédiatement au jeu
        enemies.push_back(Enemy::createEnemy(enemyType, Vector3{ -25.0f, 0.0f, -10.0f }));
    }
    if (waveNumber2 % 4 == 0) {
        enemies.push_back(Enemy::createEnemy("medium", Vector3{ -25.0f, 0.0f, -10.0f }));
    } if (waveNumber2 % 5 == 0) {
        enemies.push_back(Enemy::createEnemy("hard", Vector3{ -25.0f, 0.0f, -10.0f }));
    }
}

void GameManager::update() {
    float currentTime = GetTime();
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (currentTime - startTime >= spawnTimes[i]) {
            if (enemies[i] != nullptr) {
                enemies[i]->update();
                enemies[i]->move(path);
            }
        }
    }
    map.checkTileHover(camera);
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
                    for (size_t i = 0; i < enemies.size(); ++i) {
                        if (GetTime() - startTime >= spawnTimes[i]) {
                            if (enemies[i] != nullptr) {
                                enemies[i]->update();
                                enemies[i]->move(path);
                            }
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

void GameManager::onNotify(EventType eventType) {
    switch (eventType) {
        case EventType::TOWER_CREATION: {
            cout << "Notification received: Tower creation" << endl;
            break;
        }
        case EventType::TILE_CLICKED: {
            cout << "Notification received: Tile clicked" << endl;
            if (isPlacingTower) {
                if (hoveringTower) {
                    Vector3 hoveredPosition = map.getHoveredTilePosition();
                    cout << "Attempting to place tower at: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;

                    if (map.isTileBuildable(Vector2{hoveredPosition.x, hoveredPosition.z}, path)) {
                        cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;
                        // Reset placing state
                        isPlacingTower = false;
                        hoveringTower = nullptr;
                    } else {
                        cout << "Cannot place tower on non-buildable tile." << endl;
                    }
                } else {
                    cout << "hoveringTower is null when trying to place tower." << endl;
                }
            } else {
                cout << "isPlacingTower is false when trying to place tower." << endl;
            }
            break;
        }
        case EventType::ENEMY_IN_RANGE: {
            cout << "Notification received: Enemy in range" << endl;
            // Implement any additional logic here if needed
            break;
        }
    }
}

