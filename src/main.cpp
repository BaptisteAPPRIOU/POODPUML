#include <raylib.h>
#include "map.hpp"
#include <iostream>
using namespace std;

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    // Define the 3D rendering region
    const int regionX = 100;
    const int regionY = 100;
    const int regionWidth = 1200;
    const int regionHeight = 800;

    std::vector<Vector2> path = {
        { -10.0f, -10.0f },
        { -9.0f, -10.0f },
        { -8.0f, -10.0f },
        { -7.0f, -9.0f },
        { -6.0f, -8.0f },
        { -5.0f, -7.0f },
        { -4.0f, -6.0f },
        { -3.0f, -5.0f },
        { -2.0f, -4.0f },
        { -1.0f, -3.0f },
        { 0.0f, -2.0f },
        { 1.0f, -1.0f },
        { 2.0f, 0.0f },
        { 3.0f, 1.0f },
        { 4.0f, 2.0f },
        { 5.0f, 3.0f },
        { 6.0f, 4.0f },
        { 7.0f, 5.0f },
        { 8.0f, 6.0f },
        { 9.0f, 7.0f },
        { 10.0f, 8.0f }
    };

    Map map;

    Camera camera = { 0 };
    float aspectRatio = (float)regionWidth / regionHeight;
    float cameraDistance = 50.0f; // Adjust the distance as needed
   camera.position = Vector3{ 0.0f, cameraDistance / aspectRatio, cameraDistance };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Print the camera position
        cout << "Camera Position: "
             << "x: " << camera.position.x << ", "
             << "y: " << camera.position.y << ", "
             << "z: " << camera.position.z << endl;

        BeginDrawing();
             int mouseX = GetMouseX();
                int mouseY = GetMouseY();

                // Check if the mouse is over the 3D rendering region
                if (mouseX >= regionX && mouseX <= regionX + regionWidth &&
                    mouseY >= regionY && mouseY <= regionY + regionHeight) {
                    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
                }
            ClearBackground(RAYWHITE);

            BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
                BeginMode3D(camera);
                    map.drawTiles();
                    map.drawRoad(path);
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
