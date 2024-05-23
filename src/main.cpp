#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "map.hpp"
#include "loading_path.hpp"

using namespace std;



int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    const int regionX = 100;
    const int regionY = 100;
    const int regionWidth = 1200;
    const int regionHeight = 800;

    std::vector<Vector2> path = loadPathFromJSON("src/path_medium.json");

    if (path.empty()) {
        cerr << "Path is empty!" << endl;
        CloseWindow();
        return -1;
    }

    Map map;
    Camera camera = { 0 };
    camera.position = Vector3{ 13.0f, 60.0f, 60.0f };
    camera.target = Vector3{ 12.0f, 0.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        map.checkTileHover(camera);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
                BeginMode3D(camera);
                    map.drawTiles();
                    map.drawRoad(path);
                    map.drawBoundingBox(1.0f, path);
                    DrawGrid(100, 1.0f);
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);

            DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
