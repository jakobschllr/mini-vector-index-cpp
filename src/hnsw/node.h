#include "shared.h"

class Node {
    private:
        uint32_t offset;
        uint8_t highest_layer;
    
    public: 
        Node(uint32_t offset, uint8_t highest_layer);
        void get_neighbors();
};