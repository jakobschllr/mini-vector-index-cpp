#include "node.h"

Node::Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector) {
    this->id = id;
    this->highest_layer = highest_layer;
    *this->vector = vector;
};

// returns a vector of uint32_t offsets for all M neighbors of the node
void Node::getNeighborOffsets(std::vector<uint32_t>& neighbor_offsets, uint8_t M) {
    int count=0;
    while (this->neighborQueue.size() > 0) {
        neighbor_offsets.push_back(this->neighborQueue.top().first.id);
        this->neighborQueue.pop();
        count++;
    }

    if (count < M) {
        neighbor_offsets.push_back(0);
        count++;
    }
}