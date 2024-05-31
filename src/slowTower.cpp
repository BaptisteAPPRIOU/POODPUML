#include "slowTower.hpp"
// #include "projectile.hpp"
#include <iostream>

SlowTower::SlowTower(Vector3 position) : Tower(position) {
    tower = LoadModel("assets/models/tower2.obj");
    textureTower = LoadTexture("assets/textures/texture_tower2.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 15.0f;
    cost = 100;
    enemyInRange = false;
    type = "slow";
}

void SlowTower::update() {
    draw(towerPosition);
}

void SlowTower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void SlowTower::draw(Vector3 towerPosition) {
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

void SlowTower::checkEnemyInRange(Vector3 enemyPosition) {
    Tower::checkEnemyInRange(enemyPosition);
}

SlowTower::~SlowTower() {
    UnloadModel(tower); // Unload tower model
    UnloadTexture(textureTower); // Unload tower texture
}

Vector3 SlowTower::getTowerPosition() {
    return towerPosition;
}

string SlowTower::getType() {
    return type;
}

float SlowTower::getFireRate() {
    return __FLT_MAX__;
}