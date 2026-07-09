# Architecture

## Classes

### class HNSWIndex
- references two graph structures:
    - SearchGraph: Immutable, only for searching nearest neighbors to query vector (reads directly using interfaces that use mmap)
    - MutateGraph: Mutable, for inserting, deleting (RAM only for now)

### class Node
- attributes:
    - ID (unique offset withing the binary vector file)
    - n references to n neighbor-lists for each of the n layers the node is on
    - original-vector
    - quantized vector (1-Bit or higher quantization)
    - flag: is_deleted
    - edge_data: offset in edges.bin that points to the position where the neighbors-data for this node is stored


## File-structure

### vectors.bin
- saves the bytes for each node

### graph.bin
- for each node, saves the neighbor-list for each layer
- a neighbor is referenced by the node-offset in the vectors.bin file
- using a lookahead table, example with 3 layers:
```

    | highest_layer=3 | layer-0-neighbors-amount | layer-0-list-start-offset | layer-1-neighbors-amount | layer-1-list-start-offset | layer-0-neighbor-list (n1,n2,n3) | layer-1-neighbor-list (n1,n2,n3) | ...

offset=0                                               . + 16 Byte                   8 Byte                  8 Byte                       start of list!            
                                                            |                                                                                  /|\
                                                            |                                                                                   |
                                                            -------------------------------------------------------------------------------------
```
- the neighbors amount and offsets should be ordered by the layer-number, so the layer-0-amount and -offset are always at offset 0, layer-1-amount and -offset are always after that and so on (--> O(1))
- n1,n2,n3 ... are the offsets of the references nodes within the vectors.bin file
- IMPORTANT: the neighbor list all need to have a fixed size and must track how many neighbors are existing; this is a simplification for easier insertion

## mmap and memory interfaces

### Constructing the Graph (adding a vector; performance here isn't critical)
- use RAM-only: load graph structure into RAM and write updated graph to binary file
- after Graph was updated it needs to be written to the file using an interface `update_graph(hnsw_index)` that writes to the file with mmap
- later maybe find a more advanced approach, since loading the whole graph structure in RAM is a lot of memory


### Searching in the Graph (performance is important)
- only the necessary data is loaded from the harddrive using specifig interfaces, e.g. start with `get_global_ep(hnsw_index)` etc.
- parse the whole graph using the abstract interfaces (e.g. `get_neighbors(node_id, layer)`)


### Reading and writing to memory (using mmap)
- implement interfaces that handle the memory reading and writing
- memory needs to be handled completely separately from the search engine
- examples for necessary memory-interfaces:
    - get_vector(id) // the id of a vector is its unique offset-adress withing the vector-binary-file
    - get_neighbors(id, layer)
- for testing the search engine, each interface should exist also in a RAM-only variant without mmap