#include <string.h>
#include <stdio.h>
#include "DLListStr.h"
#include "InvertedIdx.h"

#define MAXSTRING 1000

void readSection1(char *urlname, Graph g);
Tree readSection2(char *filename, Tree t);
DLListStr GetCollection();
void GetGraph(Graph g, DLListStr L);
