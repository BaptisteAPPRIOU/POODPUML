#include "normalTower.hpp"
#include <iostream>

NormalTower::NormalTower(Vector3 position) : Tower(position)  {                                         // Constructor for the normal tower
    tower = LoadModel("assets/models/normalTower.obj");
    textureTower = LoadTexture("assets/textures/texture_normalTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 5.0f;
    cost = 400;
    enemyInRange = false;
    type = "normal";
}

void NormalTower::update() {                                                                            // Update the normal tower     
    draw(towerPosition);
}

void NormalTower::hoverTower(Vector3 position) {                                                        // Function to draw the hovering tower      
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void NormalTower::draw(Vector3 towerPosition) {                                                        // Function to draw the normal tower     
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

void NormalTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {                               // Function to check if an enemy is in range
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
                Subject::notify(EventType::ENEMY_IN_RANGE_NT);
                std::cout << "Firing projectile!" << std::endl;
                timer = 0.0f;
            }
            return;
        }
        deleteIndexOfEnemy(enemy->getIndex());
    }
    enemyInRange = false;
    timer = 0.0f;
    Subject::notify(EventType::ENEMY_OUT_OF_RANGE);
}

NormalTower::~NormalTower() {                                                                           // Destructor for the normal tower                
    UnloadModel(tower); 
    UnloadTexture(textureTower); 
}

Vector3 NormalTower::getTowerPosition() {                                                               // Get the position of the tower            
    return towerPosition;
}

string NormalTower::getType() {                                                                         // Get the type of the tower         
    return type;
}

float NormalTower::getFireRate() {                                                                      // Get the fire rate of the tower            
    return fireRate;
}

int NormalTower::getCost() {                                                                            // Get the cost of the tower        
    return cost;
}

vector<int> NormalTower::getIndexOfEnemy() {                                                            // Get the index of the enemy           
    return index_to_shoot;
}

void NormalTower::addIndexOfEnemy(int index) {                                                          // Add the index of the enemy to the vector
    index_to_shoot.push_back(index);
}

void NormalTower::deleteIndexOfEnemy(int index_to_delete) {                                             // Delete the index of the enemy from the vector
    for (int indexs : index_to_shoot) {
        if (indexs == index_to_delete) {
            index_to_shoot.erase(std::remove(index_to_shoot.begin(), index_to_shoot.end(), index_to_delete), index_to_shoot.end());
        }
    }
}

void NormalTower::resetIndexOfEnemy() {                                                                 // Reset the index of the enemy vector
    index_to_shoot.clear();
}