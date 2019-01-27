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
	int i, j;
	DLListStr L = newDLListStr();
	
	// get the urls
	for(i = 1; i < argc; i++) {
		findMatchedUrls("invertedIndex.txt", L, argv[i]);
	}
	
	// calculate the number of urls
	int size = L->nitems;
	int num[size]; // first array
	for(i = 0; i < size; i++) {
		num[i] = 0;
	}
	for(i = 1; i < argc; i++) {
		num_MatchedUrls("invertedIndex.txt", L, argv[i], num);
	}

	// pagerank array initialize
	double pr[size]; // second array
	char url[size][100];
	DLListNode *node = L->first;
	for(i = 0; i < L->nitems; i++) {
		matched_Urls_with_PR("pagerankList.txt", L, node->value, pr);
		strcpy(url[i], node->value);
		node = node->next;
	}

	// for(i = 0; i < L->nitems; i++) {
	// 	printf("%s ", url[i]);
	// 	printf("%d ", num[i]);
	//  	printf("%.7f\n", pr[i]);
	// }

	// order by number
	for(i = 0; i < size - 1; i++) {
		for(j = 0; j < size - 1 - i; j++) {
			if(num[j] < num[j+1]) {
				double t = pr[j];
				pr[j] = pr[j+1];
				pr[j+1] = t;

				int nt = num[j];
				num[j] = num[j+1];
				num[j+1] = nt;

				char ct[100];
				strcpy(ct, url[j]);
				strcpy(url[j], url[j+1]);
				strcpy(url[j+1], ct);
			}
		}
	}
	// order by pagerank
	for(i = 0; i < size - 1; i++) {
		for(j = 0; j < size - 1 - i; j++) {
			if(num[j] == num[j+1]) {
				if(pr[j] < pr[j+1]) {
					double t = pr[j];
					pr[j] = pr[j+1];
					pr[j+1] = t;

					int nt = num[j];
					num[j] = num[j+1];
					num[j+1] = nt;

					char ct[100];
					strcpy(ct, url[j]);
					strcpy(url[j], url[j+1]);
					strcpy(url[j+1], ct);
				}
			}
		}
	}

	for(i = 0; i < L->nitems; i++) {
		printf("%s\n", url[i]);
	}
	
	//showDLListStr(L);
	return 0;
}