#ifndef TAT_H
#define TAT_H

#include <list>
#include <cstring>
#include "utils.hpp"

int getNext(int u, std::list<int>* tree, int* parent);
double twiceAroundTree(int n, double** dist);

#endif