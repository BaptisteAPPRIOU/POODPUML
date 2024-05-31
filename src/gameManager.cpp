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
    for (Projectile* projectile : projectiles) {
        delete projectile;
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
                enemies[i]->update(camera);
                enemies[i]->move(path);
            }
        }
    }

    map.checkTileHover(camera);
    if (enemy) {
        enemy->move(path);
        enemy->update(camera);
        for (Tower* tower : towers) {
            tower->checkEnemyInRange(enemy->getEnemyPosition());
        }
    }

    for (Tower* tower : towers) {
        tower->update();
    }

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        (*it)->update();
        bool collided = checkProjectileCollision(*it);
        if (collided) {
            delete *it;
            it = projectiles.erase(it);
        } else {
            if ((*it)->getPosition().y <= 0.4f) { 
                delete *it;
                it = projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }
    map.checkTileHover(camera);
    for (Projectile* projectile : projectiles) {
        projectile->update();
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
                    for (size_t i = 0; i < enemies.size(); ++i) {
                        if (GetTime() - startTime >= spawnTimes[i]) {
                            if (enemies[i] != nullptr) {
                                enemies[i]->update(camera); // Pass the 'camera' object as an argument to the 'update()' function
                                enemies[i]->move(path);
                            }
                        }
                    }
                    if (enemy) {
                        enemy->move(path);
                        enemy->update(camera);

                        
                        for (Tower* tower : towers) {
                            tower->checkEnemyInRange(enemy->getEnemyPosition());
                        }
                    }
                    for (Tower* tower : towers) {
                        tower->update();
                    }
                    if (isPlacingTower && hoveringTower) {
                        hoveringTower->hoverTower(map.getHoveredTilePosition());
                    }
                    for (Projectile* projectile : projectiles) {
                        projectile->draw();
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
            cout << "Notification received: Tower creation" << endl;
            std::cout << "Notification received: Tower creation" << endl;
            isPlacingTower = true;
            Vector3 initialHoverPosition = map.getHoveredTilePosition();
            std::cout << "Initial hover position: " << initialHoverPosition.x << ", " << initialHoverPosition.y << ", " << initialHoverPosition.z << endl;
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

                    if (map.isTileBuildable(Vector3{hoveredPosition.x, hoveredPosition.y, hoveredPosition.z}, path)) {
                        cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;
                        // Reset placing state
                    }
                    if (map.isTileBuildable(hoveredPosition, path)) {
                        Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), hoveredPosition);
                        newTower->addObserver(this);
                        towers.push_back(newTower);
                        newTower->draw(hoveredPosition);
                        std::cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << endl;
                        map.setTileBuildable(hoveredPosition, false); 
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
                if(tower->getType() == "slow") {
                    if (tower->enemyInRange && !enemy->slowed && !enemy->isChecked) {                        
                        enemy->setSpeed(enemy->getSpeed() * 0.5f);
                        enemy->slowed = true;
                        enemy->isChecked = true;
                    }
                }
                if(tower->getType() == "basic") {
                    if (tower->enemyInRange) {
                        Vector3 towerPosition = tower->getTowerPosition();
                        towerPosition.y = 6.0f;
                        Projectile* newProjectile = Projectile::createProjectile("basic", towerPosition, enemy->getEnemyPosition());
                        projectiles.push_back(newProjectile);
                    }
                }
                if(tower->getType() == "normal") {
                    if (tower->enemyInRange) {
                        Vector3 towerPosition = tower->getTowerPosition();
                        towerPosition.y = 6.0f;
                        Projectile* newProjectile = Projectile::createProjectile("normal", towerPosition, enemy->getEnemyPosition());
                        projectiles.push_back(newProjectile);
                    }
                }
            }
            break;
        }
        case EventType::ENEMY_OUT_OF_RANGE: {
        std::cout << "Notification received: Enemy out of range" << std::endl;
        for (Tower* tower : towers) {
            if (!enemy->isChecked) {
                if(tower->getType() == "slow") {
                    if (enemy->slowed) {
                        enemy->slowed = false;
                        enemy->setSpeed(enemy->getSpeed()*2.0f);
                    }
                }
            }
        }
        enemy->isChecked = false; // Reset isChecked to false
        break;
        }
        default:
           break;
    }
}

void GameManager::checkTowersForEnemies() {
    Vector3 enemyPosition = enemy->getEnemyPosition();
    for (Tower* tower : towers) {
        tower->checkEnemyInRange(enemyPosition);  
    }
}

// bool GameManager::checkProjectileCollision(Projectile* projectile) {
//     // Get projectile position and damage
//     Vector3 projectilePosition = projectile->getPosition();
//     int projectileDamage = projectile->getDamage();

//     // Loop through enemies to check collision
//     for (auto it = enemies.begin(); it != enemies.end();) {
//         Vector3 enemyPosition = (*it)->getEnemyPosition(); // Access the enemy object correctly
//         float distance = Vector3Distance(projectilePosition, enemyPosition);
//         if (distance <= 1.0f) { // Adjust the collision radius as needed
//             // Apply damage to the enemy
//             (*it)->takeDamage(projectileDamage);

//             // Check if the enemy is destroyed
//             if (!(*it)->isAlive()) {
//                 delete *it;
//                 it = enemies.erase(it);
//             }

//             // Remove the projectile
//             return true;
//         } else {
//             ++it; // Move to the next enemy
//         }
//     }

//     // No collision detected
//     return false;
// }

bool GameManager::checkProjectileCollision(Projectile* projectile) {
    Vector3 projectilePosition = projectile->getPosition();
    int projectileDamage = projectile->getDamage();

    if (enemy) {
        Vector3 enemyPosition = enemy->getEnemyPosition();
        float distance = Vector3Distance(projectilePosition, enemyPosition);
        if (distance <= 1.0f) { 
            enemy->takeDamage(projectileDamage);
            if (!enemy->isEnemyAlive()) {
                delete enemy;
                enemy = nullptr; 
            }
            return true;
        }
    }
    return false;
}