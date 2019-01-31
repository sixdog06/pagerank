#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"

int main(int argc, char *argv[]) {
	if(argc != 4) {
		//printf("error");
		return 0;
	} 
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	double maxIteration = atof(argv[3]);

	// initialize double linked list to store the file names
	DLListStr L = GetCollection();

	// initialize the graph and store the url in it
	Graph g = newGraph(L->nitems);
	GetGraph(g, L);

	// calculate the pagerank
	Init_graph(g, L->nitems);
	PageRank(g, L, d, diffPR, maxIteration);
	Order(g, L);

 	//showDLListStr(L);
	//showGraph(g);
	return 0;
}
