/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"
#include "DLListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   Tree left, right;
   char  data[100];
   DLListStr  list;	
} Node;

// make a new node containing data
Tree newNode(Item it) {
    Tree new = malloc(sizeof(Node));
    assert(new != NULL);
    strcpy(new->data, it);  // replace,   data(new) = it;
    left(new) = right(new) = NULL;
    return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
    if (t != NULL) {
        showTreeR(right(t), depth+1);
        printf("%s", data(t));
        DLListNode *node = t->list->first;
        while(node != NULL) {
            printf(" %s", node->value);
            node = node->next;
        }
        printf("\n");
        showTreeR(left(t), depth+1);
    }
}

void showTree(Tree t) {
    showTreeR(t, 0);
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      return TreeSearch(left(t), it);
   
   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      return TreeSearch(right(t), it);

   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, char *filename) {
    if(t == NULL) {
        t = newNode(it);
        t->list = newDLListStr();
        insertSetOrd(t->list, filename);
    }
    else if(strcmp(it, data(t)) > 0) {  //replace, else if (it < data(t))
        left(t) = TreeInsert(left(t), it, filename);
    }
    else if (strcmp(it, data(t)) < 0) {  //replace, else if (it > data(t))
        right(t) = TreeInsert(right(t), it, filename);
    } else {
        insertSetOrd(t->list, filename);
    }
    return t;
}

// save tree to file
void saveTreeR(Tree t, int depth, FILE *fp) {
    if (t != NULL) {
        saveTreeR(right(t), depth+1, fp);
        fputs(data(t), fp);
        fputs(" ", fp);
        DLListNode *node = t->list->first;
        while(node != NULL) {
            fputs(" ", fp);
            fputs(node->value, fp);
            node = node->next;
        }
        fputs("\n", fp);
        saveTreeR(left(t), depth+1, fp);
    }
}

void saveTree(Tree t, FILE *fp) {
    saveTreeR(t, 0, fp);
}