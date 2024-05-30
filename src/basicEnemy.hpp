#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "enemy.hpp"

class BasicEnemy : public Enemy
{
public:
    BasicEnemy(Vector3 position);
    ~BasicEnemy() {}

    void update(Camera camera) override;
    void move(const vector<Vector3>& path) override;
    
};

#endif // BASIC_ENEMY_HPP