#include <string.h>
#include <stdio.h>

#include "Graph.h"
#include "readData.h"
//#include "InvertedIdx.h"

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
		if(strcmp(line, "#end Section-1") == 0) {
			return;
		}
		if(flag == 1) {
	        token = strtok(line, delim);
			while(token != NULL) {
				if(strcmp(token, "\n") != 0) {
					//printf("word is %s", token);
					
				}
				token = strtok(NULL, delim);
			}
		}
		if(strcmp(line, "#start Section-1") == 0) {
			flag = 1;
		}
	}
}


void readSection2(char *filename, InvertedIdx idx){

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

void GetCollection() {
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING] ;
	FILE *f;
}
