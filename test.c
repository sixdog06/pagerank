#include <stdio.h>
#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"


int main(void) {
/*	
	// test DLListStr.c DLListStr.h
	DLListStr L = newDLListStr();
	insertSetOrd(L, "url12");
	insertSetOrd(L, "url13");
	insertSetOrd(L, "url11");
	insertSetOrd(L, "url15");
	insertSetOrd(L, "url15");
	insertSetOrd(L, "url18");
	insertSetOrd(L, "url17");
	insertSetOrd(L, "url14");
	insertSetOrd(L, "url16");
	showDLListStr(L);
*/

	// test readData 1
	
	DLListStr L = GetCollection();
	Graph G = newGraph(L->nitems);
	readSection1("url11.txt", G, L);
	readSection1("url21.txt", G, L);
	readSection1("url22.txt", G, L);
	readSection1("url23.txt", G, L);
	readSection1("url31.txt", G, L);
	readSection1("url32.txt", G, L);
	readSection1("url34.txt", G, L);

	/*
	// test graph and double linked list
	DLListStr L = GetCollection();
	showDLListStr(L);
	for(int i = 0; i < 7; i++) {
	    printf("%s ", show_a_Str(L, i));
		//printf("%d\n", show_Index(L, show_a_Str(L, i)));
	}
	
	Graph g = newGraph(L->nitems);
	GetGraph(L, g);
	showGraph(g);
*/
	return 0;
}

