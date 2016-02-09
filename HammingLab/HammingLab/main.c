#include <stdio.h>
#define MAX 5

int main(void) {
	char x[MAX][11];
	int y[MAX][11];
	int i, j;
	int k = 0, counter = 0;

	FILE *fp;
	if (!(fp = fopen("transmit.txt", "r"))) {
		printf("codefile.txt could not be opened for input.");
		getchar(); //debug added so it actually gives user time to read in MVS
		exit(1);
	}

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < 11; j++) {
			fscanf(fp, "%c", &x[i][j]);
			printf("%c", x[i][j]);
		}
	}

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < 11; j++) {
			if (x[i][j] == 49) {
				y[i][j] = 1;
			} else
				y[i][j] = 0;
		}
	}
	printf("\n\n");

	for (i = 0; i < MAX; i++) {
		counter = 0;
		j = 0;

		k = 0;
		k += (y[i][j] + y[i][j+2] + y[i][j+4] + y[i][j+6] + y[i][j + 8] + y[i][j + 10]);
		if ((k % 2) != 0) {
			counter += 1;
		}
		printf("%di Counter %d \n", i, counter);

		k = 0;
		k += (y[i][j+1] + y[i][j + 2] + y[i][j + 5] + y[i][j + 6] + y[i][j + 9] + y[i][j + 10]);
		if ((k % 2) != 0) {
			counter += 2;
		}
		printf("%di Counter %d \n", i, counter);

		k = 0;
		k += (y[i][j + 3] + y[i][j + 4] + y[i][j + 5] + y[i][j + 6]);
		if ((k % 2) != 0) {
			counter += 4;
		}
		printf("%di Counter %d \n", i, counter);

		k = 0;
		k += (y[i][j + 7] + y[i][j + 8] + y[i][j + 9] + y[i][j + 10]);
		if ((k % 2) != 0) {
			counter += 8;
		}
		printf("%di Counter %d \n", i, counter);
		printf("%d Total Counter\n\n", counter);
	}
	

	getchar(); getchar();
	return 0;
}