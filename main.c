#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define FILE_SEPARATOR ","
#define NEWLINE "\n"

struct data {
	double measurement;
	time_t timestamp;
};

struct execution_data {
	struct timeval begin;
	struct timeval end;
};

int compare_data(const void *a, const void *b) {
	struct data *A = (struct data*)a;
	struct data *B = (struct data*)b;
	return (A->timestamp - B->timestamp);
}

void start_timer(struct execution_data *ed) {
	gettimeofday(&ed->begin, NULL);
}

void stop_timer(struct execution_data *ed) {
	gettimeofday(&ed->end, NULL);
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s <data file>\n", argv[0]);
		return -1;
	}
	struct data *data_arr;
	int row_number = 0;
	char *row;
	FILE *data_file;
	struct execution_data qsort_ed;
	if(!(data_file = fopen(argv[1], "r"))) {
		printf("Error reading from %s, exiting...\n", argv[1]);
		return 0;
	}
	row = (char*)malloc(sizeof(char)*255);
	while(fgets(row, 255, data_file)) {
		data_arr = realloc(data_arr, (sizeof(struct data) * (row_number+1)));
		data_arr[row_number].measurement = atof(strtok(row, FILE_SEPARATOR));
		data_arr[row_number].timestamp = atoi(strtok(NULL, NEWLINE));
		row_number++;
	}
	printf("%d rows read\n", row_number);
	start_timer(&qsort_ed);
	qsort(data_arr, row_number, sizeof(struct data), compare_data);
	stop_timer(&qsort_ed);
	time_t seconds = qsort_ed.end.tv_sec - qsort_ed.begin.tv_sec;
	suseconds_t usec = qsort_ed.end.tv_usec - qsort_ed.begin.tv_usec;
	printf("%ld sec %d usec\n", seconds, usec);
	printf("sorted\n");
	free(data_arr);
	fclose(data_file);
	return 0;
}
