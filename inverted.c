#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"
#include "InvertedIdx.h"

int main(void) {
	//DLListStr L = GetCollection();
	
	Tree t = newTree();
	
	t = TreeInsert(t, "avacasca5");
/*	TreeInsert(t, "avacasca2");
	TreeInsert(t, "avacasca1");
	TreeInsert(t, "avacasca10");*/
	readSection2("url11", t);
	if(t == NULL) {
		printf("yes!!!!!!\n");
	} else {
		printf("no!!!!!!\n");
	}
	showTree(t);
	free(t);
	return 0;
}