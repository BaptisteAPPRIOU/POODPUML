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
}

void BasicTower::update() {
    Tower::update();  // Call base class update
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

bool BasicTower::isEnemyInRange(const Vector3& enemyPosition) const {
    float distance = Vector3Distance(towerPosition, enemyPosition);
    return distance <= range;
}

// void BasicTower::onNotify() {
//     notify();
//     enemyInRange = true;
// }