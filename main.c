#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "type.h"
#include "sort.h"

#define FILE_SEPARATOR ","
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
	int qsort_begin, qsort_end, bsort_begin, bsort_end;
	if(!(data_file = fopen(argv[1], "r"))) {
		printf("Error reading from %s, exiting...\n", argv[1]);
		return -1;
	}
	row = (char*)malloc(sizeof(char)*LENGTH);
	data_arr = malloc(sizeof(struct data)*num_lines(argv[1]));
	while(fgets(row, LENGTH, data_file)) {
		data_arr[row_number].measurement = atof(strtok(row, FILE_SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	printf("%d rows read\n", row_number);
	printf("--- stdlib qsort ---\n");
	qsort_begin = clock();
	qsort(data_arr, row_number, sizeof(struct data), compare_data);
	qsort_end = clock();
	printf("%2f msec elapsed\n", ((double)qsort_end - (double)qsort_begin)/(CLOCKS_PER_SEC/1000));
	printf("--- bubblesort ---\n");
	bsort_begin = clock();
	bubblesort(data_arr, row_number, compare_data); /*WARNING!! data_arr is already sorted here, perhaps you'll want to read it again */
	bsort_end = clock();
	printf("%2f msec elapsed\n", ((double)bsort_end - (double)bsort_begin)/(CLOCKS_PER_SEC/1000));
	free(data_arr);
	fclose(data_file);
	return 0;
}
