#include "basicEnemy.hpp"
#include <raylib.h>
#include <vector>

BasicEnemy::BasicEnemy(Vector3 position) {
    enemy = LoadModel("assets/models/enemy.obj");
    textureEnemy = LoadTexture("assets/textures/texture_enemy.png");
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

void BasicEnemy::move(const std::vector<Vector3>& path) {
    Enemy::move(path);
}

