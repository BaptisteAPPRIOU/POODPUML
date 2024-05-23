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
    Vector3 hoveredTilePosition; 
    bool isTileHovered;          
    bool buildable;             

public:
    Map();
    ~Map();

    void drawMap(vector<Vector2> path);
    void drawTiles();
    void update();
    void drawRoad(vector<Vector2> path);
    void checkTileHover(Camera camera); 
    void drawBoundingBox(float thickness, vector<Vector2> path);            
    void loadModelsTextures(); 
};

#endif // MAP_HPP
