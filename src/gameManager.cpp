#include "gameManager.hpp"
#include "pathLoader.hpp"
#include <cmath>
#include <iostream>
using namespace std;

GameManager::GameManager()
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), hoveringTower(nullptr), towers(), projectiles(), 
      enemySpawnTimer(0.0f), enemiesToSpawn(0), currentWave(0), enemiesRemaining(0), waveRemaining(0), score(0), money(500), lives(3),  elapsedTime(0.0f), timerStarted(false) ,isGameOver(false), isGameWin(false){

    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    map.loadModelsTextures();
    ui.loadButtons();


    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = cameraFovy;
    camera.projection = CAMERA_PERSPECTIVE;

    path = loadPathFromJSON("assets/paths/pathMedium.json");

    map.drawMap(path);

    ui.addObserver(this);
    map.addObserver(this);

    SetTargetFPS(60);

    initializeWaves();
    startNextWave();
    menu = Menu();
    menu.setGameState(GameState::GAME);
    menu.isGameStarted = true;   
}

GameManager::~GameManager() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    for (Tower* tower : towers) {
        delete tower;
    }
    for (Projectile* projectile : projectiles) {
        delete projectile;
    }
}

void GameManager::initializeWaves() {
    waves = {
        {3, "basic"}
        // {15, "basic"},
        // {20, "hard"}
    };
}

void GameManager::startNextWave() {
    if (currentWave < static_cast<int>(waves.size())) {
        enemiesToSpawn = waves[currentWave].first;
        enemyTypeToSpawn = waves[currentWave].second;
        enemiesRemaining = enemiesToSpawn;
        currentWave++;
        waveRemaining ++;
        enemySpawnTimer = 0.0f;
        std::cout << "Wave " << currentWave << " started with " << enemiesToSpawn << " " << enemyTypeToSpawn << " enemies." << std::endl;
    } else {
        std::cout << "All waves completed!" << std::endl;
        if(lives > 0){
            isGameWin = true;
            menu.isGameStarted = false;
            menu.setGameState(GameState::GAME_WIN);
        }
    }
}

void GameManager::update() {
    if (isGameOver || isGameWin) return;
    map.checkTileHover(camera);

    // Update enemy spawning
    if (enemiesToSpawn > 0) {
        enemySpawnTimer += GetFrameTime();
        if (enemySpawnTimer >= 5.0f) {
            spawnEnemy();
            enemySpawnTimer = 0.0f;
            if (!timerStarted) {
                timerStarted = true;
            }
        }
    }

    // Update all enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->move(path);
        (*it)->update(camera);

        if ((*it)->hasReachedEnd(path)) {
            std::cout << "An enemy has reached the end of the path!" << std::endl;
            delete *it;
            it = enemies.erase(it);
            lives -= 1;
            enemiesRemaining--;
            if (lives <= 0) {
                std::cout << "Game Over" << std::endl;
                isGameOver = true;
                menu.isGameStarted = false;
                menu.setGameState(GameState::GAME_OVER);
            }
        } else if (!(*it)->isEnemyAlive()) {
            int enemyValue = (*it)->getEnemyValue();
            score += enemyValue;
            money += enemyValue / 2;
            delete *it;
            it = enemies.erase(it);
            enemiesRemaining--;
        } else {
            ++it;
        }
    }

    // Check if wave is completed
    if (enemiesToSpawn == 0 && enemies.empty()) {
        startNextWave();
    }

    // Update towers
    for (Tower* tower : towers) {
        tower->update();
        for (Enemy* enemy : enemies) {
            tower->checkEnemyInRange(enemies, enemy->getEnemyPosition());
        }
    }

    // Update projectiles and check collisions
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

    if (timerStarted) {
        elapsedTime += GetFrameTime();
    }

    updateCamera();
    ui.updateButtons(money);
    cout<< "Current state "<<menu.getCurrentState()<<endl;
}

void GameManager::draw() {
    while(GameManager::menu.getCurrentState() == GameState::GAME){
        map.checkTileHover(camera);

        BeginDrawing();
        updateCamera();
        ClearBackground(RAYWHITE);

        BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
        BeginMode3D(camera);
        for (Enemy* enemy : enemies) {
            enemy->move(path);
            enemy->update(camera);
        }
        for (Tower* tower : towers) {
            for (Enemy* enemy : enemies) {
                tower->checkEnemyInRange(enemies, enemy->getEnemyPosition());
            }
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
        ui.drawGameButtons(money);

        DrawText(TextFormat("SCORE: %d", score), 500, 950, 30, BLACK);
        DrawText(TextFormat("MONEY: %d", money), 800, 950, 30, BLACK);
        DrawText(TextFormat("LIVES: %d", lives), 1100, 950, 30, BLACK);
        DrawText(TextFormat("ENEMIES: %d", enemiesRemaining), 550, 1000, 30, BLACK);
        DrawText(TextFormat("WAVES: %d", waveRemaining), 850, 1000, 30, BLACK);
        DrawText(TextFormat("TIME: %.2f", elapsedTime), 1300, 200, 30, BLACK);

        EndDrawing();
        update();
    }
}

void GameManager::updateCamera() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    if (mouseX >= regionX && mouseX <= regionX + regionWidth &&
        mouseY >= regionY && mouseY <= regionY + regionHeight) {
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 1.0f;
        if (IsKeyDown(KEY_LEFT)) camera.position.x -= 1.0f;
        if (IsKeyDown(KEY_UP)) camera.position.y += 1.0f;
        if (IsKeyDown(KEY_DOWN)) camera.position.y -= 1.0f;
    }
}

