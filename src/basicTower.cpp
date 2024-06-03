#include "basicTower.hpp"
// #include "projectile.hpp"
#include <iostream>

BasicTower::BasicTower(Vector3 position) : Tower(position) {
    tower = LoadModel("assets/models/basicTower.obj");
    textureTower = LoadTexture("assets/textures/texture_basicTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 10.0f;
    cost = 200;
    enemyInRange = false;
    type = "basic";
    timer = 0.0f;
}

void BasicTower::update() {
    Tower::update();
    draw(towerPosition);
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

void BasicTower::checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 enemyPosition) {
    Tower::checkEnemyInRange(enemies, enemyPosition);
}

BasicTower::~BasicTower() {
    UnloadModel(tower); // Unload tower model
    UnloadTexture(textureTower); // Unload tower texture
    // if (projectile) {
    //     delete projectile; // Delete projectile object
    // }
}

Vector3 BasicTower::getTowerPosition() {
    return towerPosition;
}

string BasicTower::getType() {
    return type;
}

float BasicTower::getFireRate() {
    return 2.0f;
}

int BasicTower::getCost() {
    return cost;
}