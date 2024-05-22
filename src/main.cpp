#include <raylib.h>
#include "map.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to parse a JSON file manually
std::vector<Vector2> loadPathFromJSON(const std::string& filename) {
    std::vector<Vector2> path;
    std::ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return path;
    }

    std::string line;
    std::string fileContent;
    while (std::getline(file, line)) {
        fileContent += line;
    }
    file.close();

    cout << "File content: " << fileContent << endl;

    // Simple JSON parsing (not robust, assumes correct format)
    size_t pos = fileContent.find("\"path\"");
    if (pos != std::string::npos) {
        pos = fileContent.find('[', pos);
        size_t end = fileContent.find(']', pos);
        std::string pathData = fileContent.substr(pos + 1, end - pos - 1);

        std::istringstream stream(pathData);
        std::string point;
        while (std::getline(stream, point, '{')) {
            if (point.find("x") != std::string::npos && point.find("y") != std::string::npos) {
                size_t xPos = point.find("x");
                size_t yPos = point.find("y");

                size_t xStart = point.find(":", xPos) + 1;
                size_t xEnd = point.find(",", xStart);
                float x = std::stof(point.substr(xStart, xEnd - xStart));

                size_t yStart = point.find(":", yPos) + 1;
                size_t yEnd = point.find('}', yStart);
                float y = std::stof(point.substr(yStart, yEnd - yStart));

                path.push_back({ x, y });
                cout << "Loaded point: x = " << x << ", y = " << y << endl;
            }
        }
    } else {
        cerr << "Path not found in JSON" << endl;
    }

    return path;
}

int main() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Tower Defense Game");

    const int regionX = 100;
    const int regionY = 100;
    const int regionWidth = 1200;
    const int regionHeight = 800;

    std::vector<Vector2> path = loadPathFromJSON("src/path.json");

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
