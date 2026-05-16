# euler-graph-c
Implementation of Hierholzer's algorithm for finding Eulerian circuits in a graph

## Features
- Adjacency list graph representation
- Eulerian circuit detection
- Hierholzer's algorithm for finding the circuit

## Compile and run
make        # compile
./graph     # run
make clean  # remove binary

## How this works
A graph is Eulerian if it is connected and all vertices of which have even degrees. Hierholzer's algorithm finds the circuit by traversing edges and splicing sub-circuits together until all edges are used.
