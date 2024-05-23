#include "hardEnemy.hpp"
#include <raylib.h>
#include <vector>
using namespace std;

HardEnemy::HardEnemy(Vector3 position) {
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;

    enemyPosition = position;
    speed = 0.5f;
    health = 100;
    isAlive = true;
    value = 100;
}
void HardEnemy::update() {
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
}

void HardEnemy::move(const vector<Vector2>& path) {
    Enemy::move(path);
}