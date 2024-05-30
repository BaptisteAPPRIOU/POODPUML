#ifndef NORMAL_PROJECTILE_HPP
#define NORMAL_PROJECTILE_HPP

#include "projectile.hpp"

class NormalProjectile : public Projectile {
public:
    NormalProjectile(Vector3 position, Vector3 targetPosition);
    // ~BasicProjectile();

    void update() override;
    void draw() const override;

private:
    Model projectileModel;
    Texture2D textureProjectile;
};

#endif // BASIC_PROJECTILE_HPP
