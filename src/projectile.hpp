#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <raylib.h>
#include <raymath.h>
#include <string>
using namespace std;

class Projectile
{
    public:
        virtual void update() = 0;
        virtual void draw() = 0;

        Vector3 getPosition() const;
        int getDamage() const;
        static Projectile* createProjectile(const string& type, Vector3 position, Vector3 targetPosition);
        virtual ~Projectile() {}

    protected:
        Model projectile;
        Texture2D textureProjectile;
        Vector3 position;
        Vector3 targetPosition;
        float speed;
        int damage;
        
        Projectile(Vector3 position, Vector3 targetPosition, float speed, int damage);
};

#endif // PROJECTILE_HPP