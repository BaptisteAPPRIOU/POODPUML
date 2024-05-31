#ifndef NORMAL_TOWER_HPP
#define NORMAL_TOWER_HPP

#include "tower.hpp"

class NormalTower : public Tower
{
    public:
        NormalTower(Vector3 position);
        ~NormalTower() override;

        void update() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(Vector3 enemyPosition) override;
        Vector3 getTowerPosition() override;
        string getType() override;
        float getFireRate() override;

    private:
        bool enemyInRange;
        static constexpr float fireRate = 2.0f;
        // Projectile* projectile;
};

#endif // NORMAL_TOWER_HPP