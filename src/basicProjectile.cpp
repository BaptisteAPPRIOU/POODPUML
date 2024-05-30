#include "basicProjectile.hpp"
#include <iostream>

BasicProjectile::BasicProjectile(Vector3 position, Vector3 targetPosition)
    : Projectile(position, targetPosition, 1.0f, 100) {
    projectileModel = LoadModel("assets/models/projectile.obj");
    textureProjectile = LoadTexture("assets/textures/texture_projectile.png");
    projectileModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureProjectile;
}

// BasicProjectile::~BasicProjectile() {
//     UnloadModel(projectileModel);
//     UnloadTexture(textureProjectile);
// }

void BasicProjectile::update() {
    Vector3 direction = Vector3Normalize(Vector3Subtract(targetPosition, position));
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;

    std::cout << "Projectile Position: (" << position.x << ", " << position.y << ", " << position.z << ") "
              << "Target Position: (" << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << ")" << std::endl;
}

void BasicProjectile::draw() const {
    DrawModel(projectileModel, position, 1.0f, WHITE);
}