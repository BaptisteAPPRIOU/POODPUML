#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <raylib.h>
#include <vector>
#include "map.hpp"
#include "enemy.hpp"
#include "ui.hpp"
#include "tower.hpp"
#include "observer.hpp"
#include "projectile.hpp"
#include <fstream>
#include <vector>
using namespace std;

class GameManager : public Observer
{
    private:
        Camera3D camera;
        const int screenWidth;
        const int screenHeight;
        const int regionX;
        const int regionY;
        const int regionWidth;
        const int regionHeight;
        Vector3 cameraPosition;
        Vector3 cameraTarget;
        Vector3 cameraUp;
        float cameraFovy;
        Map map;
        UI ui;
        Tower* hoveringTower;
        vector<Tower*> towers;
        vector<Enemy*> enemies;  
        vector<Projectile*> projectiles;

        vector<Vector3> path;
        bool isPlacingTower;
        ofstream debugLogFile;

        float enemySpawnTimer; 
        int enemiesToSpawn;
        void spawnEnemy();
        void initializeWaves();
        void startNextWave();
        std::vector<std::pair<int, std::string>> waves;
        std::string enemyTypeToSpawn;
        int currentWave;

        int score;
        int money;
        int lives;
    public:
        GameManager();
        ~GameManager();
        void createEnemies(int numEnemies, int waveNumber);
        void update();
        void draw();
        void updateCamera();
        void onNotify(EventType eventType) override;
        void checkTowersForEnemies();
        bool checkProjectileCollision(Projectile* projectile);
};
#endif // GAME_MANAGER_HPP