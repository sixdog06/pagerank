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
/*
	// test readData 1
	Graph G = newGraph(1);
	readSection1("url11.txt", G);
	readSection1("url21.txt", G);
	readSection1("url22.txt", G);
	readSection1("url23.txt", G);
	readSection1("url31.txt", G);
	readSection1("url32.txt", G);
	readSection1("url34.txt", G);
*/
	// test graph and double linked list
	DLListStr L = GetCollection();
	showDLListStr(L);
	for(int i = 0; i < 7; i++) {
	    printf("%s ", show_a_Str(L, i));
		printf("%d\n", show_Index(L, show_a_Str(L, i)));
	}
	return 0;
}

