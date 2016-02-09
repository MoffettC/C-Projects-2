#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
//Everything working as far as I know as long as ages stay under 3 digits, tenure under 2 digits and salary under 6 digits

typedef struct employees{
	char first[8];  
	char initial[2];
	char last[10];
	char street[17];
	char city[12];
	char state[3];
	char zip[6];
	int age[4];
	char sex[2];
	int tenure[4];
	double salary[10];
} Employee;

//Func. Proto
void strsub(char buf[], char sub[], int start, int end);
int readEmployees(Employee list[]);
void displayEmployees(Employee list[], int maxWorkers);
void maleEmployees(Employee list[], int maxWorkers);
void highestWoman(Employee list[], int maxWorkers);
void lowestMan(Employee list[], int maxWorkers);
double averageSalary(Employee list[], int maxWorkers);
void belowAvgWomen(Employee list[], int maxWorkers, double avgSalary);
void maleSalaryRatio(Employee list[], int maxWorkers, double avgSalary);
void specialEmployee(Employee list[], int maxWorkers);
void poorEmployee(Employee list[], int maxWorkers);
void zipCode(Employee list[], Employee temp[], int maxWorkers);

int main(void) {
	int maxWorkers;
	double avgSalary = 0.00;

	Employee myWorkers[MAX];
	Employee temp[MAX];

	maxWorkers = readEmployees(myWorkers); //calc total workers
	displayEmployees(myWorkers, maxWorkers);
	maleEmployees(myWorkers, maxWorkers);
	highestWoman(myWorkers, maxWorkers);
	lowestMan(myWorkers, maxWorkers);
	avgSalary = averageSalary(myWorkers, maxWorkers); //calc avg salary
	belowAvgWomen(myWorkers, maxWorkers, avgSalary);
	maleSalaryRatio(myWorkers, maxWorkers, avgSalary);
	specialEmployee(myWorkers, maxWorkers);
	poorEmployee(myWorkers, maxWorkers);
	zipCode(myWorkers, temp, maxWorkers);

	getchar();
	return 0;
}

void strsub(char buf[], char sub[], int start, int end) {
	int i, j;
	for (j = 0, i = start; i <= end; i++, j++) {
		sub[j] = buf[i];
	}
	sub[j] = '\0';
}

int readEmployees(Employee list[]) {
	char buf[MAX];

	FILE *fp;
	if (!(fp = fopen("payfile.txt", "r"))) {
		printf("payfile.txt could not be opened for input.");
		getchar(); //debug added so it actually gives user time to read in MVS
		exit(1);
	}

	int i = 0;
	while (!feof(fp)) {
		fgets(buf, MAX, fp);
		strsub(buf, list[i].first, 0, 6);
		strsub(buf, list[i].initial, 8, 8);
		strsub(buf, list[i].last, 10, 18);
		strsub(buf, list[i].street, 20, 35);
		strsub(buf, list[i].city, 37, 46);
		strsub(buf, list[i].state, 48, 49);
		strsub(buf, list[i].zip, 50, 55);
		strsub(buf, (char *) list[i].age, 57, 58);			//Ensure typecast of (char *) to avoid 4133 error
		*list[i].age = atoi((char *) list[i].age);			//Ensure typecast of (char *) to avoid 4133 error
		strsub(buf, list[i].sex, 60, 61);
		strsub(buf, (char *) list[i].tenure, 62, 62);		//Ensure typecast of (char *) to avoid 4133 error
	    *list[i].tenure = atoi((char *) list[i].tenure);	//Ensure typecast of (char *) to avoid 4133 error
		strsub(buf, (char *) list[i].salary, 63, 69);		//Ensure typecast of (char *) to avoid 4133 error
		 *list[i].salary = atof((char *) list[i].salary);	//Ensure typecast of (char *) to avoid 4133 error
		i++;
	}

	fclose(fp);
	return i;
}

