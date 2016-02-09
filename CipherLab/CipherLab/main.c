#include <stdio.h>

#include <stdlib.h>

int processFile(char message[]);
void cipher(char message[], char codedMessage[], int maxMessage);
void output(char codedMessage[], int maxMessage);

int main(void) {

	int maxLengthMessage;
	char messageArray[1000];
	char codeArray[1000];

	maxLengthMessage = processFile(messageArray);
	if (maxLengthMessage == 0) {
		printf("There was no valid message to encrpyt. Hit enter to exit.");
		getchar();
		exit(1);
	}
	cipher(messageArray, codeArray, maxLengthMessage);
	output(codeArray, maxLengthMessage);

	getchar(); getchar();
	return 0;
}

int processFile(char message[]) {
	int i = 0, maxMessage = 0;

	FILE *fp;
	if (!(fp = fopen("congress.txt", "r"))) {
		printf("congress.txt could not be opened for input.");
		getchar(); //debug added so it actually gives user time to read in MVS
		exit(1);
	}

	fscanf_s(fp, "%c", &message[i], 1);
	if ((message[i] >= 97) && (message[i] <= 122)) //Uppercase function
		message[i] = message[i] - 32;
	if (!((message[i] >= 65) && (message[i] <= 90))) { //Removes non alphabet
		i--;
		maxMessage--;
	}

	while (!feof(fp)) {
		i++;
		maxMessage++;
		fscanf_s(fp, "%c", &message[i], 1);	
		if ((message[i] >= 97) && (message[i] <= 122)) //Uppercase function
			message[i] = message[i] - 32;
		if (!((message[i] >= 65) && (message[i] <= 90))) { //Removes non alphabet
				i--;
				maxMessage--;
		}
	}
	maxMessage++; //Extends maximum to last character before null

	fclose(fp);
	return maxMessage;
}

void cipher(char message[], char codedMessage[], int maxMessage){
	int shift = 0;
	int c, i;

	printf("Please input the maximum amount of shift> ");
	scanf_s("%d", &shift);
	printf("\n\n");

	for (i = 0; i < maxMessage; i++) { //Borrowed from class!
		c = ((((message[i] - 'A') + shift) % 26) + 'A');
		codedMessage[i] = (char) c;
	}

}

void output(char codedMessage[], int maxMessage) {

	int i;

	printf("Message Encrpytion:\n");
	for (i = 0; i < maxMessage; i++) {
		printf("%c", codedMessage[i]);
		if ((i % 50) == 49) 
			printf("\n");
		if (((i % 5) == 4) && !((i % 50) == 49))
			printf(" ");		
	}
	printf("\n");
}