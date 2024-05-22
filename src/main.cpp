#include <raylib.h>

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 1920;
    const int screenHeight = 1080;


    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}