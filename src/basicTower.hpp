#ifndef BASIC_TOWER_HPP
#define BASIC_TOWER_HPP

#include "tower.hpp"

class BasicTower : public Tower
{
    public:
        BasicTower(Vector3 position);
        ~BasicTower() {}

        void update() override;
        void shoot() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(Vector3 enemyPosition) override;

    private:
        bool enemyInRange;
};

#endif // BASIC_TOWER_HPP