#ifndef SLOW_TOWER_HPP
#define SLOW_TOWER_HPP

#include "tower.hpp"
#include <algorithm>

class SlowTower : public Tower                                                                              // Class for the slow tower inherited from the tower class     
{
    public:                                                                                                 // Public members            
        SlowTower(Vector3 position);                                                                        // Constructor    
        ~SlowTower() override;                                                                              // Destructor

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
        static constexpr float fireRate = 0.0f;
};

#endif // SLOW_TOWER_HPP