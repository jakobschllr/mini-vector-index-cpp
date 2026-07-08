#include "shared.h"

class Node {
    private:
        uint32_t offset;
    
    public: 
        Node(uint32_t offset);
        void get_neighbors();
};