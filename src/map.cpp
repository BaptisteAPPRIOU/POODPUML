#include "map.hpp"
#include <rlgl.h>
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

Map::Map() {
    tilePosition = Vector3{ 0.0f, 0.0f, 0.0f };
    roadPosition = Vector3{ 0.0f, 0.0f, 0.0f };
    hoveredTilePosition = Vector3{ 0.0f, 0.0f, 0.0f };
    isTileHovered = false;
}

Map::~Map() {
    UnloadModel(tile); 
    UnloadTexture(textureTile);
    UnloadModel(road);
    UnloadTexture(textureRoad); 
}

void Map::drawTiles() {
    float start = -25.0f;  
    float end = 25.0f;     
    float step = 3.0f;     

    for (float z = start; z < end; z += step) {
        for (float x = start; x < end; x += step) {
            tilePosition = Vector3{ x, 0.0f, z };
            DrawModel(tile, tilePosition, 1.0f, WHITE);
        }
    }
}

void Map::update() {
    DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
    DrawFPS(10, 10);
}

void Map::drawRoad(std::vector<Vector2> path) {
    for (auto& point : path) {
        roadPosition = Vector3{ point.x, 0.3f, point.y }; 
        DrawModel(road, roadPosition, 1.0f, WHITE);
    }
}

void Map::checkTileHover(Camera3D& camera) {
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    float start = -25.0f;
    float end = 25.0f;
    float step = 3.0f;
    isTileHovered = false;

    for (float z = start; z < end; z += step) {
        for (float x = start; x < end; x += step) {
            BoundingBox tileBounds = {
                (Vector3){ x - step / 2, 0, z - step / 2 },
                (Vector3){ x + step / 2, 1, z + step / 2 }
            };

            RayCollision collision = GetRayCollisionBox(ray, tileBounds);
            if (collision.hit) {
                hoveredTilePosition = Vector3{ x, 0.0f, z };
                isTileHovered = true;
                return;
            }
        }
    }

    std::cout << "Checking tile hover" << std::endl;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        std::cout << "Mouse button pressed" << std::endl;
        Vector2 tilePosition = Vector2{hoveredTilePosition.x, hoveredTilePosition.z};
        std::cout << "Hovered Tile Position: " << hoveredTilePosition.x << ", " << hoveredTilePosition.z << std::endl;

        if (isTileBuildable(tilePosition, path)) {
            std::cout << "Buildable tile clicked" << std::endl;
            notifyTileClicked();
        } else {
            std::cout << "Tile is not buildable" << std::endl;
        }
    }
}

void Map::drawBoundingBox(vector<Vector2> path) {
    if (isTileHovered) {
        float step = 3.0f;
        float boxHeight = 2.0f; 
        float yOffset = 1.3f; 

        buildable = true;
        for (auto& point : path) {
            if (point.x == hoveredTilePosition.x && point.y == hoveredTilePosition.z) {
                buildable = false;
                break;
            }
        }
        Vector3 centerPosition = (Vector3){ hoveredTilePosition.x, yOffset, hoveredTilePosition.z };

        Color color = buildable ? GREEN : RED;

        DrawCube(centerPosition, step, boxHeight, step, Fade(color, 0.5f));;
    }
}

void Map::drawMap(vector<Vector2> path) {
    DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
    DrawFPS(10, 10);

    drawTiles();
    drawRoad(path);
    drawBoundingBox(path);
}

void Map::loadModelsTextures() {
    tile = LoadModel("assets/models/tile.obj");
    textureTile = LoadTexture("assets/textures/texture_tile.png");
    tile.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTile;

    road = LoadModel("assets/models/road.obj");
    textureRoad = LoadTexture("assets/textures/texture_road.png");
    road.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureRoad;
}

bool Map::isTileBuildable(Vector2 position, const vector<Vector2>& path) const {
    for (const auto& point : path) {
        if (point.x == position.x && point.y == position.y) {
            return false;
        }
    }
    std::cout << "Checking if tile is buildable at position: " << position.x << ", " << position.y << std::endl;
    return true;
}

Vector3 Map::getHoveredTilePosition() const {
    return hoveredTilePosition;
}

void Map::notifyTileClicked() {
    cout << "Notify observer of the Tile clicked" << endl;
    notify();
}

void Map::setPath(const std::vector<Vector2>& newPath) {
    path = newPath;
}