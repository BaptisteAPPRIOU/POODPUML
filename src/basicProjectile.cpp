#include "basicProjectile.hpp"

BasicProjectile::BasicProjectile(Vector3 position, Vector3 targetPosition)
    : Projectile(position, targetPosition, 0.1f, 100) {
    projectile = LoadModel("assets/models/projectile.obj");
    textureProjectile = LoadTexture("assets/textures/texture_projectile.png");
    projectile.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureProjectile;
}

void BasicProjectile::update() {
    Vector3 direction = Vector3Normalize(Vector3Subtract(targetPosition, position));
    position.x += direction.x * speed;
    position.y += direction.y * speed;
    position.z += direction.z * speed;
}

void BasicProjectile::draw(){
    DrawModel(projectile, position, 1.0f, WHITE);
}
