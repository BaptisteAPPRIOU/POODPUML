#ifndef BASIC_TOWER_HPP
#define BASIC_TOWER_HPP

#include "tower.hpp"

class BasicTower : public Tower
{
    public:
        BasicTower(Vector3 position);
        ~BasicTower() override;

        void update() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 enemyPosition) override;
        Vector3 getTowerPosition() override;
        string getType() override;
        float getFireRate() override;

    private:
        bool enemyInRange;
        static constexpr float fireRate = 1.3f;
        // Projectile* projectile;
};

#endif // BASIC_TOWER_HPP