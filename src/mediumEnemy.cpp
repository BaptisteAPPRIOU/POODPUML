#include "mediumEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

MediumEnemy::MediumEnemy(Vector3 position) {                                // Constructor for the medium enemy
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy2.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;

    enemyPosition = position;
    speed = 0.15f;
    maxHealth = health = 100;
    isAlive = true;
    value = 200;
}

void MediumEnemy::update(Camera camera) {                                   // Update the medium enemy
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void MediumEnemy::move(const std::vector<Vector3>& path) {                  // Move the medium enemy
    Enemy::move(path);
}

int MediumEnemy::getEnemyValue() const{                                     // Get the value of the medium enemy
    return value;
}

bool MediumEnemy::hasReachedEnd(vector<Vector3>& path) const {              // Check if the medium enemy has reached the end
    return Enemy::hasReachedEnd(path);
}

MediumEnemy::~MediumEnemy() {                                               // Destructor for the medium enemy
    UnloadModel(enemy);
    UnloadTexture(textureEnemy);
}