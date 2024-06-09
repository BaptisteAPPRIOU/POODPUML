#include "basicTower.hpp"
#include <iostream>

BasicTower::BasicTower(Vector3 position) : Tower(position) {                                            // Constructor
    tower = LoadModel("assets/models/basicTower.obj");
    textureTower = LoadTexture("assets/textures/texture_basicTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 10.0f;
    cost = 200;
    enemyInRange = false;
    type = "basic";
    timer = 0.0f;
}

void BasicTower::update() {                                                                             // Update function
    Tower::update();
    draw(towerPosition);
}

void BasicTower::hoverTower(Vector3 position) {                                                         // Function to draw the hovering tower
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void BasicTower::draw(Vector3 towerPosition) {                                                          // Function to draw the tower
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

void BasicTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {                                // Function to check if an enemy is in range
    for (Enemy* enemy : enemies) {
        Vector3 enemyPosition = enemy->getEnemyPosition();
        float distance = Vector3Distance(enemyPosition, towerPosition);
        if (distance <= range) {
            enemyInRange = true;
            timer += GetFrameTime();  
            if (timer >= getFireRate()) {
                if (std::find(index_to_shoot.begin(), index_to_shoot.end(), enemy->getIndex()) == index_to_shoot.end()) {
                    addIndexOfEnemy(enemy->getIndex());
                }
                cout << "Index size dans le check " << getIndexOfEnemy().size() << endl;
                Subject::notify(EventType::ENEMY_IN_RANGE_BT);
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

BasicTower::~BasicTower() {                                                                             // Destructor
    UnloadModel(tower); // Unload tower model
    UnloadTexture(textureTower); // Unload tower texture
}

Vector3 BasicTower::getTowerPosition() {                                                                // Function to get the tower position
    return towerPosition;
}

string BasicTower::getType() {                                                                          // Function to get the tower type
    return type;
}

float BasicTower::getFireRate() {                                                                       // Function to get the tower fire rate
    return fireRate;
}

int BasicTower::getCost() {                                                                             // Function to get the tower cost
    return cost;
}

vector<int> BasicTower::getIndexOfEnemy() {
    return index_to_shoot;
}

void BasicTower::addIndexOfEnemy(int index) {
    index_to_shoot.push_back(index);
}

void BasicTower::deleteIndexOfEnemy(int index_to_delete) {
    for (int indexs : index_to_shoot) {
        if (indexs == index_to_delete) {
            index_to_shoot.erase(std::remove(index_to_shoot.begin(), index_to_shoot.end(), index_to_delete), index_to_shoot.end());
        }
    }
}

void BasicTower::resetIndexOfEnemy() {
    index_to_shoot.clear();
}