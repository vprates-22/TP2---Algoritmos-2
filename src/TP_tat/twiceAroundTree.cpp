#include "twiceAroundTree.hpp"

int getNext(int u, std::list<int>* tree, int* parent, bool* viewed){
    while(!tree[u].empty()){
        int v = tree[u].front();
        tree[u].pop_front();
        if(!viewed[v]){
            return v;
        }
    }
    return getNext(parent[u], tree, parent, viewed);
}

double twiceAroundTree(int n, double** dist){
    int* parent = mst(n, dist);
    
    std::list<int>* tree = new std::list<int>[n];
    for(int v = 1; v < n; v++){
        int u = parent[v];
        tree[u].push_back(v);
    }

    int u = 0, v = 0;
    bool viewed[n];
    double value = 0;

    for(int i = 0; i < n; i++){
        viewed[i] = false;
    }

    viewed[0] = true;


    for(int i = 1; i < n; i++){
        
        v = getNext(u, tree, parent, viewed);

        viewed[v] = true;

        value += dist[u][v];
        u = v;
    }

    delete parent;

    return value + dist[v][0];
}