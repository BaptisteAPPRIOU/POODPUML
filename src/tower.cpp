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
    float distance = Vector3Distance(enemyPosition, towerPosition);
    cout <<"distance: "<< distance << " range: " << range << endl;
    if (distance <= range) {
        cout << "Enemy in range!" << endl;
        enemyInRange = true;
        timer += GetFrameTime();  // Increment the timer by the frame time

        if (timer >= getFireRate()) {
            cout << "Firing projectile!" << endl;
            Subject::notify(EventType::ENEMY_IN_RANGE);  // Notify observers to fire
            std::cout << "Firing projectile!222" << std::endl;  // Debug print
            timer = 0.0f;  // Reset the timer after firing
        }
    } else {
        cout << "Enemy out of range!22222" << endl;
        enemyInRange = false;
        timer = 0.0f;  // Reset the timer if the enemy is out of range
        Subject::notify(EventType::ENEMY_OUT_OF_RANGE);  // Notify observers that the enemy is out of range
    }
}

Vector3 Tower::getTowerPosition() {
    return towerPosition;
}

string Tower::getType() {
    return type;
}

