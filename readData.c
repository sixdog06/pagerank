#include <string.h>
#include <stdio.h>

#include "Graph.h"
#include "readData.h"
#include "DLListStr.h"

//#include "InvertedIdx.h"

/*
  A possible way to read data ... 

*/


void readSection1(char *urlname, Graph g, DLListStr L){

/*
   let's say urlname is "url31"
   Open "url31.txt"
   read Section-1 
	(How?, a simple approach ... 
	 skip lines until first two tokens are "#start" and  "Section-1"
	 read lines (tokens) and add the required links in graph g
	 stop reading when first two tokens are "#end" and  "Section-1"
	)
*/
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING] ;
	FILE *f;
	int flag = 0; // if flag = 1, capture the urls

	// open a vaild file
	if((f = fopen (urlname, "r")) == NULL) {
		return;
	}

	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		//printf("line is %s\n", line);
		if(strcmp(line, "#end Section-1") == 0) {
			return;
		}
		if(flag == 1) {
	        token = strtok(line, delim);
			while(token != NULL) {
				if(strcmp(token, "\n") != 0) {
					printf("word is %s\n", token);

					//Edge e;
					//e.v = show_Index(L, temp);
					//e.w = show_Index(L, token);
					//printf("eee = %d eee = %d\n", e.v, e.w);
					//insertEdge(g, e);
				}
				token = strtok(NULL, delim);
			}
		}
		if(strcmp(line, "#start Section-1") == 0) {
			flag = 1;
		}
	}
}

/*
void readSection2(char *filename, InvertedIdx idx){

   let's say filename is "url31.txt"
   Open "url31.txt"
   read Section-2 
	(How?, a simple approach ... 
	 skip lines until first two tokens are "#start" and  "Section-2"
	 read lines (tokens) and add  words (normalised) in inverted index ADT idx
	 stop reading when first two tokens are "#end" and  "Section-2"
	)

	char delim[2] = " ";
	char *token;
	char line[MAXSTRING] ;
	FILE *f;
	int flag = 0; // if flag = 1, capture the urls
	
	// open a vaild file
	if((f = fopen (urlname , "r")) == NULL) {
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		//printf("line is %s\n", line);
		if(strcmp(line, "#end Section-2") == 0) {
			return;
		}
		if(flag == 1) {
	        token = strtok(line, delim);
			while(token != NULL) {
				if(strcmp(token, "\n") != 0) {
					printf("word is %s", token);

				}
				token = strtok(NULL, delim);
			}
		}
		if(strcmp(line, "#start Section-2") == 0) {
			flag = 1;
		}
	}

}
*/
DLListStr GetCollection() {
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING];
	FILE *f;
	
	DLListStr L = newDLListStr();
	if((f = fopen ("collection.txt" , "r")) == NULL) {
		return L;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		token = strtok(line, delim);
		while(token != NULL) {
			if(strcmp(token, "\n") != 0) {
				//printf("word is %s", token);
				//strcat(token, ".txt");
				//strcat(token, ".txt");
				//printf("%s\n", token);
				insertSetOrd(L, token);
			}
			token = strtok(NULL, delim);
		}
	}
	return L;
}

void GetGraph(DLListStr L, Graph g) {
	int i;
	DLListNode *node = L->first;
	for(i = 0; i < L->nitems; i++) {
		printf("urlname is %s\n", node->value); //!!!!!!!!!!!!!!!!!!!!!!
		readSection1(node->value, g, L);
		node = node->next;
	}
}
