#include "basicEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

BasicEnemy::BasicEnemy(Vector3 position) {
    enemy = LoadModel("assets/models/soldier1.obj");
    textureEnemy = LoadTexture("assets/textures/texture_soldier1.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;

    enemyPosition = position;
    speed = 0.05f;
    maxHealth = health = 500;
    isAlive = true;
    value = 100;
}

void BasicEnemy::update(Camera camera) {
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void BasicEnemy::move(const vector<Vector3>& path) {
    Enemy::move(path);
}

int BasicEnemy::getEnemyValue() const{
    return value;
}

bool BasicEnemy::hasReachedEnd(vector<Vector3>& path) const {
    return Enemy::hasReachedEnd(path);
}