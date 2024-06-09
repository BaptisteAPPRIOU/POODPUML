#include "map.hpp"
#include <rlgl.h>
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

Map::Map() {                                                                            // Constructor for the map
    tilePosition = Vector3{ 0.0f, 0.0f, 0.0f };
    roadPosition = Vector3{ 0.0f, 0.0f, 0.0f };
    hoveredTilePosition = Vector3{ 0.0f, 0.0f, 0.0f };
    isTileHovered = false;
    int numTilesX = 17; 
    int numTilesZ = 17; 
    buildableTiles.resize(numTilesX, vector<bool>(numTilesZ, true));
}

Map::~Map() {                                                                           // Destructor for the map
    UnloadModel(tile); 
    UnloadTexture(textureTile);
    UnloadModel(road);
    UnloadTexture(textureRoad); 
}

void Map::drawTiles() {                                                                 // Draw the tiles
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

void Map::update() {                                                                    // Update the map
    DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
    DrawFPS(10, 10);
}

void Map::drawRoad(std::vector<Vector3> path) {                                         // Draw the road
    for (auto& point : path) {
        roadPosition = Vector3{ point.x, 0.3f, point.z }; 
        DrawModel(road, roadPosition, 1.0f, WHITE);
    }
}

void Map::checkTileHover(Camera3D& camera) {                                            // Check if the tile is hovered
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    float start = -25.0f;
    float end = 25.0f;
    float step = 3.0f;
    isTileHovered = false;

    for (float z = start; z < end; z += step) {                                         // For each tile, check if the ray intersects with the tile
        for (float x = start; x < end; x += step) {                                     // If the ray intersects with the tile, set the hovered tile position
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

void Map::drawBoundingBox(vector<Vector3> path) {                                       // Draw the bounding box
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
        if (x >= 0 && x < static_cast<int>(buildableTiles.size()) && z >= 0 && z < static_cast<int>(buildableTiles[0].size())) {
            if (!buildableTiles[x][z]) {
                buildable = false;
            }
        }
        Vector3 centerPosition = (Vector3){ hoveredTilePosition.x, yOffset, hoveredTilePosition.z };
        Color color = buildable ? GREEN : RED;
        DrawCube(centerPosition, step, boxHeight, step, Fade(color, 0.5f));
    }
}

void Map::drawMap(vector<Vector3> path) {                                               // Draw the map
    DrawText("Welcome to the Tower Defense Game", 910, 10, 20, DARKGRAY);
    DrawFPS(10, 10);
    drawTiles();
    drawRoad(path);
    drawBoundingBox(path);
}

void Map::loadModelsTextures() {                                                        // Load the models and textures
    tile = LoadModel("assets/models/tile.obj");                                         // Load the tile's model and texture
    textureTile = LoadTexture("assets/textures/texture_tile.png");
    tile.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTile;

    road = LoadModel("assets/models/road.obj");                                         // Load the road's model and texture
    textureRoad = LoadTexture("assets/textures/texture_road.png");
    road.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureRoad;
}

void Map::setTileBuildable(Vector3 position, bool buildable) {                          // Set the tile to be buildable
    int x = static_cast<int>((position.x + 25.0f) / 3.0f);
    int z = static_cast<int>((position.z + 25.0f) / 3.0f); 
    if (x >= 0 && x < static_cast<int>(buildableTiles.size()) && z >= 0 && z < static_cast<int>(buildableTiles[0].size())) {
        buildableTiles[x][z] = buildable;
    }
}

bool Map::isTileBuildable(Vector3 position, const std::vector<Vector3>& path) const {   // Check if the tile is buildable
    int x = static_cast<int>((position.x + 25.0f) / 3.0f);
    int z = static_cast<int>((position.z + 25.0f) / 3.0f);
    if (x >= 0 && x < static_cast<int>(buildableTiles.size()) && z >= 0 && z < static_cast<int>(buildableTiles[0].size())) {
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

Vector3 Map::getHoveredTilePosition() const {                                           // Get the hovered tile's position
    return hoveredTilePosition;
}

void Map::setPath(const std::vector<Vector3>& newPath) {                                // Set the path
    path = newPath;
}