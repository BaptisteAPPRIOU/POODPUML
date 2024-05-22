#include "enemy.hpp"
#include "basicEnemy.hpp"
#include <vector>
#include <cmath>

Enemy* Enemy::createEnemy(const std::string& type, Vector3 position) {
    if (type == "basic") {
        return new BasicEnemy(position);
    }
    return nullptr;
}

void Enemy::move(const std::vector<Vector2>& path) {
    if (path.empty() || currentPoint >= path.size()) {
        return;
    }

    Vector2 target = path[currentPoint];
    Vector2 direction = { target.x - enemyPosition.x, target.y - enemyPosition.z };

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }

    enemyPosition.x += direction.x * speed;
    enemyPosition.z += direction.y * speed;

    if (std::fabs(enemyPosition.x - target.x) < 0.1f && std::fabs(enemyPosition.z - target.y) < 0.1f) {
        currentPoint++;
    }
}