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
    fireCountdown -= GetFrameTime();
    if (fireCountdown <= 0) {
        shoot();
        fireCountdown = 1.0f / fireRate;
    }
}

void Tower::shoot() {
    //shoot at enemy
}
