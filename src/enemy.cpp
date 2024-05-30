#include "enemy.hpp"
#include "basicEnemy.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <raymath.h>

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
    if (health <= 0) {
        isAlive = false;
    }
}

bool Enemy::isEnemyAlive() const {
    return isAlive;
}