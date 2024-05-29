#ifndef BASIC_TOWER_HPP
#define BASIC_TOWER_HPP

#include "tower.hpp"

class BasicTower : public Tower
{
    public:
        BasicTower(Vector3 position);
        ~BasicTower() override;

        void update() override;
        void shoot(Vector3 enemyPosition) override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(Vector3 enemyPosition) override;
        Vector3 getTowerPosition() override;

    private:
        bool enemyInRange;
        Projectile* projectile;
};

#endif // BASIC_TOWER_HPP