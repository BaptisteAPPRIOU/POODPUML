#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <raylib.h>
#include <vector>
#include "observer.hpp"
#include <raymath.h>
#include "projectile.hpp"
#include "enemy.hpp"

using namespace std;

class Tower : public Subject
{
public:
    virtual void update() = 0;

    static Tower* createTower(const string& type, Vector3 position);
    virtual void hoverTower(Vector3 position);
    virtual void draw(Vector3 towerPosition) = 0;
    virtual ~Tower() {}
    Vector3 towerPosition;
    Vector3 enemyPosition;
    bool enemyInRange;
    virtual void checkEnemyInRange(const std::vector<Enemy*>& enemies, Vector3 enemyPosition, const string& type) = 0;
    virtual Vector3 getTowerPosition() = 0;
    virtual string getType();
    virtual float getFireRate() = 0;
    virtual int getCost() = 0;

protected:
    Model tower;
    Texture2D textureTower;
    float range;
    float timer;
    int cost;
    string type;

    Tower() {}
    Tower(Vector3 position) : towerPosition(position), range(0.0f), timer(0.0f), type("") {}
};
#endif // TOWER_HPP