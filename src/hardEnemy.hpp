#ifndef HARD_ENEMY_HPP
#define HARD_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class HardEnemy : public Enemy
{
public:
    HardEnemy(Vector3 position);
    ~HardEnemy() {}

    void update(Camera camera) override; // Add 'override' keyword here
    void move(const vector<Vector3>& path) override;
    int getEnemyValue() const override;

};


#endif // HARD_ENEMY_HPP