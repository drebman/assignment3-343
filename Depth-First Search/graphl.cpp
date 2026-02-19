#include "graphl.h"

// ---------------- Constructor ----------------
// Initializes graph nodes
GraphL::GraphL() {
    size = 0;
    for (int i = 0; i < MAXNODES; i++) {
        graphNodes[i].edgeHead = nullptr;
        graphNodes[i].data = nullptr;
        graphNodes[i].visited = false;
    }
}

// ---------------- Destructor ----------------
// Frees all dynamic memory used by edges and node data
GraphL::~GraphL() {
    for (int i = 1; i <= size; i++) {
        EdgeNode* current = graphNodes[i].edgeHead;
        while (current != nullptr) {
            EdgeNode* temp = current;
            current = current->nextEdge;
            delete temp;  // delete each edge
        }
        delete graphNodes[i].data; // delete node description
    }
}

// ---------------- buildGraph ----------------
// Reads node descriptions and edges from file
void GraphL::buildGraph(std::ifstream& infile) {
    infile >> size;
    if (infile.eof()) return;

    std::string s;
    std::getline(infile, s); // skip to next line

    // Read node descriptions
    for (int i = 1; i <= size; i++) {
        graphNodes[i].data = new NodeData;
        graphNodes[i].data->setData(infile);
    }

    // Read edges (from -> to)
    int from, to;
    for (;;) {
        infile >> from >> to;
        if (from == 0 && to == 0) break; // end of edge list

        // Insert new edge at head of adjacency list
        EdgeNode* edge = new EdgeNode;
        edge->adjGraphNode = to;
        edge->nextEdge = graphNodes[from].edgeHead;
        graphNodes[from].edgeHead = edge;
    }
}

// ---------------- displayGraph ----------------
// Prints all nodes and their edges
void GraphL::displayGraph() const {
    std::cout << "Graph:\n";

    for (int i = 1; i <= size; i++) {
        std::cout << "Node " << i << " " << *graphNodes[i].data << std::endl;

        EdgeNode* current = graphNodes[i].edgeHead;
        while (current != nullptr) {
            std::cout << "   edge " << i << " " << current->adjGraphNode << std::endl;
            current = current->nextEdge;
        }
    }
}

// ---------------- depthFirstSearch ----------------
// Prints DFS ordering starting at Node 1
void GraphL::depthFirstSearch() {
    // Reset visited flags
    for (int i = 1; i <= size; i++)
        graphNodes[i].visited = false;

    std::cout << "Depth-first ordering: ";

    // Start DFS at each unvisited node (ensures all components visited)
    for (int i = 1; i <= size; i++) {
        if (!graphNodes[i].visited)
            dfsHelper(i);
    }
    std::cout << std::endl;
}

// ---------------- dfsHelper ----------------
// Recursive DFS traversal from node v
void GraphL::dfsHelper(int v) {
    graphNodes[v].visited = true;
    std::cout << v << " ";  // print node as visited

    // Visit all neighbors in adjacency list
    EdgeNode* current = graphNodes[v].edgeHead;
    while (current != nullptr) {
        if (!graphNodes[current->adjGraphNode].visited)
            dfsHelper(current->adjGraphNode);
        current = current->nextEdge;
    }
}
