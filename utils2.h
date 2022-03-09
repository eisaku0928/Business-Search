/*
    This defines prototypes for data-related functions.
*/

#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void *my_malloc(size_t n);
FILE *my_fopen(const char *fname, const char *mode);
char *my_strdup(char *);
int arrayCmp(double dPoint[], double rootPoint[], int n); // Checks if arrays are equal

#endif
