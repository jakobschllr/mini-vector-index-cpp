# Architecture Learnings from hnswlib

## General
- use mutexes for locking critical areas in the code
- use templates for using different distance types within the same class
- use `mutable` to make variables (like mutex) mutable within const-functions
- use atmotic variables if it makes sense
- store a list of deleted elements somewhere, to mark certain vectors as deleted.
- separate classes for queues (visited list etc.)
- datatype (template class) for distance metric
- python-bindings for easy usage with python
- hnswlib uses internal IDs (the index of the elements in the vector array) and labels; labels are the external IDs for elements in the graph; a lable-lookup is used for mapping internal to external IDs.
- hnswlib is a header only implementation, since a lot of templates are used.

## Key-Functions
- searchBaseLayer
- getNeighborsByHeuristic2
- mutuallyConnectNewElement
- saveIndex
- loadIndex
- markDelete
- searchKnn