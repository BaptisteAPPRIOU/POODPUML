#include "map.hpp"
#include <rlgl.h>
#include <raylib.h>

Map::Map() {
    tile = LoadModel("assets/models/tile.obj");
    textureTile = LoadTexture("assets/textures/texture_tile.png");
    tile.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTile;

    road = LoadModel("assets/models/road.obj");
    textureRoad = LoadTexture("assets/textures/texture_road.png");
    road.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureRoad;

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

void Map::checkTileHover(Camera camera) {
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
}

void Map::drawBoundingBox(float thickness, vector<Vector2> path) {
    if (isTileHovered) {
        float step = 3.0f;
        float boxHeight = 2.0f; // Change this value to adjust the height of the bounding box
        Vector3 min = (Vector3){ hoveredTilePosition.x - step / 2, 0, hoveredTilePosition.z - step / 2 };
        Vector3 max = (Vector3){ hoveredTilePosition.x + step / 2, boxHeight, hoveredTilePosition.z + step / 2 };

        // Check if the hovered tile is a road tile
        buildable = true;
        for (auto& point : path) {
            if (point.x == hoveredTilePosition.x && point.y == hoveredTilePosition.z) {
                buildable = false;
                break;
            }
        }

        // Define the color based on whether the tile is a road tile or not
        Color color = buildable ? GREEN : RED;

        // Define the 8 corners of the bounding box
        Vector3 vertices[8] = {
            { min.x, min.y, min.z }, { max.x, min.y, min.z },
            { min.x, max.y, min.z }, { max.x, max.y, min.z },
            { min.x, min.y, max.z }, { max.x, min.y, max.z },
            { min.x, max.y, max.z }, { max.x, max.y, max.z }
        };

        // Define the 12 edges of the bounding box
        int edges[12][2] = {
            {0, 1}, {1, 3}, {3, 2}, {2, 0},
            {4, 5}, {5, 7}, {7, 6}, {6, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7}
        };

        // Draw the edges with simulated thickness by drawing parallel lines
        for (int i = 0; i < 12; i++) {
            Vector3 start = vertices[edges[i][0]];
            Vector3 end = vertices[edges[i][1]];

            // Simulate thickness by drawing multiple parallel lines
            for (float t = -thickness / 2; t <= thickness / 2; t += thickness / 10) {
                DrawLine3D((Vector3){ start.x + t, start.y, start.z }, (Vector3){ end.x + t, end.y, end.z }, color);
                DrawLine3D((Vector3){ start.x, start.y + t, start.z }, (Vector3){ end.x, end.y + t, end.z }, color);
                DrawLine3D((Vector3){ start.x, start.y, start.z + t }, (Vector3){ end.x, end.y, end.z + t }, color);
            }
        }
    }
}
