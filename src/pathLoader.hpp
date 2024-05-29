#ifndef LOADING_HPP
#define LOADING_HPP
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<Vector3> loadPathFromJSON(const std::string& filename);

#endif // LOADING_HPP