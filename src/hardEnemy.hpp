#ifndef HARD_ENEMY_HPP
#define HARD_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class HardEnemy : public Enemy                                  // HardEnemy class inherits from Enemy class
{
public:                                                         // Public members
    HardEnemy(Vector3 position);                                // Constructor for the hard enemy
    ~HardEnemy() {}                                             // Destructor for the hard enemy

    void update(Camera camera) override;
    void move(const vector<Vector3>& path) override;
    int getEnemyValue() const override;
    bool hasReachedEnd(vector<Vector3>& path) const override;
};

#endif // HARD_ENEMY_HPP