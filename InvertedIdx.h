/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdbool.h>
#include "DLListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node *Tree;

typedef struct Node {
   Tree left, right;
   char  data[100];
   DLListStr  list;	
} Node;

typedef char *Item;      // item is just a key



Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)

bool TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item);   // insert a new item into a Tree



