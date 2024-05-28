#include "projectile.hpp"

class BasicProjectile : public Projectile
{
    public:
        BasicProjectile(Vector3 position, Vector3 targetPosition);
        ~BasicProjectile() {}
        void update();
        void draw();
};