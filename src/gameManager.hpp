#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <raylib.h>
#include <vector>
#include "map.hpp"
#include "enemy.hpp"
#include "ui.hpp"
#include "tower.hpp"
#include "osberver.hpp"

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
        Tower* tower;
        Tower* hoveringTower;

        vector<Vector2> path;
        bool isPlacingTower;

    public:
        GameManager();
        ~GameManager();

        void update();
        void draw();
        void updateCamera();
        void onNotify() override;
        void placeTower(Vector3 position);
        
};
#endif // GAME_MANAGER_HPP