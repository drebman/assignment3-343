#include "graphm.h"

// ---------------- Constructor ----------------
// Initializes the adjacency matrix to INF (no edges) and
// initializes the Dijkstra table to default values
GraphM::GraphM() {
    size = 0;

    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            C[i][j] = INF;       // No edges initially
            T[i][j].dist = INF;  // Distances are unknown
            T[i][j].visited = false;
            T[i][j].path = 0;    // No previous node
        }
    }
}

// ---------------- buildGraph ----------------
// Reads the number of nodes, node descriptions, and edges from a file
void GraphM::buildGraph(std::ifstream& infile) {
    infile >> size;
    if (infile.eof()) return;   // If file is empty, do nothing

    std::string s;
    std::getline(infile, s);   // Skip to the next line after number of nodes

    // Read node descriptions
    for (int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }

    // Read edges in the format: from to weight
    int from, to, weight;
    for (;;) {
        infile >> from >> to >> weight;
        if (from == 0 && to == 0 && weight == 0) break; // End of edges
        C[from][to] = weight;  // Set adjacency matrix
    }
}

// ---------------- insertEdge ----------------
// Inserts an edge into the adjacency matrix
bool GraphM::insertEdge(int from, int to, int weight) {
    if (from < 1 || from > size || to < 1 || to > size || weight < 0)
        return false;  // Invalid node or negative weight

    C[from][to] = weight;
    return true;
}

// ---------------- removeEdge ----------------
// Removes an edge by setting its weight to INF
bool GraphM::removeEdge(int from, int to) {
    if (from < 1 || from > size || to < 1 || to > size)
        return false;  // Invalid node

    C[from][to] = INF;
    return true;
}

// ---------------- findShortestPath ----------------
// Computes shortest paths from every node to every other node
// using Dijkstra's algorithm
void GraphM::findShortestPath() {
    for (int source = 1; source <= size; source++) {
        // Initialize Dijkstra table for this source node
        for (int i = 1; i <= size; i++) {
            T[source][i].dist = INF;
            T[source][i].visited = false;
            T[source][i].path = 0;
        }

        T[source][source].dist = 0; // Distance to itself is 0

        // Loop over all nodes
        for (int i = 1; i <= size; i++) {
            int v = 0;
            int minDist = INF;

            // Find the unvisited node with smallest distance
            for (int j = 1; j <= size; j++) {
                if (!T[source][j].visited && T[source][j].dist < minDist) {
                    minDist = T[source][j].dist;
                    v = j;
                }
            }

            if (v == 0) break;  // No more reachable nodes

            T[source][v].visited = true; // Mark node visited

            // Update distances to neighbors of v
            for (int w = 1; w <= size; w++) {
                if (!T[source][w].visited && C[v][w] != INF) {
                    if (T[source][v].dist + C[v][w] < T[source][w].dist) {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;  // store previous node
                    }
                }
            }
        }
    }
}

// ---------------- displayAll ----------------
// Prints all shortest paths from every node to every other node
void GraphM::displayAll() const {
    std::cout << "Description           From node  To node  Dijkstra's  Path\n";

    for (int from = 1; from <= size; from++) {
        std::cout << data[from] << std::endl;

        for (int to = 1; to <= size; to++) {
            if (from == to) continue;

            std::cout << std::setw(20) << from
                      << std::setw(10) << to;

            if (T[from][to].dist == INF)
                std::cout << std::setw(10) << "----"; // unreachable
            else {
                std::cout << std::setw(10) << T[from][to].dist << "     ";
                displayPath(from, to);  // display path as node sequence
            }
            std::cout << std::endl;
        }
    }
}

// ---------------- display ----------------
// Prints shortest path and distance from 'from' node to 'to' node
void GraphM::display(int from, int to) const {
    if (T[from][to].dist == INF) {
        std::cout << from << " " << to << " ----" << std::endl;
        return;
    }

    std::cout << from << " " << to << " "
              << T[from][to].dist << " ";

    displayPath(from, to);  // recursive path printing
    std::cout << std::endl;

    displayData(from, to);  // print node names along path
    std::cout << std::endl;
}

// ---------------- displayPath ----------------
// Recursive helper: prints the node numbers along the path
void GraphM::displayPath(int from, int to) const {
    if (T[from][to].path != 0) {
        displayPath(from, T[from][to].path);
    }
    std::cout << to << " ";
}

// ---------------- displayData ----------------
// Recursive helper: prints the node descriptions along the path
void GraphM::displayData(int from, int to) const {
    if (T[from][to].path != 0) {
        displayData(from, T[from][to].path);
    }
    std::cout << data[to] << std::endl;
}
