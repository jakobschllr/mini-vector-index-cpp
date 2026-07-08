# Mini-BITVEC

## Ressources:
- https://deepwiki.com/qdrant/qdrant/3.2-hnsw-index-implementation

## Concept
- use hamming-distance for vector comparison
- if too many vectors (chunks) are close, add something for sharper separation
- HNSW using Hamming Distnace as distance metric between vectors
- using mmap, I can load a file from the hard drive (e.g. a custom database file)

## How the program works
- create: Create a new vector database
- store: Store a new vector into the vector database
- get: give a vector as a input and get the closest matching vectors / chunks back
- all vector-stores are saved at the path, which can be specified during install (for example
  /Users/jakobschiller/.1_bit_mini_vector_db/vector_stores/<name>.bin)
- in the same location there should be a config-file: /Users/jakobschiller/.1_bit_mini_vector_db/config.toml; the config file should determine the default location of the vector stores

## mmap
- takes a certain window (mapping) from original file and map it directly into user space of process
- when using parts of the window, only the necessary pages (mostly pages of 4KB) are loaded from the window, e.g. if the file and mapping are both 50MB and the first 2MB and last 2MB are read, the space in between (46MB) are never mapped to the page cache.


## Optimization ideas
- calculation of l uses floating point numbers and logarithms, maybe there's a smarter / faster way to do that? Maybe using LUTs?