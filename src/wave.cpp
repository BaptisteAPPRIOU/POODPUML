#include "wave.hpp"
#include "enemy.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;

Wave::Wave(const string& enemyType, const Vector3& startPosition, int enemyCount, const vector<Vector2> path)
    : path(path) {
    for (int i = 0; i < enemyCount; ++i) {
        enemies.push_back(Enemy::createEnemy(enemyType, startPosition));
    }
}

Wave::~Wave() {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void Wave::update() {
    for (auto enemy : enemies) {
        enemy->update();
        enemy->move(path);
    }
}