#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <raylib.h>
#include <vector>
#include "map.hpp"
#include "enemy.hpp"
#include "ui.hpp"
#include "tower.hpp"
#include "osberver.hpp"
#include "projectile.hpp"
#include <fstream>

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
        Enemy* enemy;
        Tower* hoveringTower;
        Projectile* projectile1;
        vector<Tower*> towers;
        vector<Projectile*> projectiles;

        vector<Vector2> path;
        bool isPlacingTower;
        ofstream debugLogFile;

    public:
        GameManager();
        ~GameManager();

        void update();
        void draw();
        void updateCamera();
        void onNotify(EventType eventType) override;
        void checkTowersForEnemies();
};
#endif // GAME_MANAGER_HPP