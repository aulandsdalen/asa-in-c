#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"
#include "sort.h"

#define SEPARATOR ","
#define NEWLINE "\n"
#define LENGTH 255


int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <data file>\n", argv[0]);
		return -1;
	}
	struct data *data_arr;
	int row_number = 0;
	char *row;
	FILE *data_file;
	int qsort_begin, qsort_end, bsort_begin, bsort_end, msort_begin, msort_end, hsort_begin, hsort_end;
	if(!(data_file = fopen(argv[1], "r"))) {
		printf("Error reading from %s, exiting...\n", argv[1]);
		return -1;
	}
	row = (char*)malloc(sizeof(char)*LENGTH);
	data_arr = malloc(sizeof(struct data)*num_lines(argv[1]));

	/* read data for msort */
	while(fgets(row, LENGTH, data_file)) {
		data_arr[row_number].measurement = atof(strtok(row, SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	msort_begin = clock();
	mergesort(data_arr, row_number, sizeof(struct data), compare_data);
	msort_end = clock();
	/* read data for qsort */
	rewind(data_file);
	row_number = 0;
	while(fgets(row, LENGTH, data_file)) {
		data_arr[row_number].measurement = atof(strtok(row, SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	qsort_begin = clock();
	qsort(data_arr, row_number, sizeof(struct data), compare_data);
	qsort_end = clock();
	/* read data for hsort */
	rewind(data_file);
	row_number = 0;
	while(fgets(row, LENGTH, data_file)) {
		data_arr[row_number].measurement = atof(strtok(row, SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	hsort_begin = clock();
	heapsort(data_arr, row_number, sizeof(struct data), compare_data);
	hsort_end = clock();
	/* read data for bsort */
	rewind(data_file);
	row_number = 0;
	while(fgets(row, LENGTH, data_file)) {
		data_arr[row_number].measurement = atof(strtok(row, SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	bsort_begin = clock();
	bubblesort(data_arr, row_number, compare_data); 
	bsort_end = clock();
	print_stats(4, "mergesort (stdlib)", msort_begin, msort_end, "quicksort (stdlib)", qsort_begin, qsort_end, "heapsort (stdlib)", hsort_begin, hsort_end, "bubblesort", bsort_begin, bsort_end);
	free(data_arr);
	fclose(data_file);
	return 0;
}
