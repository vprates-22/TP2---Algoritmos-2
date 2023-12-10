#include "node.hpp"

Node::Node(){}

Node::Node(int depth, double bound, double cost, int* paths){
    this->depth = depth;
    this->bound = bound;
    this->cost = cost;
    this->paths = paths;
}

bool Node::operator<(const Node& other) const{
    return this->depth < other.depth || (this->depth == other.depth && this->bound > other.bound);
}