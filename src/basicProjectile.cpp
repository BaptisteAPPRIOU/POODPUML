#include "basicProjectile.hpp"
#include <iostream>

BasicProjectile::BasicProjectile(Vector3 position, Vector3 targetPosition)                                  // Constructor
    : Projectile(position, targetPosition, 1.0f, 50) {
    projectileModel = LoadModel("assets/models/projectile.obj");
    textureProjectile = LoadTexture("assets/textures/texture_projectile.png");
    projectileModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureProjectile;
}

// BasicProjectile::~BasicProjectile() {                                                                       // Destructor          
//     UnloadModel(projectileModel);
//     UnloadTexture(textureProjectile);
// }

void BasicProjectile::update() {                                                                            // Update function to move the projectile towards the target
    Vector3 direction = Vector3Normalize(Vector3Subtract(targetPosition, position));
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;
}

void BasicProjectile::draw() const {                                                                        // Draw function to draw the projectile
    DrawModel(projectileModel, position, 1.0f, WHITE);
}