#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include "nodedata.h"

// Authors: Destiny Rebman and Parisa Soltanian
// Class GraphM implements Dijkstra's shortest path algorithm
// using an adjacency matrix. It supports multiple graphs,
// computes shortest paths between all node pairs, and displays
// the shortest paths and distances.

const int MAXNODES = 101;   // Maximum number of nodes supported
const int INF = 999999;     // Representation of "infinity" for no path

class GraphM {
public:
    GraphM(); // Constructor: Initializes adjacency matrix and tables

    // Reads node data and edges from a file to build the graph
    void buildGraph(std::ifstream& infile);

    // Adds an edge from 'from' to 'to' with given weight
    bool insertEdge(int from, int to, int weight);

    // Removes the edge from 'from' to 'to' by setting it to INF
    bool removeEdge(int from, int to);

    // Computes all-pairs shortest paths using Dijkstra's algorithm
    void findShortestPath();

    // Displays all shortest paths and distances
    void displayAll() const;

    // Displays shortest path from a specific 'from' node to 'to' node
    void display(int from, int to) const;

private:
    NodeData data[MAXNODES];  // Array of node descriptions (1-indexed)
    int C[MAXNODES][MAXNODES]; // Adjacency matrix (C[i][j] = weight from i to j)
    int size;                  // Number of nodes in the graph

    // TableType stores information for Dijkstra algorithm
    struct TableType {
        bool visited;   // Whether the node has been visited
        int dist;       // Distance from source node
        int path;       // Previous node in shortest path
    };

    TableType T[MAXNODES][MAXNODES]; // Table for storing shortest path info

    // Recursive helper to print the path from 'from' to 'to'
    void displayPath(int from, int to) const;

    // Recursive helper to print the node descriptions along the path
    void displayData(int from, int to) const;
};

#endif
