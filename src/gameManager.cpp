#include "gameManager.hpp"
#include "pathLoader.hpp"
#include <cmath>
#include <iostream>
using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), enemy(nullptr), hoveringTower(nullptr), towers(), projectiles() {

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
    // projectile1 = Projectile::createProjectile("basic", Vector3{ 0.0f, 10.0f, 0.0f }, enemy->getEnemyPosition());

    ui.addObserver(this);
    map.addObserver(this);

    SetTargetFPS(60);
}

GameManager::~GameManager() {
    delete enemy;
    for (Tower* tower : towers) {
        delete tower;
    }

    for (Projectile* projectile : projectiles) {
        delete projectile;
    }
    CloseWindow();
}

void GameManager::update() { 
    map.checkTileHover(camera);
    enemy->update();
    enemy->move(path);
    for (Tower* tower : towers) {
        tower->update();
        tower->checkEnemyInRange(enemy->getEnemyPosition());
    }

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        (*it)->update();
        if ((*it)->getPosition().z <= 0.0f) { 
            delete *it;
            it = projectiles.erase(it);
        } else {
            ++it;
        }
    }
    for (Projectile* projectile : projectiles) {
        projectile->update();
    }
    // projectile1->update();

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
                    for (Tower* tower : towers) {
                        tower->checkEnemyInRange(enemy->getEnemyPosition());
                        tower->update();
                    }
                    if (isPlacingTower && hoveringTower) {
                        hoveringTower->hoverTower(map.getHoveredTilePosition());
                    }
                    for (Projectile* projectile : projectiles) {
                        projectile->draw();
                    }
                    map.drawMap(path);
                    // projectile1->draw();
                    DrawGrid(100, 1.0f);
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);
            DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);
            ui.drawGameButtons();
            ui.updateButtons();

        EndDrawing();
        update();
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
            std::cout << "Notification received: Tower creation" << endl;
            isPlacingTower = true;
            Vector3 initialHoverPosition = map.getHoveredTilePosition();
            hoveringTower = Tower::createTower(ui.getSelectedTowerType(), initialHoverPosition);
            std::cout << "Tower creation notified: " << ui.getSelectedTowerType() << endl;
            break;
        }
        case EventType::TILE_CLICKED: {
            std::cout << "Notification received: Tile clicked" << endl;
            if (isPlacingTower) {
                if (hoveringTower) {
                    Vector3 hoveredPosition = map.getHoveredTilePosition();
                    std::cout << "Attempting to place tower at: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;

                    if (map.isTileBuildable(hoveredPosition, path)) {
                        Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), hoveredPosition);
                        newTower->addObserver(this);
                        towers.push_back(newTower);
                        newTower->draw(hoveredPosition);
                        std::cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;
                        map.setTileBuildable(hoveredPosition, false); // Update to pass Vector3
                        isPlacingTower = false;
                        delete hoveringTower;
                        hoveringTower = nullptr;
                    } else {
                        std::cout << "Cannot place tower on non-buildable tile." << endl;
                    }
                } else {
                    std::cout << "hoveringTower is null when trying to place tower." << endl;
                }
            } else {
                std::cout << "isPlacingTower is false when trying to place tower." << endl;
            }
            break;
        }
         case EventType::ENEMY_IN_RANGE: {
            std::cout << "Notification received: Enemy in range" << std::endl;
            for (Tower* tower : towers) {
                if (tower->enemyInRange) {
                    Vector3 towerPosition = tower->getTowerPosition();
                    towerPosition.y = 5.0f;
                    Projectile* newProjectile = Projectile::createProjectile("basic", towerPosition, enemy->getEnemyPosition());
                    projectiles.push_back(newProjectile);
                }
            }
            break;
        }
        default:
            break;
    }
}

void GameManager::checkTowersForEnemies() {
    Vector3 enemyPosition = enemy->getEnemyPosition();
    for (Tower* tower : towers) {
        tower->checkEnemyInRange(enemyPosition);  // Call the method directly on the base class
    }
}