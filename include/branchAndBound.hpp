#ifndef BAB_H
#define BAB_H

#define TIME_LIMIT 1800

#include <queue>
#include <ctime>
#include <iostream>
#include <bits/stdc++.h>
#include "node.hpp"

int in(int e, int n, int* path);
int* deepCopy(int n, int* originalArray);

void findTwoSmallest(double* arr, int size, double& smallest, double& secondSmallest);
double estimate(int n, int* path, double** dist, double** best);
double branchAndBound(int n, double** dist);

#endif