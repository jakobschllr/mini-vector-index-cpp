#include "node.h"

Node::Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector) {
    this->id = id;
    this->highest_layer = highest_layer;
    *this->vector = vector;
};

void Node::get_neighbors() {
    
}