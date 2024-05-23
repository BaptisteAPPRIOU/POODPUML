#include "pathBuilder.hpp"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

// Constructor
PathBuilder::PathBuilder(float start, float end, float step)
    : start(start), end(end), step(step),
      width(static_cast<int>((end - start) / step) + 1),
      height(static_cast<int>((end - start) / step) + 1),
      directions({{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
    srand(time(0)); // Seed the random number generator
}

std::vector<std::pair<float, float>> PathBuilder::generateRandomPath() {
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));
    std::stack<Node> s;

    // Randomly choose a starting point on the leftmost column
    int startY = rand() % height;
    s.push({0, startY});
    visited[0][startY] = true;

    std::vector<std::pair<float, float>> path;

    while (!s.empty()) {
        Node current = s.top();
        s.pop();
        path.push_back({ toWorldCoordinate(current.x), toWorldCoordinate(current.y) });

        // If the current node is on the rightmost column, end the path
        if (current.x == width - 1) {
            break;
        }

        // Randomize directions
        std::vector<std::pair<int, int>> shuffledDirections = directions;
        std::random_shuffle(shuffledDirections.begin(), shuffledDirections.end());

        // Explore neighbors in randomized order
        for (auto dir : shuffledDirections) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;
            if (isValid(newX, newY, visited)) {
                visited[newX][newY] = true;
                s.push({newX, newY});
            }
        }
    }

    // Ensure the path ends on the rightmost column
    if (toWorldCoordinate(path.back().first) != (width - 1) * step + start) {
        path.push_back({ (width - 1) * step + start, path.back().second });
    }

    return path;
}

bool PathBuilder::isValid(int x, int y, std::vector<std::vector<bool>>& visited) {
    return x >= 0 && x < width && y >= 0 && y < height && !visited[x][y];
}

float PathBuilder::toWorldCoordinate(int gridCoordinate) {
    return start + gridCoordinate * step;
}
