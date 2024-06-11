#include "hardEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

HardEnemy::HardEnemy(Vector3 position, int index_chosen) {                                    // Constructor for the hard enemy
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy3.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;
    index = 0;
    enemyPosition = position;
    speed = 0.1f;
    maxHealth = health = 100;
    isAlive = true;
    value = 300;
}

void HardEnemy::update(Camera camera) {                                     // Update the hard enemy
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void HardEnemy::move(const vector<Vector3>& path) {                         // Move the hard enemy
    Enemy::move(path);
}

int HardEnemy::getEnemyValue() const{                                       // Get the value of the hard enemy
    return value;
}

bool HardEnemy::hasReachedEnd(vector<Vector3>& path) const {                // Check if the hard enemy has reached the end
    return Enemy::hasReachedEnd(path);
}

int HardEnemy::getIndex() const {                                           // Get the index of the hard enemy
    return index;
}

void HardEnemy::setIndex(int index) {                                       // Set the index of the hard enemy
    this->index = index;
}
