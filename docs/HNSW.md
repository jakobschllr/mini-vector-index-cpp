# HNSW

Level and Layer are the same thing.

## 0. Basic Idea
- Graph where each Node is a vector, the edges between nodes symbolize that nodes are close neighbors
- Graph has multiple layers stacked on top of each other
- layer 0 has all vectors, layer 1 has a random, smaller subset of the vectors and so on
- the higher layers are used to make fast jumps between vastly different areas of the vector space, the lower layers are then used to search more precisly in the denser vector space
- the distance between the vectors is meseared using a distance function (eucledean distance, cosine similarity, Hamming-Distance)

## 1. Saving the first vector
- graph is empty
- add vector q on layer l
- since there aren't any other nodes yet, the neighbor lists can be empty; the vector must be added to each layer in the interval [0,l]
- this node becomes the global entrypoint for the whole structur and l becomes the current highest layer of the graph
- every other insert starts it's seach at this entry point; later the entry point can be updated, if another node with a higher level than l is inserted.
- so there is also exactly one node sitting at the top of the structure

## 2. Calculating a vector's level
- the amount of layers is not fixed beforehand, the actual amount of layers emerges from the random relations between the vectors and increases logarithmically over time
- for each vector the level l (the highest layer of the vector) is calculated:
```
l = floor(-ln(u) * m_l)

u = Unif(0,1) // continuous uniform distribution on the interval (0,1); so a random number between 0 and 1 with equal probality for each area in the interval
m_l = 1 / ln(M)

M is the connectivity parameter (typical Values are between 12 and 48)

On Average every layer has 1/M as many nodes as the layer below that.
```

- the maximum layer-height of the whole graph is simply the maximum of all existing l-Values at a given moment

## 3. How are nodes connected to neighbors
- each node gets a fixed upper limit for the amount of neighbors it can have, separately for each layer (M or for layer 0 the maximum is often 2M)
- which nodes are choosen as neighbors is determined using a heuristic

## 4. Adding a new vector

### Step A
Given the graph isn't empty, a new vector q should be added
1. calculate the level l
2. save ep as the current global entry point and L has the current highest layer
3. Descent (only if l < L): for each layer starting at L down until l+1
- starting at ep, move repeatetly to the closest neighbor of q on the current layer, until no neighbor is closer than the current node. set ep on this current node
- go on layer down and repeat
This phase only touches the layers above from l where q won't be inserted. The only goal here is to find a singular good entry point ep for the connection.

### Step B
Now we want to find connections for the vector from layer l down to layer 0
- do the **Candidate Search** (explained below) with parameter ef_construction, starting at the entry points ep; the result is a list of W of ef_construction candidates, sorted by their distance to q
- apply the **Heuristic For Neighbor Selection** on W, to get the final candidates from W
- insert bidirectional edges between q and their chosen neighbors on the current layer (q gets all the neighbors in its list, all neighbors get q in their list)
- for each of the neighbors: check if the neighbor list of the node extends the allowed maximum amount of neighbors; if the node has too many neighbors, use the same heuristic on the neighbor list again to prune it (now the neighbor list ∪ w) back the the upper limit
- set ep = W, meaning the found neighbors are the starting points for the layer below

### Step C
- update the global entry point, if l > L (meaning the the vector has the highest layer).
- q is then the new global entry point and the maximum height of the graph is set to l (L = l)


## Candidate Search
- used at layer 0 for search and for every layer from l for inserting
- input is the query-vector q, a set of entry points, a target-size ef (how many candidates should be returned at the end) and the layer which should be used

Necessary are two data structures:
- Candidate-Queue C: Priority-Queue, which contains the nodes where the neighbors weren't visited yet; sorted from lowest distance to q to highest distance to q (best-first-search); this Queue returns next the most promising next candidate with the lowest distance to q
- Result-Queue W: Priority-Queue, which contains the ef best candidates (lowest distance to q), should be sorted from highest distance to q; so that the first element is the one with the highest distance to q compared to all other elements
- set V which contains the visited nodes, so now node is visited twice

Algorithm:
- initialize C, W and V each with the entry points ep
- While C is not empty:
    - choose from C the node c with the smallest distance to q (the first one)
    - select f = the node in W with the largest distance to q
    - if d(q,c) > d(d,f) then we can break the loop, since the even the most promising candidate from C has further away from q, than the most distant element at this point
    - else: for each neighbor e of c in the graph, which isn't yet in V
        - add e to V (mark as visited)
        - get f again (worst candidate from W)
        - if d(q,e) < d(q,f) or if W hasn't reached the full size ef
            - add e to C (for further exploration) and to W (as possible result candidate)
            - if W thereby got bigger then ef, remove the worst candidate from W

- Return W (W equals the the maximum of ef closest neighbors to q on this layer)

This is a Best-First-Search Algorithm: We search from the most promising nodes for even better ones, keep only the ef best ones and stop, once there's no improvement.

## Heuristic for Neighbor Selection
At this point we have a List W containing the ef closest neighbors to q. Now we want to choose the M best neighbors.
- sort the candidates in an ascending order based on their distance to q (from smallest to largest distance)
- go through the candidates in this order, keeping a result set R (empty at the beginning)
- for each candidate e:
    - add e to R, only if e is closer to q than any element alread in R
    - stop if R has reached the size M or if all candidates from W were checked.


## Searching the nearest neighbors for a query vector q
Goal: Find the K most similar vectors to a query vector q, with accuracy parameter ef_search
- 1: ep = current global entrypoint, L = current highest Layer
- 2: Rough Descent from layer L to layer 1; for each layer lc from L to 1:
    - do the Candidate Search with ef=1, based on ep on layer lc
    - the result is only one node, the closest reachable vector
    - set ep to this single closest vector

Here no candidate pool is really build, really only the best node is always used.

- 3: Granular search on layer 0
    - apply the full Candidate Search with full ef_search, starting from the last found ep, on layer 0

- 4: From the result list W choose the K nearest neighbors to q (with K <= ef_search), this is the result


## ef and ef_construction
- ef: size of candidate list during search with query vector
    - the higher the value the better the k result vectors, on the downside more calcucations and longer runtime
    - can be changed for each search, depending on whether time or accuray is more important
- ef_construction: size of candidate list during insertion of a new vector
    - the higher the value, the more accurate the position of the vector in the vector space; the neighbors are better. On the downside the insertion takes more time