#include "normalProjectile.hpp"
#include <iostream>

NormalProjectile::NormalProjectile(Vector3 position, Vector3 targetPosition)                // Constructor for the normal projectile
    : Projectile(position, targetPosition, 0.5f, 100) {
    projectileModel = LoadModel("assets/models/projectile1.obj");
    textureProjectile = LoadTexture("assets/textures/texture_projectile1.png");
    projectileModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureProjectile;
}

NormalProjectile::~NormalProjectile() {}                                                    // Destructor for the normal projectile

void NormalProjectile::update() {                                                           // Update function to move the projectile towards the target
    Vector3 direction = Vector3Normalize(Vector3Subtract(targetPosition, position));
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;
}

void NormalProjectile::draw() const {                                                       // Draw function to draw the projectile
    DrawModel(projectileModel, position, 1.0f, WHITE);
}