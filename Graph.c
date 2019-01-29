// Graph ADT interface ... COMP9024 19T0
// modified by huanrui

#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

Graph newGraph(int V) {
    if(V < 0) {
        return NULL;
    }
   int i;

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;

   // allocate memory for each row
   g->edges = malloc(V * sizeof(int *));
   

   // allocate memory for each column and initialise with 0
   for(i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
    }
   g->pr = malloc(V * sizeof(double)); // initialize after edge array to avoid error
   for(i = 0; i < V; i++) {
		g->pr[i] = 1;
    }
   return g;
}

void insertEdge(Graph g, Edge e) {
    if(g == NULL) {
        return;
    }
    if(!g->edges[e.v][e.w]) {  // edge e not in graph
      g->edges[e.v][e.w] = 1;
      g->nE++;
   }
}

void showGraph(Graph g) {
    if(g == NULL) {
        return;
    }
    int i, j;
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n\n", g->nE);
    for (i = 0; i < g->nV; i++) {
        printf("pagerank of %d is %.7f\n", i, g->pr[i]);
        printf("outdegree is %d\n", outdegreeGraph(g, i));
        printf("indegree is %d\n", indegreeGraph(g, i));
        for (j = 0; j < g->nV; j++) {
            if (g->edges[i][j] > 0) {    
                printf("Edge %d - %d\n", i, j);
            }
        }
        printf("\n");
    }
}

void freeGraph(Graph g) {
    if(g == NULL) {
        return;
    }
    int i;
    for (i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->pr);
    free(g);
}

// return the outdegree of a vertex
int outdegreeGraph(Graph g, int v) {
    int i;
    int n = 0;
    for(i = 0; i < g->nV; i++) {
        if(g->edges[v][i] > 0) {
            n++;
        }
    }
    return n;
}

// return the indegree of a vertex
int indegreeGraph(Graph g, int v) {
    int i;
    int n = 0;
    for(i = 0; i < g->nV; i++) {
        if(g->edges[i][v] > 0) {
            n++;
        }
    }
    return n;
}

// return the indegree of a vertex
int is_indegreeGraph(Graph g, int v, int w) {
    int i;
    int n = 0;
    for(i = 0; i < g->nV; i++) {
        if(g->edges[i][v] > 0) {
            n++;
        }
    }
    return n;
}
