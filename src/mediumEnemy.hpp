#ifndef MEDIUM_ENEMY_HPP
#define MEDIUM_ENEMY_HPP
#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class MediumEnemy : public Enemy
{
public:
    MediumEnemy(Vector3 position);
    ~MediumEnemy() {}

    void update(Camera camera) override;
    void move(const vector<Vector3>& path) override;
};

#endif // MEDIUM_ENEMY_HPP