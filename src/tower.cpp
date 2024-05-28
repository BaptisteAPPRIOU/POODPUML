#include "tower.hpp"
#include "basicTower.hpp"

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
        shoot(enemyPosition);
    //     fireCountdown = 1.0f / fireRate;
    // }
}

void Tower::shoot(Vector3 enemyPosition) {
    //shoot at enemy
}

void Tower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(RED, 0.5f));
}

void Tower::draw(Vector3 towerPosition) {
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}