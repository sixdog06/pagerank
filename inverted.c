#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"
#include "InvertedIdx.h"

int main(void) {
	DLListStr L = GetCollection();
	
	Tree t = newTree();
	
/*	TreeInsert(t, "avacasca2");
	TreeInsert(t, "avacasca1");
	TreeInsert(t, "avacasca10");*/
	DLListNode *node = L->first;
	while(node != NULL) {
		t = readSection2(node->value, t);
		node = node->next;
	}
	showTree(t);
	free(t);
	return 0;
}