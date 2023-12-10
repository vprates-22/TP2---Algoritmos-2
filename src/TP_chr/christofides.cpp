#include "christofides.hpp"

int* getDegree(int n, int* parent){
    int* degree = new int[n];
    memset(degree, 0, sizeof(int) * n);

    for(int i = 1; i < n; i++){
        degree[i] += 1;
        degree[parent[i]] += 1;
    }

    return degree;
}

std::vector<int> getOdds(int n, int* degree){
    std::vector<int> odds;

    for(int i = 0; i < n; i++){
        if(degree[i] % 2 == 1){
            odds.push_back(i);
        }
    }    

    return odds;
}

double** setDistOdds(std::vector<int> odds, double** dist){
    int size = odds.size();
    double** dOdds = new double*[size];
    for(int i = 0; i < size; i++){
        dOdds[i] = new double[size];

        for(int j = 0; j < size; j++){
            dOdds[i][j] = dist[odds[i]][odds[j]];
        }
    }

    return dOdds;
}

void addMatchs(int nOdds, int** M, std::vector<int> odds, std::list<int>* tree){
    for(int i = 0; i < nOdds; i++){
        for(int j = 0; j < nOdds; j++){
            if(M[i][j]){
                tree[odds[i]].push_back(odds[j]);
            }
        }
    }
}

int getNext(int i, int u, std::list<int>* tree, int* path, bool* viewed){
    while(!tree[u].empty()){
        int v = tree[u].front();
        tree[u].pop_front();
        if(!viewed[v]){
            return v;
        }
    }
    return getNext(i - 1, path[i - 1], tree, path, viewed);
}

double christofides(int n, double** dist){
    time_t start = time(NULL);

    int* parent = mst(n, dist);
    int* degree = getDegree(n, parent);

    std::list<int>* tree = new std::list<int>[n];
    for(int v = 1; v < n; v++){
        int u = parent[v];
        tree[u].push_back(v);
    }

    std::vector<int> odds = getOdds(n, degree);

    if(odds.size() > 0){
        int nOdds = odds.size();
        double** dOdds = setDistOdds(odds, dist);
        
        int** M = new int*[nOdds];
        for(int i = 0; i < nOdds; i++){
            M[i] = new int[nOdds];
            memset(M[i], 0, sizeof(int) * nOdds);
        }

        if(hungarian(nOdds, dOdds, M, start)){
            return __INT64_MAX__;
        }

        addMatchs(nOdds, M, odds, tree);
    }

    int u = 0, v = 0;
    int path[n];
    bool viewed[n];
    double value = 0;

    for(int i = 0; i < n; i++){
        viewed[i] = false;
        path[i] = -1;
    }

    viewed[0] = true;
    path[0] = 0;
    for(int i = 1; i < n; i++){

        v = getNext(i, u, tree, path, viewed);

        path[i] = v;
        viewed[v] = true;

        value += dist[u][v];
        u = v;
    }

    delete parent;
    delete degree;

    return value + dist[v][0];
}