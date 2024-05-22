#ifndef MAP_HPP
#define MAP_HPP

#include <raylib.h>
#include <vector>
using namespace std;

class Map
{
private:
    Model tile;
    Model road;
    Texture2D textureTile;
    Texture2D textureRoad;
    Vector3 tilePosition;
    Vector3 roadPosition;
    Vector3 hoveredTilePosition; // New member to store hovered tile position
    bool isTileHovered;          // New member to track if a tile is hovered

public:
    Map();
    ~Map();

    void draw();
    void drawTiles();
    void update();
    void drawRoad(vector<Vector2> path);
    void checkTileHover(Camera camera); // New method to check for hover
    void drawBoundingBox();             // New method to draw bounding box
};

#endif // MAP_HPP
