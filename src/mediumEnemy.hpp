#ifndef MEDIUM_ENEMY_HPP
#define MEDIUM_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class MediumEnemy : public Enemy                                // MediumEnemy class inherits from Enemy class
{
public:                                                         // Public members
    MediumEnemy(Vector3 position);                              // Constructor for the medium enemy
    ~MediumEnemy() {}                                           // Destructor for the medium enemy

    void update(Camera camera) override;
    void move(const vector<Vector3>& path) override;
    int getEnemyValue() const override;
    bool hasReachedEnd(vector<Vector3>& path) const override;
};

#endif // MEDIUM_ENEMY_HPP