void displayEmployees(Employee list[], int maxWorkers) {
	int i = 0;

	printf("EMPLOYEE LIST:\n");
	printf("--------------\n");
	printf("Full Name %9c Street %10c City %8c State %2c Zip %4c Age %c M/F %c Tenure %c  Salary\n", 
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	while (i < maxWorkers) {
		printf("%7s %1s %9s %16s %11s %5s %4c %s %5d %2c %3s %3d Years  %7.2lf\n", list[i].first, list[i].initial, 
			list[i].last, list[i].street, list[i].city, list[i].state, ' ', 
			list[i].zip, *list[i].age, ' ', list[i].sex, *list[i].tenure, *list[i].salary); 
		i++;
	}
}

void maleEmployees(Employee list[], int maxWorkers) {
	int i, j;
	char m[] = "M";

	printf("\nMale Workers\n");
	printf("------------\n");

	i = 0;
	while (i < maxWorkers) {
		j = (strcmp(list[i].sex, m));
		if (j > 0) {
			printf("%s %s\n", list[i].first, list[i].last);
		}
		i++;
	}
}

void highestWoman(Employee list[], int maxWorkers) {
	int i, j, k;
	double salary;
	char m[] = "M";

	i = 0;
	salary = 0.00;
	while (i < maxWorkers) {
		j = (strcmp(list[i].sex, m));
		if ((j < 0) && (*list[i].salary >= salary)) {
			salary = *list[i].salary;
			k = i;
			//printf("%.2lf\n", salary);
		}
		i++;
	}
	printf("\nHighest Paid Woman\n");
	printf("------------------\n");
	printf("%s %s \n", list[k].first, list[k].last);
}

void lowestMan(Employee list[], int maxWorkers) {
	int i, j, k, initialFlag;
	double salary;
	char m[] = "M";

	initialFlag = 0;
	for (i = 0; i < maxWorkers; i++) {
		j = (strcmp(list[i].sex, m));
		if ((j > 0) && (initialFlag == 0)) {
			salary = *list[i].salary;
			k = i;
			initialFlag = 1;
		}
		else if ((j > 0) && (initialFlag == 1) && (*list[i].salary < salary)) {
			salary = *list[i].salary;
			k = i;
		}
		else
			;
	}
	printf("\nLowest Paid Man\n");
	printf("---------------\n");
	printf("%s %s \n", list[k].first, list[k].last);
}

double averageSalary(Employee list[], int maxWorkers) {
	int i;
	double salary = 0.00, totalAverage;

	printf("\nAverage Salary\n");
	printf("--------------\n");

	i = 0;
	while (i < maxWorkers) {
		salary += *list[i].salary;
		i++;
	}
	totalAverage = (salary / (double)maxWorkers);
	printf("%.2lf\n", totalAverage);

	return totalAverage;
}

void belowAvgWomen(Employee list[], int maxWorkers, double avgSalary) {
	int i, j;
	char m[] = "M";

	printf("\nWomen Below Average Salary\n");
	printf("--------------------------\n");

	i = 0;
	while (i < maxWorkers) {
		j = (strcmp(list[i].sex, m));
		if ((j < 0) && (*list[i].salary < avgSalary)) {
			printf("%s %s\n", list[i].first, list[i].last);
		}
		i++;
	}

}

void maleSalaryRatio(Employee list[], int maxWorkers, double avgSalary) {
	int i, j;
	double above, below, ratio;
	char m[] = "M";

	printf("\nMale Workers\n");
	printf("------------\n");

	i = 0;
	above = 0.0;
	below = 0.0;
	ratio = 0.0;
	while (i < maxWorkers) {
		j = (strcmp(list[i].sex, m));
		if ((j > 0) && (*list[i].salary > avgSalary)) {
			above += 1.0;
		}
		if ((j > 0) && (*list[i].salary <= avgSalary)) {
			below += 1.0;
		}
		i++;
	}

	if (below > above) {
		ratio = below / above;
		printf("Ratio is %.2lf below average to 1 above average\n", ratio);
	}
	else if (below < above) {
		ratio = above / below;
		printf("Ratio is %.2lf above average to 1 below average\n", ratio);
	}
	else {
		printf("Ratio is 1 above to 1 below.");
	}

	printf("Below Average: %.2lf\n", below);
	printf("Above Average: %.2lf\n", above);
}

void specialEmployee(Employee list[], int maxWorkers) {
	int i;
	double expensiveSalary = 35000.00;
	int veteranEmployee = 5;
	int notYoungAnymore = 30;

	printf("\nThese Employees are Special:\n");
	printf("----------------------------\n");

	i = 0;
	while (i < maxWorkers) {
		if ((*list[i].salary * 52) >= expensiveSalary){
			if ((*list[i].tenure) >= veteranEmployee) {
				if ((*list[i].age) >= notYoungAnymore) {
					printf("%s %s\n", list[i].first, list[i].last);
				}
			}
		}
		i++;
	}
}

void poorEmployee(Employee list[], int maxWorkers) {
	int i;
	double poorSalary = 350.00;
	double raisePercent = 0.10;

	printf("\nThese Employees are receiving a %.2lf percent raise:\n", raisePercent * 100);
	printf("----------------------------------------------------\n");

	i = 0;
	while (i < maxWorkers) {
		if ((*list[i].salary) <= poorSalary) {
			*list[i].salary += (*list[i].salary) * (raisePercent);
			printf("%s %s New Salary: %.2lf\n", list[i].first, list[i].last, *list[i].salary);
		}
		i++;
	}

}

void zipCode(Employee list[], Employee temp[], int maxWorkers) {
	int i, j;

	printf("\nZip Codes\n");

	for (i = 1; i < maxWorkers; i++)
		for (j = 0; j < maxWorkers - i; j++){
			if (strcmp(list[j].zip, list[j + 1].zip) > 0) {
				temp[j] = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp[j];
			}
	}
	for (i = 0; i < maxWorkers; i++) {
		printf("%s %s %s\n", list[i].first, list[i].last, list[i].zip);
	}

}