#include <raylib.h>
#include "map.hpp"
#include "button.hpp"
#include <iostream>

using namespace std;

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    const int regionX = 100;
    const int regionY = 100;
    const int regionWidth = 1200;
    const int regionHeight = 800;

    std::vector<Vector2> path = {
        { -10.0f, -10.0f },
        { -9.0f, -10.0f },
        { -8.0f, -10.0f },
        { -7.0f, -9.0f },
    };

    Map map;
    Camera camera = { 0 };
    camera.position = Vector3{ 13.0f, 60.0f, 60.0f };
    camera.target = Vector3{ 12.0f, 0.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;

    // Load textures for buttons
    Texture2D buttonTexture1 = LoadTexture("assets/images/button.png");
    Texture2D buttonHoverTexture1 = LoadTexture("assets/button1_hover.png");
    Texture2D buttonTexture2 = LoadTexture("assets/images/button.png");
    Texture2D buttonHoverTexture2 = LoadTexture("assets/button2_hover.png");
    Texture2D buttonTexture3 = LoadTexture("assets/images/button.png");
    Texture2D buttonHoverTexture3 = LoadTexture("assets/button3_hover.png");
    Texture2D buttonTexture4 = LoadTexture("assets/images/button.png");
    Texture2D buttonHoverTexture4 = LoadTexture("assets/button4_hover.png");

    // Calculate vertical positions to center the buttons
    int buttonWidth = 300;
    int buttonHeight = 50;
    int buttonSpacing = 50;
    int totalHeight = 4 * buttonHeight + 3 * buttonSpacing;
    int startY = (screenHeight - totalHeight) / 2;

    // Create buttons
    Button button1(1550, startY, buttonWidth, buttonHeight, buttonTexture1, buttonHoverTexture1);
    Button button2(1550, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight, buttonTexture2, buttonHoverTexture2);
    Button button3(1550, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, buttonTexture3, buttonHoverTexture3);
    Button button4(1550, startY + 3 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, buttonTexture4, buttonHoverTexture4);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update buttons
        Vector2 mousePoint = GetMousePosition();
        if (button1.IsClicked(mousePoint)) {
            cout << "Button 1 clicked" << endl;
        }
        if (button2.IsClicked(mousePoint)) {
            cout << "Button 2 clicked" << endl;
        }
        if (button3.IsClicked(mousePoint)) {
            cout << "Button 3 clicked" << endl;
        }
        if (button4.IsClicked(mousePoint)) {
            cout << "Button 4 clicked" << endl;
        }

        // Print the camera position
        cout << "Camera Position: "
             << "x: " << camera.position.x << ", "
             << "y: " << camera.position.y << ", "
             << "z: " << camera.position.z << endl;
        map.checkTileHover(camera);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginScissorMode(regionX, regionY, regionWidth, regionHeight);
                BeginMode3D(camera);
                    map.drawTiles();
                    map.drawRoad(path);
                    map.drawBoundingBox(1.0f);
                    DrawGrid(100, 1.0f);
                EndMode3D();
            EndScissorMode();

            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);

            DrawRectangleLines(regionX, regionY, regionWidth, regionHeight, BLACK);

            // Draw buttons
            button1.Draw(mousePoint);
            button2.Draw(mousePoint);
            button3.Draw(mousePoint);
            button4.Draw(mousePoint);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(buttonTexture1);
    UnloadTexture(buttonHoverTexture1);
    UnloadTexture(buttonTexture2);
    UnloadTexture(buttonHoverTexture2);
    UnloadTexture(buttonTexture3);
    UnloadTexture(buttonHoverTexture3);
    UnloadTexture(buttonTexture4);
    UnloadTexture(buttonHoverTexture4);

    CloseWindow();
    return 0;
}