void GameManager::onNotify(EventType eventType) {
    switch (eventType) {
        case EventType::TOWER_CREATION: {
            std::cout << "Notification received: Tower creation" << std::endl;
            int selectedTowerCost = ui.getSelectedTowerCost();
            if (money >= selectedTowerCost) {
                isPlacingTower = true;
                Vector3 initialHoverPosition = map.getHoveredTilePosition();
                std::cout << "Initial hover position: " << initialHoverPosition.x << ", " << initialHoverPosition.y << ", " << initialHoverPosition.z << std::endl;
                hoveringTower = Tower::createTower(ui.getSelectedTowerType(), initialHoverPosition);
                std::cout << "Tower creation notified: " << ui.getSelectedTowerType() << std::endl;
            } else {
                std::cout << "Not enough money to create the tower." << std::endl;
            }
            break;
        }
        case EventType::TILE_CLICKED: {
            std::cout << "Notification received: Tile clicked" << std::endl;
            if (isPlacingTower) {
                if (hoveringTower) {
                    Vector3 hoveredPosition = map.getHoveredTilePosition();
                    std::cout << "Attempting to place tower at: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << std::endl;

                    if (map.isTileBuildable(hoveredPosition, path)) {
                        int towerCost = hoveringTower->getCost();
                        if (money >= towerCost) {
                            Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), hoveredPosition);
                            newTower->addObserver(this);
                            towers.push_back(newTower);
                            newTower->draw(hoveredPosition);
                            std::cout << "Tower placed at position: " << hoveredPosition.x << ", " << hoveredPosition.y << ", " << hoveredPosition.z << std::endl;
                            map.setTileBuildable(hoveredPosition, false); 
                            isPlacingTower = false;
                            delete hoveringTower;
                            hoveringTower = nullptr;
                            money -= towerCost;
                        } else {
                            std::cout << "Not enough money to place the tower." << std::endl;
                        }
                    } else {
                        std::cout << "Cannot place tower on non-buildable tile." << std::endl;
                    }
                } else {
                    std::cout << "hoveringTower is null when trying to place tower." << std::endl;
                }
            } else {
                std::cout << "isPlacingTower is false when trying to place tower." << std::endl;
            }
            break;
        }
        case EventType::ENEMY_IN_RANGE: {
            std::cout << "Notification received: Enemy in range" << std::endl;
            for (Tower* tower : towers) {
                for (Enemy* enemy : enemies) {
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
            }
            break;
        }
        case EventType::ENEMY_OUT_OF_RANGE: {
            std::cout << "Notification received: Enemy out of range" << std::endl;
            for (Tower* tower : towers) {
                for (Enemy* enemy : enemies) {
                    if (!enemy->isChecked) {
                        if(tower->getType() == "slow") {
                            if (enemy->slowed) {
                                enemy->slowed = false;
                                enemy->setSpeed(enemy->getSpeed()*2.0f);
                            }
                        }
                    }
                }
            }
            for (Enemy* enemy : enemies) {
                enemy->isChecked = false;
            }
            break;
        } case EventType::GAME_CLOSE: {
            std::cout << "Notification received: Game close" << std::endl;
            menu.setGameState(GameState::MAIN_MENU);
            closeGame = true;
            break;
        }
        default:
            break;
    }
    
}

void GameManager::checkTowersForEnemies() {
    for (Tower* tower : towers) {
        for (Enemy* enemy : enemies) {
            Vector3 enemyPosition = enemy->getEnemyPosition();
            tower->checkEnemyInRange(enemies, enemyPosition);  
        }
    }
}

void GameManager::spawnEnemy() {
    if (enemiesToSpawn > 0) {
        enemies.push_back(Enemy::createEnemy(enemyTypeToSpawn, Vector3{-25.0f, 0.0f, -10.0f}));
        enemiesToSpawn--;
    }
}

bool GameManager::checkProjectileCollision(Projectile* projectile) {
    Vector3 projectilePosition = projectile->getPosition();
    int projectileDamage = projectile->getDamage();
    for (auto it = enemies.begin(); it != enemies.end();) {
        Vector3 enemyPosition = (*it)->getEnemyPosition();
        float distance = Vector3Distance(projectilePosition, enemyPosition);
        if (distance <= 1.0f) { 
            (*it)->takeDamage(projectileDamage);
            if (!(*it)->isEnemyAlive()) {
                int enemyValue = (*it)->getEnemyValue();
                score += enemyValue;
                money += enemyValue / 2;
                enemiesRemaining--;
                delete *it;
                it = enemies.erase(it);
            }
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

int GameManager::getScore() const{
    return score;
}