/*
		Added array comparison function, useful for storing and finding duplicates
*/

#include "utils.h"
#include "tree.h"


/* Utility functions by Ahn Vo */
void *my_malloc(size_t n){
	assert(n>0);
	void *p = malloc(n);
	assert(p);
	return p;
}

FILE *my_fopen(const char *fname, const char *mode) {
	FILE *f = fopen(fname, mode);
	assert(f);
	return f;
}

char *my_strdup(char *s) {
	char *t = strdup(s);
	assert(t);
	return t;
}

/* Compares two arrays, third parameter is length of array. */
int arrayCmp(double dPoint[], double rootPoint[], int n){
	for (int i = 0; i < n; i++){
		if (dPoint[i] != rootPoint[i]){
			return 1;
		}
	}
	return 0;
}
