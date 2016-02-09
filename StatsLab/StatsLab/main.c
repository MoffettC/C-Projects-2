#include <stdio.h>
#define MAX 1000 //max size array

void output(int x[], int max);
void insertionSort(int x[], int max);
void freqChart(int x[], int y[], int max);
void passCheck(int x[], int max);
void mean(int x[], int max);
void mode(int x[], int y[], int max, int maxGrade);
void median(int x[], int max);

int main(void) {
	int i;
	static int x[MAX];
	static int y[MAX]; 
	int maxGrade = 100; //Max grade

	printf("Please input number of test scores or type -1 to finish> ");

	for (i = 0; i < MAX; i++) {
		scanf_s("%d", &x[i]);
		if (x[0] == -1) { //User Validation Checks
			printf("Please input at least one grade.\n");
			i--;
		} else if (x[i] == -1) {
			break;
		} else if ((x[i] > maxGrade) || (x[i] <= -2)) {
			printf("Please input a grade between 0 and 100 or -1 to calculate.\n");
			i--;
		} else
			;
	}

	printf("\n\n");
	output(x, MAX);
	insertionSort(x, MAX);

	for (i = 0; (x[i] != -1) && i < MAX; i++) { //Duplicating grades of input array into counting array according to index AFTER sorting!
		y[x[i]] += 1;
	}
	//for (i = 0; i <= maxGrade; i++)			//DEBUG y[] array
	//	printf("[%d] %d\n\n", i, y[i]);

	output(x, MAX);
	freqChart(x, y, MAX);
	passCheck(x, MAX);
	mean(x, MAX);
	mode(x, y, MAX, maxGrade);
	median(x, MAX);

	getchar(); getchar();
	return 0;
}

void output(int x[], int max) {
	int i;

	for (i = 0; (x[i] != -1) && i < max; i++) {
		printf("[%3d] = %3d", i, x[i]);
		if (i % 5 == 4 || (i == max - 1)) {
			printf("%c", '\n');
		}
		else {
			printf("%c", '  ');
		}
	}
	printf("\n\n\n");
}

void insertionSort(int x[], int max) {
	int i, j, temp;

	for (i = 1; (x[i] != -1) && i < max; i++) {
		temp = x[i];
		j = i - 1;
		while (j >= 0 && temp < x[j]) {
			x[j + 1] = x[j];
			j = j - 1;
		}
		x[j + 1] = temp;
	}
}

void freqChart(int x[], int y[], int max) {
	int i;

	printf("Value %8c Frequency\n", ' ');
	printf("----- %8c ---------\n", ' ');

	for (i = 100; i >= 0; i--) {
		if (y[i] > 0) {
			printf("%5d %10c %7d\n", i, ' ', y[i]);
		}
	}
	printf("\n\n\n");
}

void passCheck(int x[], int max) {
	int i;
	double pass = 0.0, fail = 0.0, pSum = 0.0, fSum = 0.0;

	for (i = 0; (x[i] != -1) && i < max; i++) {
		if (x[i] >= 60.0) {
			pSum++;
		}
		else {
			fSum++;
		}
	}
	pass = pSum / (double) i;
	fail = fSum / (double) i;

	printf("Passing percentage is: %5.1lf percent of %d students\n", 100.0 * pass, i);
	printf("Failing percentage is: %5.1lf percent of %d students\n\n", 100.0 * fail, i);

}

void mean(int x[], int max) {
	int i;
	double sum = 0.0, average = 0.0;

	for (i = 0; (x[i] != -1) && i < max; i++) {
		sum += (double) x[i];
	}
	average = sum / (double) i;

	printf("%10c Average is: %5.1lf for %d students\n", ' ', average, i);
}

void mode(int x[], int y[], int max, int maxGrade) {
	int i, j = 0, k = 0, maxMode = -1, mode = -1;
	int multModes = 0;

	for (i = 0; (x[i] != -1) && i < max; i++) { //first mode check
		if (y[x[i]] > mode) {
			mode = y[x[i]];
			j = y[x[i]];
			maxMode = x[i];
		}
	}

	for (i = 0; i <= maxGrade; i++) { //check for multiple modes/no modes
		if (y[i] == j){
			y[i] = 0; 
			multModes++;
			if (multModes > 1) {
				printf("%13c Mode is: There are multiple modes or no modes\n", ' ');
				break;
			}
		}
	}

	if (multModes == 1) {
		printf("%13c Mode is: %3d   with %d numbers\n", ' ', maxMode, j);
	}

}


void median(int x[], int max) {
	int i;
	int upperMedian = 0, lowerMedian = 0, median = 0;
	double evenMedian = 0.0, oddMedian = 0.0;

	for (i = 0; (x[i] != -1) && i < max; i++) {
		; //counting total grades entered
	}

	if ((i % 2) == 0) { //even
		median = ( i + 1 )/ 2;
		lowerMedian = median - 1; //subtracting one due to 0 based indexing on x[]
		upperMedian = median;
		evenMedian = ((double)(x[upperMedian] + x[lowerMedian]) / 2.0);
		printf("%11c Median is: %5.1lf", ' ', evenMedian);
	}
	else { //odd
		oddMedian = (double) i / 2.0;
		median = (int) oddMedian; 
		printf("%11c Median is: %3d", ' ', x[median]); 
	}
}

