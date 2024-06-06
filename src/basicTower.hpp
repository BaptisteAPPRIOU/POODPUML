#ifndef BASIC_TOWER_HPP
#define BASIC_TOWER_HPP

#include "tower.hpp"
#include <algorithm>

class BasicTower : public Tower                                                                             // Class for the basic tower inherited from the tower class
{
    public:                                                                                                 // Public members
        BasicTower(Vector3 position);                                                                       // Constructor
        ~BasicTower() override;                                                                             // Destructor

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
    private:                                                                                                // Private members
        bool enemyInRange;
        static constexpr float fireRate = 1.5f;
};

#endif // BASIC_TOWER_HPP