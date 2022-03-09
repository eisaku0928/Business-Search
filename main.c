/**

			Creates a K-D tree to support interactive map functionality for the City of
			Melbourne Census of Land Use and Employment (CLUE) dataset.

			The user is able to query locations to find nearby businesses.

			Created by Eisaku Daniel Tanaka, September 2020.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "tree.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	data_t *data;
	char *s = NULL;
	tree_t nearestNeighbor = NULL;

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

			/* Search for the nearest neighbor and print to outfile */
			nearestNeighbor = searchTree(queryPoint, s, root);
			printAll(s, queryPoint, nearestNeighbor, f);

			/* Free mallocs for search */
			free(s);
			free(queryPoint);
  }

	/* Close file and delete tree and header line */
	fclose(f);
	deleteTree(root);
  	data_free_header();
	return 0;
}
