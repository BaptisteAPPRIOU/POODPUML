#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class BasicEnemy : public Enemy                                                 // Inheritance from the Enemy class
{
public:                                                                         // Public members
    BasicEnemy(Vector3 position);                                               // Constructor
    ~BasicEnemy() {}                                                            // Destructor       

    void update(Camera camera) override;
    void move(const std::vector<Vector3>& path) override;
    int getEnemyValue() const override;
    bool hasReachedEnd(std::vector<Vector3>& path) const override;
};

#endif // BASIC_ENEMY_HPP