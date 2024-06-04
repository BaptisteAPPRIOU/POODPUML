#include "enemy.hpp"
#include "basicEnemy.hpp"
#include "mediumEnemy.hpp"
#include "hardEnemy.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <raymath.h>
#include <iostream>
using namespace std;

Enemy* Enemy::createEnemy(const string& type, Vector3 position) {                                       // Create enemy based on type
    if (type == "basic") {
        return new BasicEnemy(position);
    } else if (type == "medium") {
        return new MediumEnemy(position);
    } else if (type == "hard") {
        return new HardEnemy(position);
    }
    return nullptr;
}

void Enemy::move(const std::vector<Vector3>& path) {                                                    // Move enemy along the path
    if (path.empty() || static_cast<std::vector<Vector3>::size_type>(currentPoint) >= path.size()) {    
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

Vector3 Enemy::getEnemyPosition() const {                                                               // Get enemy position                  
    return enemyPosition;
}

void Enemy::takeDamage(int damage) {                                                                    // Take damage
    health -= damage;
    cout << "Health: "<< health << endl;
    if (health <= 0) {
        isAlive = false;
    }
}

bool Enemy::isEnemyAlive() const {                                                                       // Check if enemy is alive                    
    return isAlive;
}

void Enemy::drawLifeBar(Camera camera) {                                                                // Draw life bar
    const float lifeBarFixedWidth = 2.0f;                                                               // Fixed total width in world units
    const float lifeBarHeight = 0.2f;                                                                   // Height in world units
    const float lifeBarDepth = 0.2f;                                                                    // Depth in world units

    float healthPercentage = (float)health / maxHealth;                                                 // Calculate health percentage based on max health

    Vector3 lifeBarPosition = Vector3Add(enemyPosition, Vector3{0, 4.5f, 0});                           // Calculate the position of the lifebar

    DrawCube(Vector3Add(lifeBarPosition, Vector3{0, 0, 0}), lifeBarFixedWidth, lifeBarHeight, lifeBarDepth, DARKGRAY);      // Draw background bar (full width, representing the max health)

    DrawCube(Vector3Add(lifeBarPosition, Vector3{-lifeBarFixedWidth * (1 - healthPercentage) / 2, 0, 0}), lifeBarFixedWidth * healthPercentage, lifeBarHeight, lifeBarDepth, GREEN);
}

void Enemy::setSpeed(float speed) {                                                                     // Set speed
    this->speed = speed;
}

float Enemy::getSpeed() {                                                                               // Get speed
    return speed;
}

int Enemy::getEnemyValue() const {                                                                      // Get enemy value                        
    return value;
}

bool Enemy::hasReachedEnd(std::vector<Vector3>& path) const {                                           // Check if enemy has reached the end of the path                    
    return static_cast<std::vector<Vector3>::size_type>(currentPoint) >= path.size();
}

Enemy::~Enemy() {}                                                                                      // Destructor