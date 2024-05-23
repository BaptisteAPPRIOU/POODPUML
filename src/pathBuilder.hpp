#ifndef PATH_BUILDER_HPP
#define PATH_BUILDER_HPP

#include <vector>
#include <utility>

class PathBuilder {
public:
    PathBuilder(float start, float end, float step);

    std::vector<std::pair<float, float>> generateRandomPath();

private:
    struct Node {
        int x, y;
    };

    int width;
    int height;
    float start;
    float end;
    float step;
    const std::vector<std::pair<int, int>> directions;

    bool isValid(int x, int y, std::vector<std::vector<bool>>& visited);
    float toWorldCoordinate(int gridCoordinate);
};

#endif // PATH_BUILDER_HPP
