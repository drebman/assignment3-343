# CSS 343 – Assignment 3

Data Structures, Algorithms, and Discrete Mathematics II
Total: 100 points (12% of course grade)

This assignment consists of two parts:

Part 1 (6%) – Dijkstra’s Shortest Path Algorithm

Part 2 (6%) – Depth-First Search (DFS)

📌 Part 1 – Dijkstra’s Shortest Path (GraphM)
🎯 Objective

Implement Dijkstra’s shortest path algorithm using an adjacency matrix.

Your program must:

Read graph data from a file (e.g., data31.txt)

Compute shortest paths between every node and every other node

Display:

All shortest paths

A specific shortest path in detail

📥 Input Format (data31.txt)
<number of nodes>
<description of node 1>
<description of node 2>
...
<description of node n>
<from> <to> <weight>
<from> <to> <weight>
...
0 0 0
Notes:

Maximum nodes per graph: 100

Node descriptions: max 50 characters

0 0 0 indicates the end of a graph

Multiple graphs may appear in the file

🏗 Class Design – GraphM
class GraphM {
public:
    GraphM();
    void buildGraph(ifstream&);
    bool insertEdge(int from, int to, int weight);
    bool removeEdge(int from, int to);
    void findShortestPath();
    void displayAll() const;
    void display(int from, int to) const;

private:
    NodeData data[MAXNODES];
    int C[MAXNODES][MAXNODES];        // adjacency matrix (costs)
    int size;                        // number of nodes

    struct TableType {
        bool visited;
        int dist;
        int path;
    };

    TableType T[MAXNODES][MAXNODES];
};
🧠 Dijkstra Algorithm Logic

For each source node:

for (int source = 1; source <= nodeSize; source++) {
    T[source][source].dist = 0;

    for (int i = 1; i <= nodeSize; i++) {
        find v (smallest unvisited distance)
        mark v visited

        for each w adjacent to v:
            if w not visited:
                update distance and path
    }
}
Important Notes:

Index 0 is unused

All distances initialized to infinity

path stores the previous node in the shortest path

🖥 Required Functions
✔ Constructor

Initialize:

dist = ∞

visited = false

path = 0

✔ buildGraph

Reads file

Stores node descriptions

Builds adjacency matrix

✔ insertEdge / removeEdge

Modify graph edges

✔ findShortestPath

Computes shortest paths for all node pairs

✔ displayAll

Displays:

From node  To node  Distance  Path
✔ display(from, to)

Displays:

1 4 50
1 3 2 4
Aurora and 85th
Woodland Park Zoo
Green Lake Starbucks
Troll under bridge
📂 Supporting Files

data31.txt – Input data

dataUWB.txt – Additional dataset

nodedata.h / nodedata.cpp

lab3.cpp

lab3output.txt

⚠ Note: lab3.cpp includes code for Part 2 — comment it out when testing Part 1.

📌 Part 2 – Depth-First Search (GraphL)
🎯 Objective

Implement DFS using an adjacency list.

DFS must always start at Node 1

Display graph structure

Output DFS ordering

📥 Input Format (data32.txt)
<number of nodes>
<description of node 1>
...
<description of node n>
<from> <to>
<from> <to>
...
0 0
Notes:

Edges for node 1 listed first, then node 2, etc.

Insert edges at the beginning of the adjacency list

Output edges will appear in reverse order of input

🏗 Class Design – GraphL
struct EdgeNode;

struct GraphNode {
    EdgeNode* edgeHead;
    NodeData* data;
    bool visited;
};

struct EdgeNode {
    int adjGraphNode;
    EdgeNode* nextEdge;
};

class GraphL {
public:
    GraphL();
    ~GraphL();
    void buildGraph(ifstream&);
    void displayGraph() const;
    void depthFirstSearch();

private:
    GraphNode graphNodes[MAXNODES];
};
✔ Required Functions
✔ Constructor / Destructor

Initialize nodes

Free all dynamic memory

✔ buildGraph

Build adjacency list

Insert edges at beginning of list

✔ displayGraph

Displays:

Graph:
Node 1 Aurora and 85th
  edge 1 2
  edge 1 3
...
✔ depthFirstSearch

Outputs:

Depth-first ordering: 1 2 4 3 5
🔎 Implementation Details

Process edges in list order

Always insert new edges at head of list

DFS must respect adjacency list ordering

No edge sorting allowed

📝 Submission Requirements

Follow Assignment 1 submission rules

Proper formatting and code documentation required

Program must compile and run correctly

Memory must be properly managed (no leaks)

🚀 Summary
Part	Algorithm	Representation	Key Feature
1	Dijkstra	Adjacency Matrix	All-pairs shortest path
2	DFS	Adjacency List	Recursive traversal
