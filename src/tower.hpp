#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <raylib.h>
#include <vector>
#include "observer.hpp"
#include <raymath.h>
#include "projectile.hpp"

using namespace std;

class Tower : public Subject
{
public:
    virtual void update() = 0;

    static Tower* createTower(const string& type, Vector3 position, float fireRate);
    virtual void hoverTower(Vector3 position);
    virtual void draw(Vector3 towerPosition) = 0;
    virtual ~Tower() {}
    Vector3 towerPosition;
    Vector3 enemyPosition;
    bool enemyInRange;
    virtual void checkEnemyInRange(Vector3 enemyPosition) = 0;
    virtual Vector3 getTowerPosition() = 0;
    virtual string getType();
    virtual float getFireRate();

protected:
    Model tower;
    Texture2D textureTower;
    float range;
    float fireRate;
    float timer;
    int cost;
    string type;

    Tower() {}
    Tower(Vector3 position, float fireRate) : towerPosition(position), range(0.0f), fireRate(fireRate), timer(0.0f), type("") {}
};
#endif // TOWER_HPP