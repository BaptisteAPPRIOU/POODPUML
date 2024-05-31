#ifndef SLOW_TOWER_HPP
#define SLOW_TOWER_HPP

#include "tower.hpp"

class SlowTower : public Tower
{
    public:
        SlowTower(Vector3 position, float fireRate);
        ~SlowTower() override;

        void update() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(Vector3 enemyPosition) override;
        Vector3 getTowerPosition() override;
        string getType() override;
        float getFireRate() override;

    private:
        bool enemyInRange;
        // Projectile* projectile;
};

#endif // SLOW_TOWER_HPP