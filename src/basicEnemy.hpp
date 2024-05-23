#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
using namespace std;

class BasicEnemy : public Enemy
{
public:
    BasicEnemy(Vector3 position);
    ~BasicEnemy() {}

    void update() override;
    void move(const vector<Vector2>& path) override;
};

#endif // BASIC_ENEMY_HPP