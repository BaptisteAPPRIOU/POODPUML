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

Vector3 Tower::getTowerPosition() {
    return towerPosition;
}

string Tower::getType() {
    return type;
}

int Tower::getCost() {
    return cost;
}
