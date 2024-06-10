#include "mediumEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

MediumEnemy::MediumEnemy(Vector3 position, int index_chosen) {                                  // Constructor for the medium enemy
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_mediumEnemy.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;
    index = 0;
    enemyPosition = position;
    speed = 0.07f;
    maxHealth = health = 300;
    isAlive = true;
    value = 200;
}

void MediumEnemy::update(Camera camera) {                                                       // Update the medium enemy
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void MediumEnemy::move(const std::vector<Vector3>& path) {                                      // Move the medium enemy
    Enemy::move(path);
}

int MediumEnemy::getEnemyValue() const{                                                         // Get the value of the medium enemy
    return value;
}

bool MediumEnemy::hasReachedEnd(vector<Vector3>& path) const {                                  // Check if the medium enemy has reached the end
    return Enemy::hasReachedEnd(path);
}

int MediumEnemy::getIndex() const {                                                             // Get the index of the enemy
    return index;
}

void MediumEnemy::setIndex(int index) {                                                         // Set the index of the enemy
    this->index = index;
}