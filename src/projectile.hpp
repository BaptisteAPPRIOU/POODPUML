#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>

class Projectile {                                                                                          // Class for the projectile       
public:                                                                                                     // Public members       
    virtual ~Projectile() {}                                                                                // Virtual destructor

    virtual void update() = 0;
    virtual void draw() const = 0;

    static Projectile* createProjectile(const std::string& type, Vector3 position, Vector3 targetPosition); // Function to create a projectile

    Vector3 getPosition() const;
    int getDamage() const;

protected:
    Projectile(Vector3 position, Vector3 targetPosition, float speed, int damage);                          // Constructor for the projectile class       

    Model projectileModel;
    Texture2D textureProjectile;
    Vector3 position;
    Vector3 targetPosition;
    float speed;
    int damage;
};

#endif // PROJECTILE_HPP
