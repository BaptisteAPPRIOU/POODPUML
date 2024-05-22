#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <raylib.h>
using namespace std;

class Enemy
{
public:
    // Pure virtual function to update the enemy
    virtual void update() = 0;

    static Enemy* createEnemy(const string& type, Vector3 position);

    virtual void move(const vector<Vector2>& path);

protected:
    Model enemy;
    Texture2D textureEnemy;
    Vector3 enemyPosition;
    float speed;
    int health;
    bool isAlive;
    int currentPoint;

    Enemy() {}
    virtual ~Enemy() {}
    Enemy(Vector3 position) : enemyPosition(position), speed(0.0f), currentPoint(0) {}

};

#endif // ENEMY_HPP