#include "normalTower.hpp"
// #include "projectile.hpp"
#include <iostream>

NormalTower::NormalTower(Vector3 position) : Tower(position)  {
    tower = LoadModel("assets/models/normalTower.obj");
    textureTower = LoadTexture("assets/textures/texture_normalTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 5.0f;
    cost = 400;
    enemyInRange = false;
    type = "normal";
}

void NormalTower::update() {
    draw(towerPosition);
}

void NormalTower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void NormalTower::draw(Vector3 towerPosition) {
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

void NormalTower::checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 enemyPosition) {
    Tower::checkEnemyInRange(enemies, enemyPosition);
}

NormalTower::~NormalTower() {
    UnloadModel(tower); // Unload tower model
    UnloadTexture(textureTower); // Unload tower texture
}

Vector3 NormalTower::getTowerPosition() {
    return towerPosition;
}

string NormalTower::getType() {
    return type;
}

float NormalTower::getFireRate() {
    return fireRate;
}

int NormalTower::getCost() {
    return cost;
}