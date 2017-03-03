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

void bubblesort(const void *data, unsigned int length, int(*cmp)(const void*, const void*)) {
	struct data *DATA = (struct data*)data;
	struct data tmp;
	int i, j;
	enum bool swapped;
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