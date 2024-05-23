#include "mediumEnemy.hpp"
#include <raylib.h>
#include <vector>

MediumEnemy::MediumEnemy(Vector3 position) {
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy2.png");
    enemy.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureEnemy;

    enemyPosition = position;
    speed = 0.15f;
    health = 100;
    isAlive = true;
    value = 100;
}
void MediumEnemy::update() {
    DrawModel(enemy, enemyPosition, 1.0f, WHITE);
}

void MediumEnemy::move(const std::vector<Vector2>& path) {
    Enemy::move(path);
}