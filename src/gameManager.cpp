#include "gameManager.hpp"
#include "pathLoader.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

GameManager::GameManager(string difficulty_chosen)
    : screenWidth(1920), screenHeight(1080), regionX(100), regionY(100), regionWidth(1200), regionHeight(800),
      cameraPosition(Vector3{13.0f, 60.0f, 60.0f}), cameraTarget(Vector3{12.0f, 0.0f, 0.0f}), cameraUp(Vector3{0.0f, 1.0f, 0.0f}),
      cameraFovy(50.0f), hoveringTower(nullptr), towers(), projectiles(), 
      enemySpawnTimer(0.0f), enemiesToSpawn(0), currentWave(0), enemiesRemaining(0), waveRemaining(0), score(0), money(500), lives(3),  elapsedTime(0.0f), timerStarted(false) ,isGameOver(false), isGameWin(false){

    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    map.loadModelsTextures();
    ui.loadButtons();

    statisticBackground = LoadImage("assets/images/stats.png");
    textureStatisticBackground = LoadTextureFromImage(statisticBackground);

    setDifficulty(difficulty_chosen);
    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = cameraFovy;
    camera.projection = CAMERA_PERSPECTIVE;

    if (difficulty == "easy") {
        cout << "Normally easy path loaded" << endl;
        path = loadPathFromJSON("assets/paths/pathEasy.json");
    } else if (difficulty == "medium") {
        money = 700;
        cout << "Normally medium path loaded" << endl;
        path = loadPathFromJSON("assets/paths/pathMedium.json");
    } else if (difficulty == "hard") {
        money = 900;
        cout << "Normally hard path loaded" << endl;
        path = loadPathFromJSON("assets/paths/pathHard.json");
    } else {
        cout << "Problem with the difficulty choice" << endl;
        path = loadPathFromJSON("assets/paths/pathMedium.json");
    }

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

GameManager::~GameManager() {                                                                                       // Destructor
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
    if (difficulty == "easy") {
        cout << "Easy waves and easy enemies" << endl;
        waves = {
            {3, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},
            {2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},
            {2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},
            {2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},{2, "basic"},        
        };
    } else if (difficulty == "medium") {
        cout << "Medium waves and medium enemies" << endl;
        waves = {
            {4, "basic"},{4, "medium"},{4, "medium"},{4, "hard"},{4, "medium"},
            // {4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},
            // {4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},
            // {4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},{4, "medium"},        
        };
    } else if (difficulty == "hard") {
        cout << "Hard waves and hard enemies" << endl;
        waves = {
            {6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},
            {6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},
            {6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},
            {6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},{6, "hard"},        
        };
    } else {
        cout << "Problem with difficulty and waves" << endl;
        waves = {
            {10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},
            {10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},
            {10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},
            {10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},{10, "basic"},        
        };
    }
}

void GameManager::startNextWave() {                                                                                 // Function to start the next wave of enemies
    if (currentWave < static_cast<int>(waves.size())) {
        enemyCount = 0;
        for (Tower* tower : towers) {
            tower->resetIndexOfEnemy();
        }
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

void GameManager::update() {                                                                                        // Update function                   
    if (isGameOver || isGameWin) return;
    map.checkTileHover(camera);

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

    for (auto it = enemies.begin(); it != enemies.end();) {                                                         // Update enemies
        (*it)->move(path);
        (*it)->update(camera);

        if ((*it)->hasReachedEnd(path)) {                                                                           // Check if an enemy has reached the end of the path
            std::cout << "An enemy has reached the end of the path!" << std::endl;
            delete *it;
            it = enemies.erase(it);
            lives -= 1;
            enemiesRemaining--;
            if (lives <= 0) {                                                                                       // Check if the player has lost all lives
                std::cout << "Game Over" << std::endl;
                isGameOver = true;
                menu.isGameStarted = false;
                menu.setGameState(GameState::GAME_OVER);
            }
        } else if (!(*it)->isEnemyAlive()) {                                                                        // Check if an enemy is dead
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

    if (enemiesToSpawn == 0 && enemies.empty()) {                                                                   // Check if all enemies have been spawned and defeated to start the next wave
        startNextWave();
    }

    for (Tower* tower : towers) {                                                                                   // Update towers
        tower->checkEnemyInRange(enemies);
        tower->update();
    }

    for (auto it = projectiles.begin(); it != projectiles.end();) {                                                 // Update projectiles and check for collisions
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

    if (timerStarted) {                                                                                             // Update the timer
        elapsedTime += GetFrameTime();
    }

    updateCamera();
    ui.updateButtons(money);
}

void GameManager::draw() {                                                                                          // Draw function                  
    while(GameManager::menu.getCurrentState() == GameState::GAME){
        map.checkTileHover(camera);

        BeginDrawing();
        updateCamera();
        ClearBackground(WHITE);
        DrawTexture(textureStatisticBackground, 1420, 780, WHITE);

        BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
        ClearBackground(LIGHTGRAY);
        BeginMode3D(camera);
        for (Enemy* enemy : enemies) {                                                                              // Draw enemies
            enemy->move(path);
            enemy->update(camera);
        }
        for (Tower* tower : towers) {                                                                               // Draw towers
            tower->checkEnemyInRange(enemies);
            tower->update();
        }
        if (isPlacingTower && hoveringTower) {                                                                      // Draw hovering tower                        
            hoveringTower->hoverTower(map.getHoveredTilePosition());
        }
        for (Projectile* projectile : projectiles) {                                                                // Draw projectiles             
            projectile->draw();
        }
        map.drawMap(path);
        // DrawGrid(100, 1.0f);
        EndMode3D();
        EndScissorMode();

        DrawFPS(10, 10);
        DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);
        ui.drawGameButtons(money);

        DrawText(TextFormat("SCORE: %d", score), 1650, 200, 30, BLACK);
        DrawText(TextFormat("MONEY: %d", money), 1450, 800, 30, BLACK);
        DrawText(TextFormat("LIVES: %d", lives), 1450, 840, 30, BLACK);
        DrawText(TextFormat("ENEMIES: %d", enemiesRemaining), 1450, 920, 30, BLACK);
        DrawText(TextFormat("WAVES: %d", waveRemaining), 1450, 880, 30, BLACK);
        int minutes = static_cast<int>(elapsedTime) / 60;
        int seconds = static_cast<int>(elapsedTime) % 60;
        DrawText(TextFormat("TIME: %02d:%02d", minutes, seconds), 1400, 200, 30, BLACK);

        EndDrawing();
        update();
    }
}

void GameManager::updateCamera() {                                                                                  // Update camera function based on user input             
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

void GameManager::onNotify(EventType eventType) {                                                                   // Notify function for the observer pattern           
    switch (eventType) {
        case EventType::TOWER_CREATION: {                                                                           // Check if a tower is being placed
            int selectedTowerCost = ui.getSelectedTowerCost();
            if (money >= selectedTowerCost) {
                isPlacingTower = true;
                Vector3 initialHoverPosition = map.getHoveredTilePosition();
                hoveringTower = Tower::createTower(ui.getSelectedTowerType(), initialHoverPosition);
            } else {
                std::cout << "Not enough money to create the tower." << std::endl;
            }
            break;
        }
        case EventType::TILE_CLICKED: {                                                                             // Check if a tile is clicked
            if (isPlacingTower) {
                if (hoveringTower) {
                    Vector3 hoveredPosition = map.getHoveredTilePosition();
                    if (map.isTileBuildable(hoveredPosition, path)) {
                        int towerCost = hoveringTower->getCost();
                        if (money >= towerCost) {
                            Tower* newTower = Tower::createTower(ui.getSelectedTowerType(), hoveredPosition);
                            newTower->addObserver(this);
                            towers.push_back(newTower);
                            newTower->draw(hoveredPosition);
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
        case EventType::ENEMY_IN_RANGE_BT: {                                                                        // Check if an enemy is in range for a basic tower
            std::cout << "Notification received: Enemy in range for a basic tower" << std::endl;
            for (Tower* tower : towers) {
                for (Enemy* enemy : enemies) {
                    if(tower->getType() == "basic") {
                        if (tower->enemyInRange) {                                                                  // Check if an enemy is in range and initialize the projectile
                            for(int indexs : tower->getIndexOfEnemy()) {            
                                if (indexs == enemy->getIndex()) {
                                    cout << "basic shoot" << endl;
                                    Vector3 towerPosition = tower->getTowerPosition();
                                    towerPosition.y = 6.0f;
                                    Projectile* newProjectile = Projectile::createProjectile("basic", towerPosition, enemy->getEnemyPosition());
                                    projectiles.push_back(newProjectile);
                                }
                                else {
                                    cout << "Not in range" << endl;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case EventType::ENEMY_IN_RANGE_NT:{                                                                         // Check if an enemy is in range for a normal tower
            std::cout << "Notification received: Enemy in range for a normal tower" << std::endl;
            for (Tower* tower : towers) {
                for (Enemy* enemy : enemies) {
                    if(tower->getType() == "normal") {
                        if (tower->enemyInRange) {
                            for(int indexs : tower->getIndexOfEnemy()) {                                            // Check if the index is already in the array and if so, shoot
                                if (indexs == enemy->getIndex()) {
                                    cout << "basic shoot" << endl;
                                    Vector3 towerPosition = tower->getTowerPosition();
                                    towerPosition.y = 6.0f;
                                    Projectile* newProjectile = Projectile::createProjectile("basic", towerPosition, enemy->getEnemyPosition());
                                    projectiles.push_back(newProjectile);
                                }
                                else {
                                    cout << "Not in range" << endl;
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case EventType::ENEMY_IN_RANGE_ST: {                                                                        // Check if an enemy is in range for a slow tower
            std::cout << "Notification received: Enemy in range for a slow tower" << std::endl;
            for (Tower* tower : towers) {
                for (Enemy* enemy : enemies) {
                    if(tower->getType() == "slow") {
                        if (tower->enemyInRange) {
                            for(int indexs : tower->getIndexOfEnemy()) {            
                                if (indexs == enemy->getIndex()) {  
                                    if (!enemy->slowed) {
                                        enemy->setSpeed(enemy->getSpeed() * 0.5f);
                                        enemy->slowed = true;
                                        enemy->isChecked = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case EventType::ENEMY_OUT_OF_RANGE: {                                                                       // Check if an enemy is out of range for a slow tower and reset the speed
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
        }
        case EventType::GAME_CLOSE: {                                                                             // Check if the game is closed
            std::cout << "Notification received: Game close" << std::endl;
            menu.setGameState(GameState::MAIN_MENU);
            closeGame = true;
            break;
        }
        default:
            break;
    }
    
}

void GameManager::checkTowersForEnemies() {                                                                         // Function to check if an enemy is in range for a tower
    for (Tower* tower : towers) {
        tower->checkEnemyInRange(enemies);  
    }
}

void GameManager::spawnEnemy() {                                                                                    // Function to spawn an enemy based on the wave and enemy type
    if (enemiesToSpawn > 0) {
        enemyCount++;
        Enemy* Test1 = Enemy::createEnemy(enemyTypeToSpawn, Vector3{-25.0f, 0.0f, -10.0f}, enemyCount);
        Test1->setIndex(enemyCount);
        enemies.push_back(Test1);
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

int GameManager::getScore() const{                                                                                  // Function to get the score
    return score;
}

void GameManager::setDifficulty(string difficulty_chosen) {
    difficulty = difficulty_chosen;
}