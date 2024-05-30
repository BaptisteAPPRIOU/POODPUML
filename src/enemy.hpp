#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <raylib.h>
using namespace std;

class Enemy
{
public:
    virtual void update(Camera camera) = 0;

    static Enemy* createEnemy(const string& type, Vector3 position);

    virtual void move(const vector<Vector3>& path);
    virtual ~Enemy() {}
    virtual Vector3 getEnemyPosition() const;
    virtual void takeDamage(int damage);
    virtual bool isEnemyAlive() const;
    bool isAlive;
    void drawLifeBar(Camera camera);

protected:
    Model enemy;
    Texture2D textureEnemy;
    Vector3 enemyPosition;
    float speed;
    int health;
    int maxHealth;
    int currentPoint;
    int value;

    Enemy() {}
    Enemy(Vector3 position) : enemyPosition(position), speed(0.0f), currentPoint(0) {}

};

#endif // ENEMY_HPP