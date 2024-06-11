#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "enemy.hpp"
#include <vector>
#include <iostream>
using namespace std;

class BasicEnemy : public Enemy                                                 // Inheritance from the Enemy class
{
public:                                                                         // Public members
    BasicEnemy(Vector3 position, int index_chosen);                                               // Constructor
    ~BasicEnemy() {}                                                            // Destructor       
    int index = 0;
    void update(Camera camera) override;
    void move(const std::vector<Vector3>& path) override;
    int getEnemyValue() const override;
    bool hasReachedEnd(std::vector<Vector3>& path) const override;
    int getIndex() const override;
    void setIndex(int index) override;
};

#endif // BASIC_ENEMY_HPP