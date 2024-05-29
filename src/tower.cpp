#include "tower.hpp"
#include "basicTower.hpp"
#include <iostream>
using namespace std;

Tower* Tower::createTower(const std::string& type, Vector3 position) {
    if (type == "basic") {
        return new BasicTower(position);
    }
    return nullptr;
}

void Tower::update() {
    //add observer to calculate distance between tower and enemy
    // fireCountdown -= GetFrameTime();
    // if (fireCountdown <= 0) {
        // shoot(enemyPosition);
    //     fireCountdown = 1.0f / fireRate;
    // }
}

// void Tower::shoot(Vector3 enemyPosition) {
//     //shoot at enemy
// }

void Tower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(RED, 0.5f));
}

void Tower::draw(Vector3 towerPosition) {
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}

void Tower::checkEnemyInRange(Vector3 enemyPosition) {
    float distance = Vector3Distance(towerPosition, enemyPosition);
    cout << "Checking enemy in range. Tower Position: (" << towerPosition.x << ", " << towerPosition.y << ", " << towerPosition.z 
              << "), Enemy Position: (" << enemyPosition.x << ", " << enemyPosition.y << ", " << enemyPosition.z 
              << "), Distance: " << distance << ", Range: " << range << endl;
    if (distance <= range) {
        if (!enemyInRange) {
            enemyInRange = true;
            Subject::notify(EventType::ENEMY_IN_RANGE);  // Notify observers
        }
    } else {
        enemyInRange = false;
    }
}

Vector3 Tower::getTowerPosition() {
    return towerPosition;
}