#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"
#include "InvertedIdx.h"

void findMatchedUrls(FILE pr_file, char *word) {

	;
}

int main(int argc, char *argv[]) {

	double d = 0.85; //atof(argv[1]);
	double diffPR = 0.00001; //atof(argv[2]);
	double maxIteration = 1000; //atof(argv[3]);

	// initialize double linked list to store the file names
	DLListStr L = GetCollection();

	// initialize the graph and store the url in it
	Graph g = newGraph(L->nitems);
	GetGraph(g, L);

	// calculate the pagerank
	Init_graph(g, L->nitems);
	PageRank(g, L, d, diffPR, maxIteration);
	Order(g, L);

	FILE *fp;
	fp = fopen("invertedIndex.txt", "w+");
	L = GetCollection();
	Tree t = newTree();
	DLListNode *node = L->first;
	
	while(node != NULL) {
		t = readSection2(node->value, t);
		node = node->next;
	}
	// save tree to file
	saveTree(t, fp);

	free(t);
	free(L);


	return 0;
}