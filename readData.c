#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "readData.h"
#include "DLListStr.h"
#include "InvertedIdx.h"

/*
  A possible way to read data ... 

*/


void readSection1(char *urlname, Graph g){

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
	DLListStr L = GetCollection();

	char delim[2] = " ";
	char *token;
	char line[MAXSTRING] ;
	FILE *f;
	int flag = 0; // if flag = 1, capture the urls
	char temp[100];
	strcpy(temp, urlname);
	strcat(temp, ".txt");
	
	// open a vaild file
	if((f = fopen (temp, "r")) == NULL) {
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {

		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n' and '\t'
			line[len-1] = '\0';
		}
		for(int i = len-1; i >= 0; i--) {
			if(line[i] == '\t') {
				line[i] = ' ';
			}
		}
		if(strcmp(line, "#end Section-1") == 0) {
			return;
		}
		if(flag == 1) {
	        token = strtok(line, delim);
			while(token != NULL) {
				if(strcmp(token, "\n") != 0) {
					Edge e;
					e.v = show_Index(L, urlname);
					e.w = show_Index(L, token);
					insertEdge(g, e);
				}
				token = strtok(NULL, delim);
			}
		}
		if(strcmp(line, "#start Section-1") == 0) {
			flag = 1;
		}
	}
	fclose(f);
	free(L);
}
//void readSection2(char *filename, InvertedIdx idx){
Tree readSection2(char *filename, Tree t) {
	/*
   let's say filename is "url31.txt"
   Open "url31.txt"
   read Section-2 
	(How?, a simple approach ... 
	 skip lines until first two tokens are "#start" and  "Section-2"
	 read lines (tokens) and add  words (normalised) in inverted index ADT idx
	 stop reading when first two tokens are "#end" and  "Section-2"
	)
	*/
	//DLListStr L = GetCollection();
	if(t == NULL) {
		t = newTree();
	}
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING] ;
	FILE *f;
	int flag = 0; // if flag = 1, capture the urls
	char temp[100];
	strcpy(temp, filename);
	strcat(temp, ".txt");
	
	// open a vaild file
	if((f = fopen (temp, "r")) == NULL) {
		return NULL;
	}
	int len;
	while(fgets(line, MAXSTRING, f) != NULL) {

		len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n' and '\t'
			line[len-1] = '\0';
		}
		for(int i = len-1; i >= 0; i--) {
			if(line[i] == '\t') {
				line[i] = ' ';
			}
		}
		// get rid of the punctuation marks
		len = strlen(line);
		for(int i = len-1; i >= 0; i--) {
			if(line[i] == '.' || line[i] == ',' || line[i] == ';' || line[i] == '?') { // get rid of the punctuation marks
				line[i] = '\0';
			}
		}
		if(strcmp(line, "#end Section-2") == 0) {
			return t;
		}
		if(flag == 1) {
	        token = strtok(line, delim);
			while(token != NULL) {
				if(strcmp(token, "\n") != 0) {
					// printf("%s\n", token);
					t = TreeInsert(t, token, filename);
				}
				token = strtok(NULL, delim);
			}
		}
		if(strcmp(line, "#start Section-2") == 0) {
			flag = 1;
		}
	}
	fclose(f);
	//free(L);
	return t;
}

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
				insertSetOrd(L, token);
			}
			token = strtok(NULL, delim);
		}
	}
	return L;
}

void GetGraph(Graph g, DLListStr L) {
	int i;
	DLListNode *node = L->first;

	for(i = 0; i < L->nitems; i++) {
		readSection1(node->value, g);
		node = node->next;
	}
}