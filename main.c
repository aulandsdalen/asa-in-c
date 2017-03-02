#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define FILE_SEPARATOR ","
#define NEWLINE "\n"

struct data {
	double measurement;
	time_t timestamp;
};

int compare_data(const void *a, const void *b) {
	struct data *A = (struct data*)a;
	struct data *B = (struct data*)b;
	return (A->timestamp - B->timestamp);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <data file>\n", argv[0]);
		return -1;
	}
	struct data *data_arr;
	//data_arr= malloc(sizeof(struct data));
	int row_number = 0;
	char *row;
	FILE *data_file;
	if(!(data_file = fopen(argv[1], "r"))) {
		printf("Error reading from %s, exiting...\n", argv[1]);
		return 0;
	}
	row = (char*)malloc(sizeof(char)*255);
	while(fgets(row, 255, data_file)) {
		//fscanf(data_file, "%s", row);
		data_arr = realloc(data_arr, row_number + (row_number*sizeof(struct data)));
		data_arr[row_number].measurement = atof(strtok(row, FILE_SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		//printf("%2f, %ld\n", data_arr[row_number].measurement, data_arr[row_number].timestamp);
		row_number++;
	}
	printf("%d rows read\n", row_number); 
	fclose(data_file);
	struct data a, b;
	a.measurement = 0.123;	
	a.timestamp = 345;
	b.measurement = 0;
	b.timestamp = 567;
	printf("now sorting...");
	qsort(data_arr, row_number, sizeof(struct data), compare_data);
	printf("sorted\n");
	return 0;
}
