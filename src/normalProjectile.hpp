#ifndef NORMAL_PROJECTILE_HPP
#define NORMAL_PROJECTILE_HPP

#include "projectile.hpp"

class NormalProjectile : public Projectile {                    // Class for the basic projectile inherited from the projectile class
public:                                                         // Public members
    NormalProjectile(Vector3 position, Vector3 targetPosition); // Constructor
    ~NormalProjectile();
    void update() override;
    void draw() const override;

private:                                                        // Private members
    Model projectileModel;
    Texture2D textureProjectile;
};

#endif // BASIC_PROJECTILE_HPP