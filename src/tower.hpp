#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <raylib.h>
#include <vector>

using namespace std;

class Tower
{
public:
    virtual void update() = 0;

    static Tower* createTower(const string& type, Vector3 position);
    virtual void hoverTower(Vector3 position);
    virtual void shoot() = 0;
    virtual void draw(Vector3 towerPosition) = 0;
    virtual ~Tower() {}
    Vector3 towerPosition;

protected:
    Model tower;
    Texture2D textureTower;
    float range;
    int damage;
    float fireRate;
    float fireCountdown;
    int cost;

    Tower() {}
    Tower(Vector3 position) : towerPosition(position), range(0.0f), damage(0), fireRate(0.0f), fireCountdown(0.0f) {}
};


#endif // TOWER_HPP