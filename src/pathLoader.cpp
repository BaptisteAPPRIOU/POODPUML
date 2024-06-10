#include "pathLoader.hpp"
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

std::vector<Vector3> loadPathFromJSON(const std::string& filename) {                        // Load path from JSON file and return it as a vector of Vector3
    std::vector<Vector3> path;
    std::ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return path;
    }

    string line;
    string fileContent;
    while (getline(file, line)) {
        fileContent += line;
    }
    file.close();

    size_t pos = fileContent.find("\"path\"");
    if (pos != string::npos) {
        pos = fileContent.find('[', pos);
        size_t end = fileContent.find(']', pos);
        string pathData = fileContent.substr(pos + 1, end - pos - 1);

        std::istringstream stream(pathData);
        std::string point;
        while (std::getline(stream, point, '{')) {                                          // Parse the points from the JSON file              
            if (point.find("x") != std::string::npos && point.find("y") != std::string::npos && point.find("z") != std::string::npos) {
                size_t xPos = point.find("x");
                size_t yPos = point.find("y");
                size_t zPos = point.find("z");

                size_t xStart = point.find(":", xPos) + 1;
                size_t xEnd = point.find(",", xStart);
                float x = stof(point.substr(xStart, xEnd - xStart));

                size_t yStart = point.find(":", yPos) + 1;
                size_t yEnd = point.find('}', yStart);
                float y = std::stof(point.substr(yStart, yEnd - yStart));

                size_t zStart = point.find(":", zPos) + 1;
                size_t zEnd = point.find(',', zStart);
                float z = std::stof(point.substr(zStart, zEnd - zStart));

                path.push_back({ x, y, z});
            }
        }
    } else {
        cerr << "Path not found in JSON" << endl;
    }

    return path;
}