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

void Tower::checkEnemyInRange(Vector3 enemyPosition) {
    float distance = Vector3Distance(towerPosition, enemyPosition);
    if (distance <= range) {
        if (!enemyInRange) {
            enemyInRange = true;
            Subject::notify(EventType::ENEMY_IN_RANGE);  // Notify observers
        }
    } 
    else if (distance > range) {
            enemyInRange = false;
            Subject::notify(EventType::ENEMY_OUT_OF_RANGE);  // Notify observers
        }
}

Vector3 Tower::getTowerPosition() {
    return towerPosition;
}

string Tower::getType() {
    return type;
}