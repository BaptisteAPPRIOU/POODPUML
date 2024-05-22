#ifndef MAP_HPP
#define MAP_HPP

#include <raylib.h>

class Map
{
    private:
        Model tile;
        Model road;
        Texture2D textureTile;
        Texture2D textureRoad;
        Vector3 tilePosition;
        Vector3 roadPosition;
    public:
        Map();
        ~Map();

        void draw();
        void drawTiles();
        void update();
        void drawRoad();
};

#endif // MAP_HPP