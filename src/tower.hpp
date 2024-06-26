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

class Tower : public Subject                                                                // Tower class inherits from Subject   
{
public:                                                                                     // Public members        
    virtual void update() = 0;

    static Tower* createTower(const string& type, Vector3 position);
    virtual void hoverTower(Vector3 position);
    virtual void draw(Vector3 towerPosition) = 0;
    virtual ~Tower() {}                                                                     // Virtual destructor
    Vector3 towerPosition;
    Vector3 enemyPosition;
    bool enemyInRange;
    virtual void checkEnemyInRange(const std::vector<Enemy*>& enemies) = 0;
    virtual Vector3 getTowerPosition() = 0;
    virtual string getType();
    virtual float getFireRate() = 0;
    virtual int getCost() = 0;
    virtual void addIndexOfEnemy(int index) = 0;
    virtual vector<int> getIndexOfEnemy() = 0;
    virtual void deleteIndexOfEnemy(int index) = 0;
    virtual void resetIndexOfEnemy() = 0;

protected:                                                                                // Protected members      
    Model tower;
    Texture2D textureTower;
    float range;
    float timer;
    int cost;
    string type;

    Tower() {}                                                                                  // Constructor for the tower class            
    Tower(Vector3 position) : towerPosition(position), range(0.0f), timer(0.0f), type("") {}    // Constructor for the tower class with parameters
};
#endif // TOWER_HPP