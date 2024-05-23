#ifndef HARD_ENEMY_HPP
#define HARD_ENEMY_HPP
#include <vector>
#include "enemy.hpp"

class HardEnemy : public Enemy
{
public:
    HardEnemy(Vector3 position);
    ~HardEnemy() {}

    void update() override;
    void move(const vector<Vector2>& path) override;
};

#endif // HARD_ENEMY_HPP