#ifndef SLOW_TOWER_HPP
#define SLOW_TOWER_HPP

#include "tower.hpp"

class SlowTower : public Tower
{
    public:
        SlowTower(Vector3 position);
        ~SlowTower() override;

        void update() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 enemyPosition) override;
        Vector3 getTowerPosition() override;
        string getType() override;
        float getFireRate() override;
        int getCost() override;

    private:
        bool enemyInRange;
        static constexpr float fireRate = 0.1f;
        // Projectile* projectile;
};

#endif // SLOW_TOWER_HPP