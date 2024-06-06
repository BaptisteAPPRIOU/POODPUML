#include "normalTower.hpp"
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

void NormalTower::checkEnemyInRange(const std::vector<Enemy*>& enemies) {
    cout << "Checking enemy in range" << endl;
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

vector<int> NormalTower::getIndexOfEnemy() {
    return index_to_shoot;
}

void NormalTower::addIndexOfEnemy(int index) {
    index_to_shoot.push_back(index);
}

void NormalTower::deleteIndexOfEnemy(int index_to_delete) {
    for (int indexs : index_to_shoot) {
        if (indexs == index_to_delete) {
            index_to_shoot.erase(std::remove(index_to_shoot.begin(), index_to_shoot.end(), index_to_delete), index_to_shoot.end());
        }
    }
}

void NormalTower::resetIndexOfEnemy() {
    index_to_shoot.clear();
}