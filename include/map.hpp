#ifndef MAP_H
#define MAP_H

#define INF std::numeric_limits<int>::max()

#include <cmath>
#include <limits>
#include <cstring>

class City{
    private:
        int x;
        int y;

    public:
        City();
        City(int x, int y);
        double distance(City cityB);
};

class Map{
    private:
        int n;
        City* cities;
        double** distances;

    public:
        Map(int n);
        void addCity(int id, int x, int y);
        double** getDistances();
};

#endif