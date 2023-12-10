#include "branchAndBound.hpp"

void findTwoSmallest(double* dist, int size, double& smallest, double& secondSmallest) {
    smallest = INT64_MAX;
    secondSmallest = INT64_MAX;

    for (int i = 0; i < size; ++i) {
        if (dist[i] < smallest) {
            secondSmallest = smallest;
            smallest = dist[i];
        } else if (dist[i] < secondSmallest) {
            secondSmallest = dist[i];
        }
    }
}

int in(int e, int n, int* path){
    for(int i = 0; i < n; i++){
        if(e == path[i]){
            return i;
        } else if (path[i] == -1){
            return -1;
        }
    }
    return -1;
}

double estimate(int n, int* path, double** dist, double** best){
    double value = 0;
    double v1, v2;
    for(int i = 0; i < n; i++){
        int inside = in(i, n, path);
        if(inside == -1){
            v1 = best[i][0];
            v2 = best[i][1];
        } else if(path[(inside + 1) % n] == -1){
            v1 = path[(inside + n - 1) % n] == -1 ? best[i][0] : dist[path[(inside + n - 1) % n]][i];
            v2 = best[i][0] == v1 ? best[i][1] : best[i][0];
        } else if(path[(inside + n - 1) % n] == -1){
            v1 = path[(inside + 1) % n];
            v2 = best[i][0] == v1 ? best[i][1] : best[i][0];
        } else {
            v1 = dist[path[(inside + 1) % n]][i];
            v2 = dist[path[(inside + n - 1) % n]][i];
        }
        value += v1 + v2;
    }
    return value/2;
}

int* deepCopy(int n, int* originalArray) {
    int* newArray = new int[n];

    for (int i = 0; i < n; ++i) {
        newArray[i] = originalArray[i];
    }

    return newArray;
}

void print(int n, int* p){
    for(int i = 0; i < n; i++){
        std::cout << p[i] << '\t';
    }
    std::cout << std::endl;
}

double branchAndBound(int n, double** dist){
    int* path = new int[n];
    double** bestEdges = new double*[n];
    
    for(int i = 0; i < n; i++){
        path[i] = -1;
        bestEdges[i] = new double[2];
        findTwoSmallest(dist[i], n, bestEdges[i][0], bestEdges[i][1]);
    }
    path[0] = 0;
    
    double best = INT64_MAX;
    
    std::priority_queue<Node>* queue = new std::priority_queue<Node>();
    queue->push(Node(1, estimate(n, path, dist, bestEdges), 0, path));  

    time_t start = time(NULL);
    Node node;
    while(!queue->empty()){
        if((time(NULL) - start) > TIME_LIMIT){
            break;
        }

        node = queue->top();
        queue->pop();

        if(node.depth > n && node.cost < best){
            best = node.cost;
        } else if(node.bound < best){
            if(node.depth < n){
                for(int i = 1; i < n; i++){
                    if(in(i, n, node.paths) == -1){

                        node.paths[node.depth] = i;

                        double bound = estimate(n, node.paths, dist, bestEdges);

                        if(bound < best){
                            queue->push(Node(node.depth+1, bound, 
                                            node.cost + dist[node.paths[node.depth-1]][i], 
                                            deepCopy(n, node.paths)));
                        }
                    }
                }
            } else if(node.cost + dist[node.paths[n-1]][0] < best){
                queue->push(Node(node.depth+1, 0, 
                                node.cost + dist[node.paths[n-1]][0], 
                                deepCopy(n, node.paths)));
                
            }
        }
        delete node.paths;
    }
    delete queue;
    return best;
}