#include "basicTower.hpp"

BasicTower::BasicTower(Vector3 position) : Tower(position) {
    tower = LoadModel("assets/models/tower.obj");
    textureTower = LoadTexture("assets/textures/texture_tower.png");
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTower;
    range = 5.0f;
    damage = 10;
    fireRate = 1.0f;
    cost = 100;
}

void BasicTower::update() {
    Tower::update();  // Call base class update
    draw(towerPosition);
}

void BasicTower::shoot() {
    //shoot at enemy
}

void BasicTower::hoverTower(Vector3 position) {
    DrawModel(tower, position, 1.0f, Fade(WHITE, 0.5f));
}

void BasicTower::draw(Vector3 towerPosition) {
    DrawModel(tower, towerPosition, 1.0f, WHITE);
}