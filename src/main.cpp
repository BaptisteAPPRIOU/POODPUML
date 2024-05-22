#include <raylib.h>
#include "map.hpp"
#include <iostream>
using namespace std;

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    Map map;

    Camera camera = { 0 };
    camera.position = Vector3{ 55.0f, 40.0f, 0.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;

    // camera.projection = CAMERA_FREE;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    cout << "Camera Position: "
                  << "x: " << camera.position.x << ", "
                  << "y: " << camera.position.y << ", "
                  << "z: " << camera.position.z << endl;

        BeginDrawing();
            UpdateCamera(&camera, CAMERA_THIRD_PERSON);
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                map.drawTiles();
                map.drawRoad();
                DrawGrid(100, 1.0f);
            EndMode3D();
            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
