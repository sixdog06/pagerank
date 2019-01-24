// Graph ADT interface ... COMP9024 19T0
// modified by huanrui

typedef struct GraphRep {
   int **edges;   // adjacency matrix
   double *pr;     // pagerank array
   int nV;      // #vertices
   int nE;      // #edges
} GraphRep;

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
void  insertEdge(Graph, Edge);
void  showGraph(Graph);
void  freeGraph(Graph);
int outdegreeGraph(Graph g, int v);
int indegreeGraph(Graph g, int v);