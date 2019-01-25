#include <string.h>
#include <stdio.h>
#include "DLListStr.h"

#define MAXSTRING 1000

void readSection1(char *urlname, Graph g);
void readSection2(char *filename);
DLListStr GetCollection();
void GetGraph(Graph g, DLListStr L);
