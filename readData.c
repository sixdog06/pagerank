#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "Graph.h"
#include "readData.h"
#include "DLListStr.h"
#include "InvertedIdx.h"

void readSection1(char *urlname, Graph g) {
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

Tree readSection2(char *filename, Tree t) {
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
					len = strlen(token);
					for(int i = 0; i < len; ++i) {
						token[i] = tolower(token[i]);
					}
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
	return t;
}

// get the urls in the fold
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

// get the section1
void GetGraph(Graph g, DLListStr L) {
	int i;
	DLListNode *node = L->first;

	for(i = 0; i < L->nitems; i++) {
		readSection1(node->value, g);
		node = node->next;
	}
}

// set the initialize PR to 1/N
void Init_graph(Graph g, int N) {
    if(g == NULL) {
    	return;
    }
    int i;
    for (i = 0; i < g->nV; i++) {
			g->pr[i] = 1.0 / N;
    }
}

// calculate pagerank
void PageRank(Graph g, DLListStr L, double d, double diffPR, double maxIteration) {
	int N = L->nitems;
	double t_1[N];
	double t[N];
	double sum;
	int i, j;

	int iteration = 0;
	double diff = diffPR;
	
	for(i = 0; i < N; i++) {
		t_1[i] = g->pr[i];
	}
	while(iteration < maxIteration && diff >= diffPR) {
		iteration++;
		for(i = 0; i < N; i++) {
			t[i] = t_1[i];		
		}

		for(i = 0; i < N; i++) {
			sum = 0;
			for(j = 0; j < N; j++) {
				if(g->edges[j][i] == 1 && i != j) {
					sum += t[j] / outdegreeGraph(g, j);
				} else if(outdegreeGraph(g, j) == 0) {
					sum += t[j] / N;
				}
			}
			t_1[i] = (1 - d) / N + d * sum;
		}
		diff = 0;
		sum = 0;
		for(i = 0; i < N; i++) {
			diff += fabs(t_1[i] - t[i]);
			sum += t_1[i];		
			//printf("%.7f ", t[i]);
		}
		//printf("   %.7f\n", sum);
	}
	// assign result to graph
	for(i = 0; i < N; i++) {
		g->pr[i] = t_1[i];
	}
}

// output the well-ordered urls to pagerangList.txt
void Order(Graph g, DLListStr L) {
	int N = L->nitems;
	double temp_pr[N];
	char temp_url[N][100];
	int i, j;
	DLListNode *node = L->first;

	for(i = 0; i < N; i++) {
		temp_pr[i] = g->pr[i];
		strcpy(temp_url[i], node->value);
		node = node->next;
	}

	// order the list
	for(i = 0; i < N - 1; i++) {
		for(j = 0; j < N - 1 - i; j++) {
			if(temp_pr[j] < temp_pr[j+1]) {
				double t = temp_pr[j];
				temp_pr[j] = temp_pr[j+1];
				temp_pr[j+1] = t;
				char ct[100];
				strcpy(ct, temp_url[j]);
				strcpy(temp_url[j], temp_url[j+1]);
				strcpy(temp_url[j+1], ct);
			}
		}
	}

	FILE *fp;
	fp = fopen("pagerankList.txt", "w+");
	
	for(i = 0; i < N; i++) {
		fputs(temp_url[i], fp);
		fputs(", ", fp);
		
		char str[100];
		sprintf(str, "%d", outdegreeGraph(g, show_Index(L, temp_url[i])));
		fputs(str, fp);
		fputs(", ", fp);

		sprintf(str, "%.7f", temp_pr[i]);
		fputs(str, fp);
		
		fputs("\n", fp);
		
	}
	fclose(fp);
}
