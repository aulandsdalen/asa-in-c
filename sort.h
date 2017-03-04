#ifndef _STDARG_H
#include <stdarg.h>
#endif
#define TSEPARATOR "|+-------------------------------+-------------------------------+|\n"

enum bool {
	false = 0,
	true =1
};


int compare_data(const void *a, const void *b) {
	/* compares two data structures based on timestamp, required by qsort() */
	struct data *A = (struct data*)a;
	struct data *B = (struct data*)b;
	return (A->timestamp - B->timestamp);
}


int num_lines(char* filename) {
	FILE *f;
	char row[255];
	int n = 0;
	f = fopen(filename, "r");
	if (!f) 
		return -1;
	while(fgets(row, 255, f)) {
		n++;
	}
	fclose(f);
	return n;
}

void bubblesort(const void *data, unsigned int length, int(*cmp)(const void*, const void*)) {
	struct data *DATA = (struct data*)data;
	struct data tmp;
	int i, j;
	enum bool swapped;
	int allocated_mem;
	allocated_mem = (sizeof(struct data) * (length+1)) + (sizeof(int) * 2) + sizeof(enum bool);
	for(i = 0; i < length; i++) {
		swapped = false;
		for(j = 0; j < length-i; j++) {
			if((*cmp)(&DATA[j], &DATA[j+1])>0) {
				tmp = DATA[j];
				DATA[j] = DATA[j+1];
				DATA[j+1] = tmp;

				swapped = true;
			}
		}
		if(!swapped)
			break;
	}
}

void print_stats(int count, ...) {
	/**/
	printf(TSEPARATOR);
	printf("| %-30s | %-30s |\n", "Algorithm", "Time elapsed (msec)");
	printf(TSEPARATOR);
	va_list arglist;
	int i;
	int sort_begin, sort_end;
	double exectime; 
	char name[255];
	va_start(arglist, count);
	for(i = 0; i < count; i++) {
		strcpy(name, va_arg(arglist, char*));
		sort_begin = va_arg(arglist, int);
		sort_end = va_arg(arglist, int);
		exectime = ((double)sort_end - (double)sort_begin)/(CLOCKS_PER_SEC/1000);
		printf("| %-30s | %-30f |\n", name, exectime);
		printf(TSEPARATOR);
	}
}
