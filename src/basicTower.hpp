#ifndef BASIC_TOWER_HPP
#define BASIC_TOWER_HPP

#include "tower.hpp"

class BasicTower : public Tower, public Subject
{
    public:
        BasicTower(Vector3 position);
        ~BasicTower() {}

        void update() override;
        void shoot() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        bool isEnemyInRange(const Vector3& enemyPosition) const;
        void onNotify() override;

    private:
        bool enemyInRange;
};

#endif // BASIC_TOWER_HPP