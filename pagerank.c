#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListStr.h"
#include "Graph.h"
#include "readData.h"

// set the initialize PR to 1/N
void Init_graph(Graph g, int N) {
    if(g == NULL) {
    	return;
    }
    int i, j;
    for (i = 0; i < g->nV; i++) {
			g->pr[i] = g->pr[i] / N;
    }
}

void PageRank(Graph g, DLListStr L, double d, double diffPR, double maxIteration) {
	int iteration = 0;
	double diff = diffPR;
	int N = L->nitems;
	double temp[N];
	double sum;
	int i, j;

	while(iteration < maxIteration && diff >= diffPR) {
		iteration++;
		for(i = 0; i < N; i++) {
			sum = 0;
			for(j = 0; j < N; j++) {
				if(g->edges[j][i] == 1) {
					sum += g->pr[j] / outdegreeGraph(g, j);
				}
			}
			temp[i] = (1 - d) / N + d * sum;
		}
		
		for(i = 0; i < N; i++) {
			//printf("temp is %.7f\n", temp[i]);
			g->pr[i] = temp[i];
		}
	}
}

// output the urls to pagerangList.txt
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

/*	for(i = 0; i < N; i++) {
		printf("%.7f ", temp_pr[i]);
		printf("%s\n", temp_url[i]);	
	}*/
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

int main(int argc, char *argv[]) {
	if(argc != 4) {
		//printf("error");
		return 0;
	} 
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	double maxIteration = atof(argv[3]);

	// initialize double linked list to store the file names
	DLListStr L = GetCollection();

	// initialize the graph and store the url in it
	Graph g = newGraph(L->nitems);
	GetGraph(g, L);

	// calculate the pagerank
	Init_graph(g, L->nitems);
	PageRank(g, L, d, diffPR, maxIteration);
	Order(g, L);
	//showGraph(g);
	return 0;
}