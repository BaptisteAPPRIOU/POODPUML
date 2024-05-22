#include <raylib.h>

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    // Color darkGreen = Color{20, 160, 133, 255};
    Model model = LoadModel("assets/models/tower.obj");
    Texture2D texture = LoadTexture("assets/textures/texture.png");

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Camera camera = { 0 };
    camera.position = Vector3{ 50.0f, 50.0f, 50.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 50.0f;
    CameraMode cameraMode = CAMERA_FREE;

    Vector3 towerPosition = Vector3{ 0.0f, 0.0f, 0.0f };
    BoundingBox towerBox = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, cameraMode);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawModel(model, towerPosition, 1.0f, WHITE);
                DrawGrid(100, 10.0f);
                DrawBoundingBox(towerBox, RED);

            EndMode3D();
            DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }
    UnloadTexture(texture);
    UnloadModel(model);
    CloseWindow();
    return 0;
}