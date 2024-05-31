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
    speed = 0.5f;
    health = 100;
    isAlive = true;
    value = 100;
}
void HardEnemy::update(Camera camera) {
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
    drawLifeBar(camera);
}

void HardEnemy::move(const vector<Vector3>& path) {
    Enemy::move(path);
}