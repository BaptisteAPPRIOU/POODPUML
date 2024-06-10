#include "projectile.hpp"
#include "basicProjectile.hpp"
#include "normalProjectile.hpp"

Projectile::Projectile(Vector3 position, Vector3 targetPosition, float speed, int damage)               // Constructor for the projectile class
    : position(position), targetPosition(targetPosition), speed(speed), damage(damage) {}

Vector3 Projectile::getPosition() const {                                                               // Function to get the position of the projectile    
    return position;
}

int Projectile::getDamage() const {                                                                     // Function to get the damage of the projectile          
    return damage;
}

Projectile* Projectile::createProjectile(const std::string& type, Vector3 position, Vector3 targetPosition) {   // Function to create a projectile
    if (type == "basic") {
        return new BasicProjectile(position, targetPosition);
    }
    else if (type == "normal") {
        return new NormalProjectile(position, targetPosition);
    }
    return nullptr;
}