/*
    This defines prototypes for tree-related functions.
*/
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "data.h"
/* define dimensions of point */
#define K 2

/* Defines structs for tree nodes and query points*/

typedef struct node node_t;

struct node {
	data_t *d;
	node_t *next; // next pointer for chaining
	node_t *left, *right; // left and right pointer for a tree node
};

typedef node_t *tree_t;

/* For queryPoint struct, other than the point itself,
keep track of key comparisons to print to stdout*/
typedef struct {
	double point[K];
	int keyComparisons;
} queryPoint;

typedef queryPoint *queryPoint_t;

/* Function prototypes */
tree_t createTree();
tree_t insert(data_t *d, tree_t l);
tree_t insertRec(data_t *d, tree_t root, unsigned depth);
tree_t newNode(data_t *d);
tree_t chainRec(data_t *d, tree_t root);

double distance(double point1[], double point2[]);
tree_t searchTree(queryPoint_t queryPoint, const char *key, tree_t root);
tree_t searchRec(queryPoint_t queryPoint, tree_t root, unsigned depth);
tree_t closerDistance(queryPoint_t queryPoint, tree_t subTree, tree_t curRoot);
double axisDistance(double pointAx1, double pointAx2);
void printAll(char* searchString, queryPoint_t queryPoint, tree_t nearestNeighbor, FILE *file);

void deleteTree(tree_t root);
void deleteChain(tree_t rootChain);


#endif
