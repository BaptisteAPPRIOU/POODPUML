#include "normalProjectile.hpp"
#include <iostream>

NormalProjectile::NormalProjectile(Vector3 position, Vector3 targetPosition)
    : Projectile(position, targetPosition, 0.5f, 100) {
    projectileModel = LoadModel("assets/models/projectile1.obj");
    textureProjectile = LoadTexture("assets/textures/texture_projectile1.png");
    projectileModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureProjectile;
}

// BasicProjectile::~BasicProjectile() {
//     UnloadModel(projectileModel);
//     UnloadTexture(textureProjectile);
// }

void NormalProjectile::update() {
    Vector3 direction = Vector3Normalize(Vector3Subtract(targetPosition, position));
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;

    // std::cout << "Projectile Position: (" << position.x << ", " << position.y << ", " << position.z << ") "
    //           << "Target Position: (" << targetPosition.x << ", " << targetPosition.y << ", " << targetPosition.z << ")" << std::endl;
}

void NormalProjectile::draw() const {
    DrawModel(projectileModel, position, 1.0f, WHITE);
}