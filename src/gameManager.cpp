#include "gameManager.hpp"
#include "pathLoader.hpp"
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
    map.setPath(path);

    map.drawMap(path);
    enemy = Enemy::createEnemy("basic", Vector3{ -25.0f, 0.0f, -10.0f });
    tower = Tower::createTower("basic", Vector3{ -22.0f, 0.0f, 2.0f });

    ui.addObserver(this);
    map.addObserver(this);

    debugLogFile.open("debug.log", ios::out | ios::trunc);
    if (!debugLogFile.is_open()) {
        cerr << "Failed to open debug log file!" << endl;
    }

    SetTargetFPS(60);
    
}

GameManager::~GameManager() {
    delete enemy;
    delete tower;
    if (debugLogFile.is_open()) {
        debugLogFile.close();
    }
    CloseWindow();
}

void GameManager::update() {
    map.checkTileHover(camera);
    enemy->update();
    enemy->move(path);
    
    if (isPlacingTower && hoveringTower) {
        Vector3 hoveredPosition = map.getHoveredTilePosition();
        hoveringTower->hoverTower(hoveredPosition);
        logDebug("Hovering Tower at Position: " + to_string(hoveredPosition.x) + ", " + to_string(hoveredPosition.y) + ", " + to_string(hoveredPosition.z));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            logDebug("Mouse button pressed while placing tower");
            if (map.isTileBuildable(Vector2{hoveredPosition.x, hoveredPosition.z}, path)) {
                logDebug("Tile is buildable at position: " + to_string(hoveredPosition.x) + ", " + to_string(hoveredPosition.z));
                placeTower(hoveredPosition);
            } else {
                logDebug("Tile is NOT buildable at position: " + to_string(hoveredPosition.x) + ", " + to_string(hoveredPosition.z));
            }
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
                    tower->update();
                    if (isPlacingTower && hoveringTower) {
                        hoveringTower->hoverTower(map.getHoveredTilePosition());
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
    std::cout << "GameManager received notification from Map" << std::endl;

    if (ui.isPlacingTower()) {
        Vector3 position = map.getHoveredTilePosition();
        logDebug("Placing tower at position: " + to_string(position.x) + ", " + to_string(position.y) + ", " + to_string(position.z));
        placeTower(position);
    } else {
        logDebug("Not placing tower. UI is not in placing tower mode.");
    }

    isPlacingTower = true;
    Vector3 initialHoverPosition = map.getHoveredTilePosition();
    hoveringTower = Tower::createTower(ui.getSelectedTowerType(), initialHoverPosition);
    std::cout << "Tower creation notified: " << ui.getSelectedTowerType() << std::endl;
}


void GameManager::placeTower(Vector3 position) {
    if (hoveringTower && map.isTileBuildable(Vector2{position.x, position.z}, path)) {
        logDebug("Placing tower at position: " + to_string(position.x) + ", " + to_string(position.y) + ", " + to_string(position.z));

        // Place the tower at the specified position
        
        tower = hoveringTower; // Assign hovering tower to the main tower
        tower->towerPosition = position; // Fix the tower position

        // Clear hovering state
        hoveringTower = nullptr;
        isPlacingTower = false;
        ui.resetPlacingTower();

        logDebug("Tower placed successfully");
    } else {
        logDebug("Failed to place tower");
    }
}

void GameManager::logDebug(const std::string& message) {
    if (debugLogFile.is_open()) {
        debugLogFile << message << std::endl;
        debugLogFile.flush();
    }
}
