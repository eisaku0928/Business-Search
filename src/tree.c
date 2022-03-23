/**

			This file contains function implementations for creating, inserting,
			searching and freeing a K-D Tree.
			Functions are divided by partitions

*/

#include "utils.h"
#include "tree.h"

// ----------------- Start of creating and inserting tree -------------
tree_t createTree() {
	return NULL;
}

/* Initialize currently inserting data points, and depth of tree */
tree_t insert(data_t *d, tree_t l) {
	unsigned depth = 0;
	d->point[0] = atof(d->x);
	d->point[1] = atof(d->y);
	return insertRec(d, l, depth);
}

/* Recursively insert data into tree */
tree_t insertRec(data_t *d, tree_t root, unsigned depth) {

	/* Inserts at leaf */
	if (root == NULL){
		return newNode(d);
	}

	// Calculate current dimension
	unsigned axis = depth % K;

	/* Compare the same axes, and traverse appropriate direction */
	if (d->point[axis] < (root->d->point[axis])){
		root->left = insertRec(d, root->left, depth + 1);
	}
	else {
		if (arrayCmp(d->point, root->d->point, K) == 0){
			// Chain data for duplicate points
			root->next = chainRec(d, root->next);
		}
		else {
			root->right = insertRec(d, root->right, depth + 1);
		}
	}
	return root;
}

/* Insert new node at leaf */
tree_t newNode(data_t *d){
	node_t *node = my_malloc(sizeof(*node));
	node->d = d;
	node->next = NULL;
	node->left = node->right = NULL;
	return node;
}

// Chain duplicates
tree_t chainRec(data_t *d, tree_t root){
	node_t *node = my_malloc(sizeof(*node));
	node->d = d;
	node->next = root;
	node->left = node->right = NULL;
	return node;
}

// ---------------------- END OF INSERT IMPLEMENTATION ------------------

// ---------------------- START OF SEARCH IMPLEMENTATION ------------------

// Initialize searching point in queryPoint struct
tree_t searchTree(queryPoint_t queryPoint, const char *key, tree_t root){

	// Initialize depth
	unsigned depth = 0;

	/* Copy the key to get tokens */
	char keyCpy[strlen(key) + 1];
	strncpy(keyCpy, key, sizeof(keyCpy));
	keyCpy[sizeof(keyCpy)] = '\0';

	// Store token in appropriate fields
	char *ptr = strtok(keyCpy, " ");
	for (int i = 0; ptr != NULL; i++){
		double point = atof(ptr);
		queryPoint->point[i] = point;
		ptr = strtok(NULL, " ");
	}

	// After search, send back to main as nearest neighbor
	return searchRec(queryPoint, root, depth);;
}

/* Traverse through the tree, ignoring impossible unneeded branches */
tree_t searchRec(queryPoint_t queryPoint, tree_t root, unsigned depth){

	// Initialize variables for branches and nearest neighbor
	tree_t next_branch = NULL;
	tree_t opposite_branch = NULL;
	tree_t nearestNeighbor = NULL;

	// If root does not exist return NULL
	if (root == NULL){
		return NULL;
	}

	// Calculate current dimension
	unsigned axis = depth % K;

	// Choose which branch is next and the opposite for cases to check the opposite branch
	if (queryPoint->point[axis] < (root->d->point[axis])){
		next_branch = root->left;
		opposite_branch = root->right;
	}
	else {
		next_branch = root->right;
		opposite_branch = root->left;
	}

	// Increment comparisons
	queryPoint->keyComparisons++;

	// Recursively compare current splitting point is better than what is in
	// the "next_branch".
	nearestNeighbor = closerDistance(queryPoint, searchRec(queryPoint, next_branch, depth + 1), root);
	/* Check other subtree if radius from queryPoint to nearestNeighbor is greater than it's splitting point */
	if (distance(queryPoint->point, nearestNeighbor->d->point) > (axisDistance(queryPoint->point[axis], root->d->point[axis]))){
		nearestNeighbor = closerDistance(queryPoint, searchRec(queryPoint, opposite_branch, depth + 1), nearestNeighbor);
	}

	return nearestNeighbor;
}

// Finds the closer distance to the query point
tree_t closerDistance(queryPoint_t queryPoint, tree_t subTree, tree_t curRoot){
	double d1;
	double d2;

	if (subTree == NULL){
		return curRoot;
	}
	if (curRoot == NULL){
		return subTree;
	}

	/* Compare and return closer node to be stored as the closest node */
	d1 = distance(queryPoint->point, subTree->d->point);
	d2 = distance(queryPoint->point, curRoot->d->point);

	if (d1 < d2){
		return subTree;
	}
	else {
		return curRoot;
	}
}

/* Compares distance in the same axis */
double axisDistance(double pointAx1, double pointAx2){
	return pow((pointAx1 - pointAx2), 2);
}

/* Calculates distance between two points */
double distance(double point1[], double point2[]){
	double x1 = point1[0];
	double y1 = point1[1];
	double x2 = point2[0];
	double y2 = point2[1];

	double dx = x1 - x2;
	double dy = y1 - y2;

	return pow(dx, 2) + pow(dy, 2);
}

/* prints node sent in and those that are also chained */
void printAll(char* searchString, queryPoint_t queryPoint, tree_t nearestNeighbor, FILE *file){
	node_t *ptr = nearestNeighbor;
	while (ptr != NULL){
		fprintf(file, "%s --> ", searchString);
		print_data(ptr->d, file);
		ptr = ptr->next;
	}
	printf("%s --> %d\n", searchString, queryPoint->keyComparisons);

}


// ------------------------ END OF SEARCH IMPLEMENTATION ------------------
// ------------------------ START OF DELETE IMPLEMENTATION ----------------

/* Deletes tree with a post-order traversal*/
void deleteTree(tree_t root){
	if (root == NULL){
		return;
	}

	/* Delete all subtrees before deleting current node */
	deleteTree(root->left);
	deleteTree(root->right);

	/* Send chain to be deleted if exists */
	if (root->next){
		deleteChain(root->next);
	}
	/* Delete current node */
	free_data(root->d);
	free(root);
}

/* Deletes the chain of passed in node of tree */
void deleteChain(tree_t rootChain){
	tree_t ptr = rootChain;
	while (ptr != NULL) {
		tree_t tmp = ptr;
		ptr = ptr->next;
		free_data(tmp->d);
		free(tmp);
	}
}

// ------------------------ END OF DELETE IMPLEMENTATION ------------------
