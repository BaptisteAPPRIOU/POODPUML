#include "map.hpp"

Map::Map() {
    tile = LoadModel("assets/models/tile.obj");
    textureTile = LoadTexture("assets/textures/texture_tile.png");
    tile.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureTile;

    road = LoadModel("assets/models/road.obj");
    textureRoad = LoadTexture("assets/textures/texture_road.png");
    road.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureRoad;

    tilePosition = Vector3{ 0.0f, 0.0f, 0.0f };
    roadPosition = Vector3{ 0.0f, 0.0f, 0.0f };
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
    float step = 1.0f;     

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
