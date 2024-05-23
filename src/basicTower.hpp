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
};

#endif // BASIC_TOWER_HPP