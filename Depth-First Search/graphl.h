#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include <fstream>
#include "nodedata.h"

// Authors: Destiny Rebman and Parisa Soltanian
// GraphL class implements Depth-First Search using adjacency lists
// Supports multiple graphs and prints DFS ordering starting at Node 1

const int MAXNODES = 101;

class GraphL {
private:
    struct EdgeNode {
        int adjGraphNode;  // node this edge points to
        EdgeNode* nextEdge; // pointer to next edge in adjacency list
    };

    struct GraphNode {
        EdgeNode* edgeHead; // head of adjacency list
        NodeData* data;     // node description
        bool visited;       // visited flag for DFS
    };

    GraphNode graphNodes[MAXNODES]; // nodes array (1-indexed)
    int size;                        // number of nodes

    void dfsHelper(int v);  // recursive DFS helper

public:
    GraphL();                   // constructor: initializes graph
    ~GraphL();                  // destructor: frees memory
    void buildGraph(std::ifstream& infile); // reads nodes and edges
    void displayGraph() const;  // prints adjacency list
    void depthFirstSearch();    // prints DFS ordering starting at node 1
};

#endif
