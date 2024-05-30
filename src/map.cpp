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

    int numTilesX = 17; 
    int numTilesZ = 17; 
    buildableTiles.resize(numTilesX, vector<bool>(numTilesZ, true));
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

void Map::drawRoad(std::vector<Vector3> path) {
    for (auto& point : path) {
        roadPosition = Vector3{ point.x, 0.3f, point.z }; 
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

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (isTileBuildable(hoveredTilePosition, path)) {
                        cout << "Tile clicked and notified: " << hoveredTilePosition.x << ", " << hoveredTilePosition.z << endl;
                        notify(EventType::TILE_CLICKED);
                    } else {
                        cout << "Tile clicked but not buildable: " << hoveredTilePosition.x << ", " << hoveredTilePosition.z << endl;
                    }
                }
                return;
            }
        }
    }
}

void Map::drawBoundingBox(vector<Vector3> path) {
    if (isTileHovered) {
        float step = 3.0f;
        float boxHeight = 2.0f; 
        float yOffset = 1.3f; 

        bool buildable = true;
        for (auto& point : path) {
            if (point.x == hoveredTilePosition.x && point.z == hoveredTilePosition.z) {
                buildable = false;
                break;
            }
        }
        
        int x = static_cast<int>((hoveredTilePosition.x + 25.0f) / 3.0f);
        int z = static_cast<int>((hoveredTilePosition.z + 25.0f) / 3.0f);
        if (x >= 0 && x < buildableTiles.size() && z >= 0 && z < buildableTiles[0].size()) {
            if (!buildableTiles[x][z]) {
                buildable = false;
            }
        }
        Vector3 centerPosition = (Vector3){ hoveredTilePosition.x, yOffset, hoveredTilePosition.z };

        Color color = buildable ? GREEN : RED;

        DrawCube(centerPosition, step, boxHeight, step, Fade(color, 0.5f));
    }
}

void Map::drawMap(vector<Vector3> path) {
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

void Map::setTileBuildable(Vector3 position, bool buildable) {
    int x = static_cast<int>((position.x + 25.0f) / 3.0f);
    int z = static_cast<int>((position.z + 25.0f) / 3.0f); 
    if (x >= 0 && x < buildableTiles.size() && z >= 0 && z < buildableTiles[0].size()) {
        buildableTiles[x][z] = buildable;
    }
}

bool Map::isTileBuildable(Vector3 position, const std::vector<Vector3>& path) const {
    int x = static_cast<int>((position.x + 25.0f) / 3.0f);
    int z = static_cast<int>((position.z + 25.0f) / 3.0f);
    if (x >= 0 && x < buildableTiles.size() && z >= 0 && z < buildableTiles[0].size()) {
        if (!buildableTiles[x][z]) {
            return false;
        }
    }

    for (const auto& point : path) {
        if (point.x == position.x && point.z == position.z) {
            return false;
        }
    }
    cout << "Checking if tile is buildable at position: " << position.x << ", " << position.z << endl;
    return true;
}

Vector3 Map::getHoveredTilePosition() const {
    return hoveredTilePosition;
}

void Map::setPath(const std::vector<Vector3>& newPath) {
    path = newPath;
}
