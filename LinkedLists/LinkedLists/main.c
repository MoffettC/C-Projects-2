#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int info;
	struct node *next;
} *NODEPTR;

int main(void) {

	int i;
	NODEPTR list, p, q;

	list = (NODEPTR)malloc(sizeof(struct node));
	p = list;
	p->info = 1;
	for (i = 2; i <= 5; i++) {
		q = (NODEPTR)malloc(sizeof(struct node));
		q->info = i;
		p->next = q;
		p = q;
	}

	p->next = NULL;

	getchar(); getchar();
	return 0;
}