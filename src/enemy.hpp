#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

class Enemy                                                                // Class for the enemy
{
public:                                                                    // Public members
    virtual void update(Camera camera) = 0;

    static Enemy* createEnemy(const string& type, Vector3 position, int index_chosen); // Add on class diagram

    virtual void move(const std::vector<Vector3>& path);
    virtual ~Enemy();
    virtual Vector3 getEnemyPosition() const;
    virtual void takeDamage(int damage);
    virtual bool isEnemyAlive() const;
    bool isAlive;
    void drawLifeBar(Camera camera);
    void setSpeed(float speed);
    float getSpeed();
    bool slowed = false;
    bool isChecked = false;
    int getIndex() const; // Add on class diagram
    void setIndex(int index); // Add on class diagram
    virtual int getEnemyValue() const;
    virtual bool hasReachedEnd(std::vector<Vector3>& path) const;

protected:                                                                  // Protected members
    Model enemy;
    Texture2D textureEnemy;
    Vector3 enemyPosition;
    float speed;
    int health;
    int maxHealth;
    int currentPoint = 0;
    int value;
    int index = 15; // Add on class diagram
    Enemy() {}
    Enemy(Vector3 position) : enemyPosition(position), speed(0.0f), currentPoint(0) {}
};

#endif // ENEMY_HPP