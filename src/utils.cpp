#include "utils.hpp"

int minKey(int n, double* cost, bool* viewed){
    int index = 0;
    double minK = __INT_MAX__;
    for(int i = 0; i < n; i++){
        if(viewed[i] == false && cost[i] < minK){
            minK = cost[i];
            index = i;
        }
    }
    return index;
}

int* mst(int n, double** dist){
    int* parent = new int[n];
    double cost[n];
    bool viewed[n];

    for(int i = 0; i < n; i++){
        parent[i] = -1;
        viewed[i] = false;
        cost[i] = __INT_MAX__;
    }

    cost[0] = 0;
    viewed[0] = true;

    for(int i = 0; i < n; i++){
        int u = minKey(n, cost, viewed);

        viewed[u] = true;

        for(int v = 0; v < n; v++){
            if(viewed[v] == false && dist[u][v] < cost[v]){
                cost[v] = dist[u][v];
                parent[v] = u;
            }
        }
        
    }
    return parent;
}

Map* readFile(std::string fileName, int &nS){
    std::ifstream inputFile(fileName);

    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the file
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    // Extract data from the lines
    int n = std::stoi(lines[3].substr(lines[3].find(":") + 1));
    nS = n;
    Map* mapa = new Map(n);

    for (size_t i = 6; i < lines.size(); ++i) {
        if (lines[i].find("EOF") != std::string::npos) {
            break;
        }

        std::istringstream iss(lines[i]);
        int a;
        double b, c;
        iss >> a >> b >> c;
        mapa->addCity(a, b, c);
    }

    inputFile.close();

    return mapa;
}