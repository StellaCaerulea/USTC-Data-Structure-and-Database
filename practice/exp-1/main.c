typedef struct polynomial
{
	double coef;
	int expn;

} term, typeElem;

#include <stdbool.h>
#include <stdio.h>
#include "../../library/listLinked.h"

listLinked *polynCreate(const int m);
int polynInsert(listLinked *p, node *n);
void polynPrint(const listLinked *p);

int main(void)
{
	listLinked *p = polynCreate(3);
	polynPrint(p);
	return 0;
}

listLinked *polynCreate(const int m)
{
	listLinked *l = listInit();
	node *p = NULL;
	for (int i = 0; i < m; i++)
	{
		p = nodeAlloc();
		printf("Input exponent: ");
		scanf("%d", &p->data.expn);
		printf("Input coefficient: ");
		scanf("%lf", &p->data.coef);
		printf("%+.2e x^%d\n", p->data.coef, p->data.expn);
		polynInsert(l, p);
	}
	return l;
}

int polynInsert(listLinked *p, node *n)
{
	node *crusor = p->head;
	int counter = 1;
	(p->len)++;
	if (crusor == NULL)
	{
		p->head = n;
		return 0;
	}
	else if (crusor->data.expn > n->data.expn)
	{
		n->next = p->head;
		p->head = n;
		return 0;
	}
	else if (crusor->data.expn == n->data.expn)
	{
		crusor->data.coef += n->data.coef;
		nodeFree(n);
	}
	else
	{
		while (crusor->next != NULL)
		{
			if (crusor->next->data.expn > n->data.expn)
			{
				n->next = crusor->next;
				crusor->next = n;
				return counter;
			}
			else
			{
				crusor = crusor->next;
				counter++;
			}
		}
	}
	crusor->next = n;
	return counter;
}

void polynPrint(const listLinked *p)
{
	for (node *crusor = p->head; crusor != NULL; crusor = crusor->next)
	{
		printf("%+.2e x^%d ", crusor->data.coef, crusor->data.expn);
		;
	}
	return;
}
