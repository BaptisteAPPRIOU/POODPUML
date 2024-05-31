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
        vector<Enemy*> enemies;  // Vecteur d'ennemis
        vector<Projectile*> projectiles;

        vector<Vector3> path;
        bool isPlacingTower;
        ofstream debugLogFile;
        // Wave* wave = nullptr; // Declare the variable "wave"
        // bool isFirstUpdate = true; // Add this static variable

        vector<float> spawnTimes; // Temps d'apparition des ennemis
        float startTime; // Temps initial
        int waveNumber = 21; // Numéro de la vague
        int numEnemies = 30; // Nombre d'ennemis

        float enemySpawnTimer; // Timer for enemy spawning
        int enemiesToSpawn;
        void spawnEnemy();

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