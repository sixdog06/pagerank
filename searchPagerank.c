#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"
#include "InvertedIdx.h"

// find the macthed urls and insert to the double linked list
void findMatchedUrls(char *pr_file, DLListStr L, char *word) {
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING];
	FILE *f;
	
	if((f = fopen (pr_file , "r")) == NULL) {
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		token = strtok(line, delim);
		if(strcmp(token, word) == 0) {
			while(token != NULL) {
				if(strcmp(token, "\n") != 0 && strcmp(token, word) != 0) { // select the url and insert to the list
					// printf("%s ", token);
					insertSetOrd(L, token);
				}
				token = strtok(NULL, delim);
			}		
		}
	}
}

void num_MatchedUrls(char *pr_file, DLListStr L, char *word, int *arr) {
	char delim[2] = " ";
	char *token;
	char line[MAXSTRING];
	FILE *f;
	
	if((f = fopen (pr_file , "r")) == NULL) {
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		token = strtok(line, delim);
		if(strcmp(token, word) == 0) {
			while(token != NULL) {
				if(strcmp(token, "\n") != 0 && strcmp(token, word) != 0) { // select the url and insert to the list
					arr[show_Index(L, token)] += 1;
				}
				token = strtok(NULL, delim);
			}		
		}
	}
}

void matched_Urls_with_PR(char *pr_file, DLListStr L, char *word, double *arr) {
	char delim[2] = ",";
	char *token;
	char line[MAXSTRING];
	FILE *f;
	
	if((f = fopen (pr_file , "r")) == NULL) {
		return;
	}
	while(fgets(line, MAXSTRING, f) != NULL) {
		int len = strlen(line);
		if(line[len-1] == '\n') { // get rid of the '\n'
			line[len-1] = '\0';
		}
		token = strtok(line, delim);
		
		if(strcmp(token, word) == 0) {
			while(token != NULL) {
				if(strcmp(token, "\n") != 0 && strcmp(token, word) != 0) { // select the url and insert to the list
					// printf("%f!\n", atof(token));
					arr[show_Index(L, word)] = atof(token);
				}
				token = strtok(NULL, delim);
			}		
		}		
	}
}

int main(int argc, char *argv[]) {
	int i;
	DLListStr L = newDLListStr();
	
	// get the urls
	for(i = 1; i < argc; i++) {
		findMatchedUrls("invertedIndex.txt", L, argv[i]);
	}
	
	// calculate the number of urls
	int size = L->nitems;
	int num[size];
	for(i = 0; i < size; i++) {
		num[i] = 0;
	}
	for(i = 1; i < argc; i++) {
		num_MatchedUrls("invertedIndex.txt", L, argv[i], num);
	}

	// pagerank array initialize
	double pr[size];
	DLListNode *node = L->first;
	for(i = 0; i < L->nitems; i++) {
		matched_Urls_with_PR("pagerankList.txt", L, node->value, pr);
		node = node->next;
	}
	// for(i = 0; i < L->nitems; i++) {
	// 	printf("%.7f\n", pr[i]);
	// }
	
	//showDLListStr(L);
	return 0;
}