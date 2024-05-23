#include "basicTower.hpp"

BasicTower::BasicTower(Vector3 position) : Tower(position) {
    range = 5.0f;
    damage = 10;
    fireRate = 1.0f;
    cost = 100;
}

void BasicTower::update() {
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}

void BasicTower::shoot() {
    //shoot at enemy
}
