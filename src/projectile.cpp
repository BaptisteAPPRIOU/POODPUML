#include "projectile.hpp"
#include "basicProjectile.hpp"

Projectile::Projectile(Vector3 position, Vector3 targetPosition, float speed, int damage)
    : position(position), targetPosition(targetPosition), speed(speed), damage(damage) {}

Vector3 Projectile::getPosition() const {
    return position;
}

int Projectile::getDamage() const {
    return damage;
}

Projectile* Projectile::createProjectile(const std::string& type, Vector3 position, Vector3 targetPosition) {
    if (type == "basic") {
        return new BasicProjectile(position, targetPosition);
    }
    return nullptr;
}