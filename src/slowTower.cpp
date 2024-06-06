#include "slowTower.hpp"
#include <iostream>

SlowTower::SlowTower(Vector3 position) : Tower(position) {
    tower = LoadModel("assets/models/slowTower.obj");
    textureTower = LoadTexture("assets/textures/texture_slowTower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 15.0f;
    cost = 500;
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

void SlowTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {
    cout << "Checking enemy in range" << endl;
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
    return fireRate;
}

int SlowTower::getCost() {
    return cost;
}

vector<int> SlowTower::getIndexOfEnemy() {
    return index_to_shoot;
}

void SlowTower::addIndexOfEnemy(int index) {
    index_to_shoot.push_back(index);
}

void SlowTower::deleteIndexOfEnemy(int index_to_delete) {
    for (int indexs : index_to_shoot) {
        if (indexs == index_to_delete) {
            index_to_shoot.erase(std::remove(index_to_shoot.begin(), index_to_shoot.end(), index_to_delete), index_to_shoot.end());
        }
    }
}

void SlowTower::resetIndexOfEnemy() {
    index_to_shoot.clear();
}