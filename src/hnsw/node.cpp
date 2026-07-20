#include "node.h"

Node::Node(uint32_t id, uint8_t highest_layer, const std::vector<float>& vector) {
    this->id = id;
    this->highest_layer = highest_layer;
    *this->vector = vector;
};

// returns a vector of uint32_t offsets for all M neighbors of the node
void Node::getNeighborOffsets(std::vector<std::vector<uint32_t>>& neighbor_offsets, uint8_t M) {

    int count=0;
    for (uint16_t cur_layer = 0; cur_layer <= this->highest_layer; cur_layer++) {
        while (this->neighborQueues[cur_layer].size() > 0) {
            neighbor_offsets[cur_layer].push_back(this->neighborQueues[cur_layer].top().first.id);
            this->neighborQueues[cur_layer].pop();
            count++;
        }

        if (count < M) {
            neighbor_offsets[cur_layer].push_back(0);
            count++;
        }
        count = 0;
    }
}
