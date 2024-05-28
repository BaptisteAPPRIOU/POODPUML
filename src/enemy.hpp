#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <raylib.h>
#include <vector>
using namespace std;

class Enemy
{
public:
    virtual void update() = 0;

    static Enemy* createEnemy(const string& type, Vector3 position);

    virtual void move(const vector<Vector2>& path);
    virtual ~Enemy() {}
    virtual Vector3 getEnemyPosition() const;

protected:
    Model enemy;
    Texture2D textureEnemy;
    Vector3 enemyPosition;
    float speed;
    int health;
    bool isAlive;
    int currentPoint = 0;
    int value;

    Enemy() {}
    Enemy(Vector3 position) : enemyPosition(position), speed(0.0f), currentPoint(0) {}

};

#endif // ENEMY_HPP