#ifndef MAP_HPP
#define MAP_HPP

#include <raylib.h>
#include <vector>
#include "observer.hpp"
using namespace std;

class Map : public Subject                                                          // Map class inherits from Subject        
{
private:                                                                            // Private members
    Model tile;
    Model road;
    Texture2D textureTile;
    Texture2D textureRoad;
    Vector3 tilePosition;
    Vector3 roadPosition;
    vector<Vector3> path;
    vector<vector<bool>> buildableTiles;           

public:                                                                             // Public members
    Vector3 hoveredTilePosition; 
    bool isTileHovered;          
    Map();                                                                          // Constructor
    ~Map();                                                                         // Destructor

    void drawMap(vector<Vector3> path);
    void drawTiles();
    void update();
    void drawRoad(vector<Vector3> path);
    void checkTileHover(Camera3D& camera);
    void drawBoundingBox(vector<Vector3> path);            
    void loadModelsTextures(); 
    bool isTileBuildable(Vector3 position, const vector<Vector3>& path) const;
    Vector3 getHoveredTilePosition() const;
    void setPath(const std::vector<Vector3>& newPath);
    void setTileBuildable(Vector3 position, bool buildable); 
};

#endif // MAP_HPP