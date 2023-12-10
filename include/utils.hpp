#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "map.hpp"

int minKey(int n, double* keys, bool* viewed);
int* mst(int n, double** dist);
Map* readFile(std::string fileName, int &nS);

#endif