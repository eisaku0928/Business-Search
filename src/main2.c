/**

			Creates a K-D tree to support interactive map functionality for the City of
			Melbourne Census of Land Use and Employment (CLUE) dataset.

			The user is able to query locations to find businesses within a specified radius.

			Created by Eisaku Daniel Tanaka, September 2020.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data2.h"
#include "tree2.h"
#include "utils2.h"

int main(int argc, char *argv[]) {
	data_t *data;
	char *s = NULL;

	// Incorrect input error message from Assignment 1 solution by Gary Fitzpatrick
	if(argc < 3){
		fprintf(stderr, "Incorrect arguments\n");
		fprintf(stderr, "Run in the form\n");
		fprintf(stderr, "\tdict datafile outputfile < inputfile\n");
		exit(1);
	}
	FILE *f = my_fopen(argv[1], "r");
	data_get_header(f);  // get header line of data

	/* Build tree while getting data from the CSV */
  tree_t root = createTree();
	while ((data = get_next_data(f))) {
        root = insert(data, root);
	}
	/* Close file after usage */
	fclose(f);

	/* Setup outfile from argv[2] */
	f= my_fopen(argv[2],"w");

	/* Get each query, and search through the tree */
  while ( (s= getfield(stdin,NL)) ) {
			/* Define struct for queried point */
			queryPoint_t queryPoint = malloc(sizeof(*queryPoint));
			queryPoint->keyComparisons = 0;
			queryPoint->radius = 0;
			queryPoint->found = 0;
			/* Search for the nearest neighbor and print to outfile */
			searchTree(queryPoint, s, root, f);
			if (queryPoint->found == 0){
				fprintf(f, "%s --> NOTFOUND\n", s);
			}
			printf("%s --> %d\n", s, queryPoint->keyComparisons);
			/* Free mallocs for search */
			free(s);
			free(queryPoint);
  }

	/* Close outfile and delete tree and header line */
	fclose(f);
	deleteTree(root);
  data_free_header();
	return 0;
}
