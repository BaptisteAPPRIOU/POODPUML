#include "basicTower.hpp"
// #include "projectile.hpp"
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

void BasicTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {         // Function to check if an enemy is in range
    for (Enemy* enemy : enemies) {
        Vector3 enemyPosition = enemy->getEnemyPosition();
        float distance = Vector3Distance(enemyPosition, towerPosition);
        if (distance <= range) {
            enemyInRange = true;
            timer += GetFrameTime();  // Increment the timer by the frame time
            addIndexOfEnemy(enemy->getIndex());
            if (timer >= getFireRate()) {
                Subject::notify(EventType::ENEMY_IN_RANGE);  // Notify observers to fire
                std::cout << "Firing projectile!" << std::endl;  // Debug print
                timer = 0.0f;  // Reset the timer after firing
            }
            return; // Exit the loop if any enemy is in range
        }
    }
    // If no enemy is in range
    enemyInRange = false;
    timer = 0.0f;  // Reset the timer if the enemy is out of range
    Subject::notify(EventType::ENEMY_OUT_OF_RANGE);  // Notify observers that the enemy is out of range
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