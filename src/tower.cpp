#include "tower.hpp"
#include "basicTower.hpp"
#include "normalTower.hpp"
#include "slowTower.hpp"
#include <iostream>
using namespace std;

Tower* Tower::createTower(const std::string& type, Vector3 position) {                                  // Function to create a tower   
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

void Tower::hoverTower(Vector3 position) {                                                              // Function to draw the hovering tower     
    DrawModel(tower, position, 1.0f, Fade(RED, 0.5f));
}

void Tower::draw(Vector3 towerPosition) {                                                               // Function to draw the tower  
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}

Vector3 Tower::getTowerPosition() {                                                                     // Function to get the position of the tower         
    return towerPosition;
}

string Tower::getType() {                                                                               // Function to get the type of the tower       
    return type;
}

int Tower::getCost() {                                                                                  // Function to get the cost of the tower      
    return cost;
}