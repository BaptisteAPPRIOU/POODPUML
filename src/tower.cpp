#include "tower.hpp"
#include "basicTower.hpp"
#include "normalTower.hpp"
#include "slowTower.hpp"
#include <iostream>
using namespace std;

Tower* Tower::createTower(const std::string& type, Vector3 position) {
    if (type == "basic") {
        return new BasicTower(position);
    }
    else if (type == "normal") {
        return new NormalTower(position);
    }
    else if (type == "slow") {
        return new SlowTower(position);
    }
    return nullptr;
}

void Tower::update() {
}

void Tower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(RED, 0.5f));
}

void Tower::draw(Vector3 towerPosition) {
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}

void Tower::checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 ) {
    for (Enemy* enemy : enemies) {
        Vector3 enemyPosition = enemy->getEnemyPosition();
        float distance = Vector3Distance(enemyPosition, towerPosition);
        if (distance <= range) {
            enemyInRange = true;
            timer += GetFrameTime();  // Increment the timer by the frame time

            if (timer >= getFireRate()) {
                Subject::notify(EventType::ENEMY_IN_RANGE);  // Notify observers to fire
                std::cout << "Firing projectile!" << std::endl;  // Debug print
                timer = 0.0f;  // Reset the timer after firing
            }
            return; // Exit the loop if any enemy is in range
        }
    }
    // If no enemy is in range
    enemyInRange = false;
    timer = 0.0f;  // Reset the timer if the enemy is out of range
    Subject::notify(EventType::ENEMY_OUT_OF_RANGE);  // Notify observers that the enemy is out of range
}


Vector3 Tower::getTowerPosition() {
    return towerPosition;
}

string Tower::getType() {
    return type;
}

