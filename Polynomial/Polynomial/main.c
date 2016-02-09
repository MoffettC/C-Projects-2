#include<stdio.h>
#include<stdlib.h>

typedef struct poly {
	float coeff;
	int expon;
	struct poly *next;
} *POLYPTR;

POLYPTR sum(POLYPTR p, POLYPTR q);
void makeTerm(POLYPTR *add, float coeff, int expon);

int main(void) {

	//return 0;
}

POLYPTR sum(POLYPTR p, POLYPTR q) {
	float coeff;
	POLYPTR add = NULL;

	while (p != NULL && q != NULL) {
		if (p->expon == q->expon) {
			coeff = p->coeff + q->coeff;
			if (coeff) {
				makeTerm(&add, coeff, p->expon);
				p = p->next;
				q = q->next;
			}
		}
		else if (p->expon > q->expon) {
			makeTerm(&add, p->coeff, p->expon);
			p = p->next;
		}
		else {
			makeTerm(&add, q->coeff, q->expon);
			q = q->next;
		}
	}
	while (p) {
		makeTerm(&add, p->coeff, p->expon);
		p = p->next;
	}
	while (q) {
		makeTerm(&add, q->coeff, q->expon);
		q = q->next;
	}
	return add;
}

void makeTerm(POLYPTR *add, float coeff, int expon) {
	POLYPTR t;
	POLYPTR last = NULL;

	t = (POLYPTR)malloc(sizeof(struct poly));
	t->coeff = coeff;
	t->expon = expon;
	t->next = NULL;
	if (last == NULL) {
		*add = t;
	}
	else {
		last->next = t;
	}
	last = t;

}