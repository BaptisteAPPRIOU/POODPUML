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
    bool buildable;             

public:
    Vector3 hoveredTilePosition; 
    bool isTileHovered;          
    Map();
    ~Map();

    void drawMap(vector<Vector2> path);
    void drawTiles();
    void update();
    void drawRoad(vector<Vector2> path);
    void checkTileHover(Camera camera); 
    void drawBoundingBox(float thickness, vector<Vector2> path);            
    void loadModelsTextures(); 
    bool isTileBuildable(Vector2 position, const vector<Vector2>& path) const;
    Vector3 getHoveredTilePosition() const;
};

#endif // MAP_HPP
