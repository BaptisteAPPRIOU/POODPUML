#ifndef MAP_HPP
#define MAP_HPP

#include <raylib.h>
#include <vector>
#include "osberver.hpp"
using namespace std;

class Map : public Subject
{
private:
    Model tile;
    Model road;
    Texture2D textureTile;
    Texture2D textureRoad;
    Vector3 tilePosition;
    Vector3 roadPosition;
    bool buildable;  
    vector<Vector2> path;           

public:
    Vector3 hoveredTilePosition; 
    bool isTileHovered;          
    Map();
    ~Map();

    void drawMap(vector<Vector2> path);
    void drawTiles();
    void update();
    void drawRoad(vector<Vector2> path);
    void checkTileHover(Camera3D& camera);
    void drawBoundingBox(vector<Vector2> path);            
    void loadModelsTextures(); 
    bool isTileBuildable(Vector2 position, const vector<Vector2>& path) const;
    Vector3 getHoveredTilePosition() const;
    void setPath(const std::vector<Vector2>& newPath); 
};

#endif // MAP_HPP
