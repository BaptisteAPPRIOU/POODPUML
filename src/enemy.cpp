#include "enemy.hpp"
#include "basicEnemy.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <raymath.h>
#include <iostream>
using namespace std;

Enemy* Enemy::createEnemy(const std::string& type, Vector3 position) {
    if (type == "basic") {
        return new BasicEnemy(position);
    }
    return nullptr;
}

void Enemy::move(const std::vector<Vector3>& path) {
    if (path.empty() || currentPoint >= path.size()) {
        return;
    }

    Vector3 target = path[currentPoint];
    Vector3 direction = Vector3Subtract(target, enemyPosition);

    float length = Vector3Length(direction);
    if (length > 0) {
        direction = Vector3Scale(direction, speed / length);
    }

    enemyPosition = Vector3Add(enemyPosition, direction);

    if (Vector3Distance(enemyPosition, target) < 0.1f) {
        currentPoint++;
    }
}

Vector3 Enemy::getEnemyPosition() const {
    return enemyPosition;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    cout << "Health: "<< health << endl;
    if (health <= 0) {
        isAlive = false;
    }
}

bool Enemy::isEnemyAlive() const {
    return isAlive;
}

void Enemy::drawLifeBar(Camera camera) {
    // Define constants
    const float lifeBarFixedWidth = 2.0f; // Fixed total width in world units
    const float lifeBarHeight = 0.2f; // Height in world units
    const float lifeBarDepth = 0.2f; // Depth in world units

    // Calculate health percentage
    float healthPercentage = (float)health / maxHealth; // Calculate health percentage based on max health

    // Calculate the position of the lifebar
    Vector3 lifeBarPosition = Vector3Add(enemyPosition, Vector3{0, 2.5f, 0});

    // Draw background bar (full width, representing the max health)
    DrawCube(Vector3Add(lifeBarPosition, Vector3{0, 0, 0}), lifeBarFixedWidth, lifeBarHeight, lifeBarDepth, DARKGRAY);

    // Draw foreground (health) bar (width adjusted by health percentage within the fixed width)
    DrawCube(Vector3Add(lifeBarPosition, Vector3{-lifeBarFixedWidth * (1 - healthPercentage) / 2, 0, 0}), lifeBarFixedWidth * healthPercentage, lifeBarHeight, lifeBarDepth, GREEN);
}

void Enemy::setSpeed(float speed) {
    this->speed = speed;
}

float Enemy::getSpeed() {
    return speed;
}