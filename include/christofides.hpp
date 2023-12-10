#ifndef CHRISTOFIDES_H
#define CHRISTOFIDES_H

#include <list>
#include <vector>
#include <iostream>
#include "utils.hpp"
#include "matching.hpp"

int* getDegree(int n, int* parent);
std::vector<int> getOdds(int n, int* degree);
double** setDistOdds(std::vector<int> odds, double** dist);

double christofides(int n, double** dist);


#endif