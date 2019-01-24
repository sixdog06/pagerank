#include <stdio.h>
#include <stdlib.h>

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
	double maxIterations = atof(argv[3]);
	printf("%.10f %.10f %.10f\n", d, diffPR, maxIterations);
	// initialize double linked list to store the file names
	DLListStr L = GetCollection();
	// initialize the graph and store the url in it
	Graph G = newGraph(L->nitems);
	GetGraph(G, L);
	// calculate the pagerank
	

	showGraph(G);
	return 0;
}