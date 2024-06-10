#ifndef BASIC_PROJECTILE_HPP
#define BASIC_PROJECTILE_HPP

#include "projectile.hpp"

class BasicProjectile : public Projectile {                         // Class for the basic projectile inherited from the projectile class
public:                                                             // Public members
    BasicProjectile(Vector3 position, Vector3 targetPosition);      // Constructor
    ~BasicProjectile();                                             // Destructor

    void update() override;
    void draw() const override;

private:                                                            // Private members
    Model projectileModel;
    Texture2D textureProjectile;
};

#endif // BASIC_PROJECTILE_HPP