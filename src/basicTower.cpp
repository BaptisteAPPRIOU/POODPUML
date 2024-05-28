#include "basicTower.hpp"
#include <iostream>

BasicTower::BasicTower(Vector3 position) : Tower(position) {
    tower = LoadModel("assets/models/tower.obj");
    textureTower = LoadTexture("assets/textures/texture_tower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 10.0f;
    damage = 10;
    fireRate = 1.0f;
    cost = 100;
    enemyInRange = false;
}

void BasicTower::update() {
    if (enemyInRange) {
        shoot();
    }
    draw(towerPosition);
}

void BasicTower::shoot() {
    cout << "Basic Tower shooting" << endl;
    //shoot at enemy
}

void BasicTower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void BasicTower::draw(Vector3 towerPosition) {
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

void BasicTower::checkEnemyInRange(Vector3 enemyPosition) {
    float distance = Vector3Distance(towerPosition, enemyPosition);
    std::cout << "Checking enemy in range. Tower Position: (" << towerPosition.x << ", " << towerPosition.y << ", " << towerPosition.z 
              << "), Enemy Position: (" << enemyPosition.x << ", " << enemyPosition.y << ", " << enemyPosition.z 
              << "), Distance: " << distance << ", Range: " << range << std::endl;
    if (distance <= range) {
        if (!enemyInRange) {
            enemyInRange = true;
            Subject::notify(EventType::ENEMY_IN_RANGE);  // Qualify notify with Subject
        }
    } else {
        enemyInRange = false;
    }
}