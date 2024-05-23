#include "pathLoader.hpp"
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


// Function to parse a JSON file manually
vector<Vector2> loadPathFromJSON(const string& filename) {
    vector<Vector2> path;
    ifstream file(filename);
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

    cout << "File content: " << fileContent << endl;

    // Simple JSON parsing (not robust, assumes correct format)
    size_t pos = fileContent.find("\"path\"");
    if (pos != string::npos) {
        pos = fileContent.find('[', pos);
        size_t end = fileContent.find(']', pos);
        string pathData = fileContent.substr(pos + 1, end - pos - 1);

        istringstream stream(pathData);
        string point;
        while (getline(stream, point, '{')) {
            if (point.find("x") != string::npos && point.find("y") != string::npos) {
                size_t xPos = point.find("x");
                size_t yPos = point.find("y");

                size_t xStart = point.find(":", xPos) + 1;
                size_t xEnd = point.find(",", xStart);
                float x = stof(point.substr(xStart, xEnd - xStart));

                size_t yStart = point.find(":", yPos) + 1;
                size_t yEnd = point.find('}', yStart);
                float y = stof(point.substr(yStart, yEnd - yStart));

                path.push_back({ x, y });
                cout << "Loaded point: x = " << x << ", y = " << y << endl;
            }
        }
    } else {
        cerr << "Path not found in JSON" << endl;
    }

    return path;
}