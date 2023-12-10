#include "map.hpp"

City::City(){
    this->x = 0;
    this->y = 0;
}

City::City(int x, int y){
    this->x = x;
    this->y = y;
}

double City::distance(City cityB){
    int dx = pow(this->x - cityB.x, 2);
    int dy = pow(this->y - cityB.y, 2);
    return sqrt(dx + dy);
}

Map::Map(int n){
    this->cities = new City[n];
    this->distances = new double* [n];

    for(int i = 0; i < n; i++){
        this->distances[i] = new double[n];
        memset(this->distances[i], INF, sizeof(double) * n);
    }
}

void Map::addCity(int id, int x, int y){
    City city = City(x, y);
    this->cities[id - 1] = city;
    for(int i = 0; i < id-1; i++){
        double dist = city.distance(this->cities[i]);
        this->distances[id - 1][i] = dist;
        this->distances[i][id - 1] = dist;
    }
}

double** Map::getDistances(){
    return this->distances;
}