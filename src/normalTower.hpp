#ifndef NORMAL_TOWER_HPP
#define NORMAL_TOWER_HPP

#include "tower.hpp"
#include <algorithm>

class NormalTower : public Tower
{
    public:
        NormalTower(Vector3 position);
        ~NormalTower() override;

        void update() override;
        void hoverTower(Vector3 position) override;
        void draw(Vector3 position) override;
        void checkEnemyInRange(const std::vector<Enemy*>& enemies) override;
        Vector3 getTowerPosition() override;
        string getType() override;
        float getFireRate() override;
        int getCost() override;
        vector<int> index_to_shoot = {};
        vector<int> getIndexOfEnemy() override;
        void addIndexOfEnemy(int index) override;
        void deleteIndexOfEnemy(int index) override;
        void resetIndexOfEnemy() override;
    private:
        bool enemyInRange;
        static constexpr float fireRate = 2.0f;
        // Projectile* projectile;
};

#endif // NORMAL_TOWER_HPP