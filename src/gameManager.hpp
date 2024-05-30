#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <raylib.h>
#include <vector>
#include <chrono>

#include "map.hpp"
#include "enemy.hpp"
#include "ui.hpp"

class GameManager
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
        Enemy* enemy;
        UI ui;
        Font timerFont;
        std::chrono::steady_clock::time_point startTime;
        int minutes;
        int seconds;

        std::vector<Vector2> path;

    public:
        GameManager();
        ~GameManager();

        void update();
        void draw();
        void updateCamera();
};

#endif // GAME_MANAGER_HPP
