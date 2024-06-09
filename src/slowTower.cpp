#include "slowTower.hpp"
#include <iostream>

SlowTower::SlowTower(Vector3 position) : Tower(position) {                                              // Constructor for the slow tower class             
    tower = LoadModel("assets/models/slowTower.obj");
    textureTower = LoadTexture("assets/textures/texture_slowTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 15.0f;
    cost = 500;
    enemyInRange = false;
    type = "slow";
}

void SlowTower::update() {                                                                              // Update the slow tower      
    draw(towerPosition);
}

void SlowTower::hoverTower(Vector3 position) {                                                          // Function to draw the hovering tower        
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void SlowTower::draw(Vector3 towerPosition) {                                                           // Function to draw the slow tower      
    DrawModel(tower, towerPosition, 1.0f, WHITE);
    Vector3 adjustedPosition = towerPosition;
    adjustedPosition.z += 0.4f; 
    DrawCircle3D(
        Vector3{adjustedPosition.x, towerPosition.y + 0.4f, adjustedPosition.z}, 
        range, 
        Vector3{1, 0, 0}, 
        90.0f, 
        RED
    );
}

void SlowTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {                                 // Function to check if an enemy is in range
    for (Enemy* enemy : enemies) {
        Vector3 enemyPosition = enemy->getEnemyPosition();
        float distance = Vector3Distance(enemyPosition, towerPosition);
        if (distance <= range) {                                                                        // If the enemy is in range of the tower check if the tower can shoot the enemy and notify the subject
            enemyInRange = true;
            timer += GetFrameTime();  
            if (timer >= getFireRate()) {
                if (std::find(index_to_shoot.begin(), index_to_shoot.end(), enemy->getIndex()) == index_to_shoot.end()) {
                    addIndexOfEnemy(enemy->getIndex());
                }
                cout << "Index size dans le check " << getIndexOfEnemy().size() << endl;
                Subject::notify(EventType::ENEMY_IN_RANGE_ST);
                std::cout << "Firing projectile!" << std::endl;
                timer = 0.0f;
            }
            continue;
        }
        deleteIndexOfEnemy(enemy->getIndex());
    }
    enemyInRange = false;
    timer = 0.0f;
    Subject::notify(EventType::ENEMY_OUT_OF_RANGE);
}

SlowTower::~SlowTower() {                                                                               // Destructor for the slow tower           
    UnloadModel(tower); 
    UnloadTexture(textureTower); 
}

Vector3 SlowTower::getTowerPosition() {                                                                 // Get the position of the tower
    return towerPosition;
}

string SlowTower::getType() {                                                                           // Get the type of the tower               
    return type;
}

float SlowTower::getFireRate() {                                                                        // Get the fire rate of the tower           
    return fireRate;
}

int SlowTower::getCost() {                                                                              // Get the cost of the tower          
    return cost;
}

vector<int> SlowTower::getIndexOfEnemy() {                                                              // Get the index of the enemy
    return index_to_shoot;
}

void SlowTower::addIndexOfEnemy(int index) {                                                            // Add the index of the enemy
    index_to_shoot.push_back(index);
}

void SlowTower::deleteIndexOfEnemy(int index_to_delete) {                                               // Delete the index of the enemy           
    for (int indexs : index_to_shoot) {
        if (indexs == index_to_delete) {
            index_to_shoot.erase(std::remove(index_to_shoot.begin(), index_to_shoot.end(), index_to_delete), index_to_shoot.end());
        }
    }
}

void SlowTower::resetIndexOfEnemy() {                                                                   // Reset the index of the enemy            
    index_to_shoot.clear();
}