#include "enemy.hpp"
#include "basicEnemy.hpp"
#include "mediumEnemy.hpp"
#include "hardEnemy.hpp"
#include <vector>
#include <cmath>
using namespace std;

Enemy* Enemy::createEnemy(const string& type, Vector3 position) {
    if (type == "basic") {
        return new BasicEnemy(position);
    } else if (type == "medium") {
        return new MediumEnemy(position);
    } else if (type == "hard") {
        return new HardEnemy(position);
    }
    return nullptr;
}

void Enemy::move(const vector<Vector2>& path) {
    if (path.empty() || currentPoint >= static_cast<int>(path.size())) {
        return;
    }

    Vector2 target = path[currentPoint];
    Vector2 direction = { target.x - enemyPosition.x, target.y - enemyPosition.z };

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }

    enemyPosition.x += direction.x * speed;
    enemyPosition.z += direction.y * speed;

    if (fabs(enemyPosition.x - target.x) < 0.1f && fabs(enemyPosition.z - target.y) < 0.1f) {
        currentPoint++;
    }
}