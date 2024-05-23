#ifndef PATH_BUILDER_HPP
#define PATH_BUILDER_HPP

#include <vector>
#include <utility>
#include <vector>
using namespace std;

// Define the Node struct
struct Node {
    int x;
    int y;
};

// Define the PathBuilder class
class PathBuilder {
public:
    PathBuilder(float start, float end, float step);
    vector<pair<float, float>> generateRandomPath();
    bool isValid(int x, int y, vector<vector<bool>>& visited);
    float toWorldCoordinate(int gridCoordinate);

private:
    float start;
    float end;
    float step;
    int width;
    int height;
    vector<pair<int, int>> directions;
};

#endif // PATH_BUILDER_HPP