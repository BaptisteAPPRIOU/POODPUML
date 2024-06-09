#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <raylib.h>
#include <vector>
#include <chrono>
#include "map.hpp"
#include "enemy.hpp"
#include "ui.hpp"
#include "tower.hpp"
#include "observer.hpp"
#include "projectile.hpp"
#include "menu.hpp"
#include <fstream>
#include "leaderboard.hpp"
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
        Menu menu;
        Tower* hoveringTower;
        vector<Tower*> towers;
        vector<Enemy*> enemies;  
        vector<Projectile*> projectiles;

        vector<Vector3> path;
        bool isPlacingTower;

        float enemySpawnTimer; 
        int enemiesToSpawn;
        void spawnEnemy();
        void initializeWaves();
        void startNextWave();
        std::vector<std::pair<int, std::string>> waves;
        std::string enemyTypeToSpawn;
        int currentWave;
        int enemiesRemaining;
        int waveRemaining;

        int score;
        int money;
        int lives;
        int enemyCount = 0; // Add on claass diagram
        float elapsedTime; 
        bool timerStarted;

        int mediumEnemyCount = 1;
        int hardEnemyCount = 1;
    public:
        bool isGameOver;
        bool isGameWin;
        bool closeGame = false;
        GameManager();
        ~GameManager();
        void update();
        void draw();
        void updateCamera();
        void onNotify(EventType eventType) override;
        void checkTowersForEnemies();
        bool checkProjectileCollision(Projectile* projectile);
        int getScore() const;

};

#endif // GAME_MANAGER_HPP
