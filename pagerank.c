#include <stdio.h>
#include <stdlib.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"

// set the initialize PR to 1/N
void Init_graph(Graph g, int N) {
    if(g == NULL) {
    	return;
    }
    int i, j;
    for (i = 0; i < g->nV; i++) {
			g->pr[i] = g->pr[i] / N;
    }
}

void PageRank(Graph g, DLListStr L, double d, double diffPR, double maxIteration) {
	int iteration = 0;
	double diff = diffPR;
	int N = L->nitems;
	double temp[N];
	double sum;
	int i, j;

	while(iteration < maxIteration && diff >= diffPR) {
		iteration++;
		for(i = 0; i < N; i++) {
			sum = 0;
			for(j = 0; j < N; j++) {
				if(g->edges[j][i] == 1) {
					sum += g->pr[j] / outdegreeGraph(g, j);
					
				}
			}
			temp[i] = (1 - d) / N + d * sum;
		}
		
		for(i = 0; i < N; i++) {
			//printf("temp is %.7f\n", temp[i]);
			g->pr[i] = temp[i];
		}
	}
}

int main(int argc, char *argv[]) {
	if(argc != 4) {
		//printf("error");
		return 0;
	} 
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	double maxIteration = atof(argv[3]);
	printf("%.10f %.10f %.10f\n", d, diffPR, maxIteration);
	// initialize double linked list to store the file names
	DLListStr L = GetCollection();

	// initialize the graph and store the url in it
	Graph g = newGraph(L->nitems);
	GetGraph(g, L);

	// calculate the pagerank
	Init_graph(g, L->nitems);
	PageRank(g, L, d, diffPR, maxIteration);
	showGraph(g);
	return 0;
}