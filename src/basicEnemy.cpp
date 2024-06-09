#include "basicEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

BasicEnemy::BasicEnemy(Vector3 position, int index_chosen) {                                                  // Constructor
    enemy = LoadModel("assets/models/basicEnemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_basicEnemy.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;
    index = 0;
    enemyPosition = position;
    speed = 0.05f;
    maxHealth = health = 500;
    isAlive = true;
    value = 100;
}

void BasicEnemy::update(Camera camera) {                                                    // Update function            
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void BasicEnemy::move(const vector<Vector3>& path) {                                        // Move function along a path
    Enemy::move(path);
}

int BasicEnemy::getEnemyValue() const{                                                      // Get the value of the enemy to update the score and money
    return value;
}

bool BasicEnemy::hasReachedEnd(vector<Vector3>& path) const {                               // Check if the enemy has reached the end of the path
    return Enemy::hasReachedEnd(path);
}

int BasicEnemy::getIndex() const {                                                          // Get the index of the enemy
    return index;
}

void BasicEnemy::setIndex(int index) {                                                      // Set the index of the enemy
    this->index = index;
}