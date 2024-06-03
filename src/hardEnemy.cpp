#include "hardEnemy.hpp"
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

HardEnemy::HardEnemy(Vector3 position) {
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy3.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;

    enemyPosition = position;
    speed = 0.1f;
    maxHealth = health = 100;
    isAlive = true;
    value = 300;
}
void HardEnemy::update(Camera camera) {
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void HardEnemy::move(const vector<Vector3>& path) {
    Enemy::move(path);
}

int HardEnemy::getEnemyValue() const{
    return value;
}

bool HardEnemy::hasReachedEnd(vector<Vector3>& path) const {
    return Enemy::hasReachedEnd(path);
}