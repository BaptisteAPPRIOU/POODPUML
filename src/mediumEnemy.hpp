#ifndef MEDIUM_ENEMY_HPP
#define MEDIUM_ENEMY_HPP
#include <vector>
#include "enemy.hpp"

class MediumEnemy : public Enemy
{
public:
    MediumEnemy(Vector3 position);
    ~MediumEnemy() {}

    void update() override;
    void move(const vector<Vector2>& path) override;
};

#endif // MEDIUM_ENEMY_HPP