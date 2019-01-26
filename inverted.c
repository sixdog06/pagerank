#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"
#include "InvertedIdx.h"

int main(void) {
	FILE *fp;
	fp = fopen("invertedIndex.txt", "w+");
	DLListStr L = GetCollection();
	Tree t = newTree();
	DLListNode *node = L->first;
	
	while(node != NULL) {
		t = readSection2(node->value, t);
		node = node->next;
	}
	// save tree to
	saveTree(t, fp);
	free(t);
	return 0;
}