# Mini-BITVEC

## Ressources:
- https://deepwiki.com/qdrant/qdrant/3.2-hnsw-index-implementation
- https://github.com/nmslib/hnswlib

## API-Documentation

- create_index(str name): creates new empty index with unique reference
- load_index(str name): loads existing index by its name 
- add_elements(): adds elements to index
- remove_element(element_id)
- search_k_neighbors(query v)