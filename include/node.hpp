#ifndef NODE_H
#define NODE_H

class Node{
    public:
        int depth;
        double bound;
        double cost;
        int* paths;

        Node();
        Node(int depth, double bound, double cost, int* paths);
        bool operator<(const Node& other) const;
};

#endif