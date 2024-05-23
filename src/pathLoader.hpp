#ifndef LOADING_HPP
#define LOADING_HPP
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<Vector2> loadPathFromJSON(const string& filename);

#endif // LOADING_HPP