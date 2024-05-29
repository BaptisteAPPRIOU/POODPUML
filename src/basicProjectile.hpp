#ifndef BASIC_PROJECTILE_HPP
#define BASIC_PROJECTILE_HPP

#include "projectile.hpp"

class BasicProjectile : public Projectile {
public:
    BasicProjectile(Vector3 position, Vector3 targetPosition);
    ~BasicProjectile();

    void update() override;
    void draw() const override;

private:
    Model projectileModel;
    Texture2D textureProjectile;
};

#endif // BASIC_PROJECTILE_HPP
