typedef struct polynomial
{
	double coef;
	int expn;

} term, typeElem;

#include <stdbool.h>
#include <stdio.h>
#include "../../library/listLinked.h"
#include <math.h>

#define _DEST_SIZE_ 0xff

listLinked *polynCreate(const int m);
int polynInsert(listLinked *p, node *n);
void polynPrint(const listLinked *p);
listLinked *polynSum(const listLinked *_Pln1, const listLinked *_Pln2);
double polynValue(const listLinked *f, const double x);

int main_t(void)
{
	listLinked *p = polynCreate(3);
	polynPrint(p);
	return 0;
}

int main(void)
{
	int key = -1;
	int temp = 0;
	int temp_1 = 0;
	bool isReturn = false;

	listLinked *dest[_DEST_SIZE_] = {NULL};

	while (true)
	{
		printf("---menu---\n");
		printf("0. Exit\n");
		printf("1. Create Polymonial\n");
		printf("2. Print Polynomial\n");
		printf("3. Add\n");
		printf("4. Value\n");
		printf("5. Free\n");
		printf("6. Edit\n");
		printf("---------\n");
		printf(" 7. Differential\n");
		printf(" 8. Intergral\n");
		printf(" 9. Multiply\n");
		printf("10. Divide\n");
		printf("11. Power\n");
		printf("12. Max common factor\n");
		printf("13. Min common multiple\n");
		printf("---------\n");
		if (scanf("%d", &key))
		{
			switch(key)
			{
			case 0: // Exit
				return 0;
			case 1: // Create Polymonial
				for (temp = 0; temp < _DEST_SIZE_; temp++)
				{
					if (dest[temp] == NULL)
					{
						break;
					}
				}
				printf("Create Polynomial_%d:\n", temp);
				printf("Input the num of the terms: ");
				scanf("%d", &temp_1);
				dest[temp] = polynCreate(temp_1);
				break;
			case 2:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			default:
				break;
			}
		}
	}
	
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
		if (fabs(p->data.coef) >= __DBL_EPSILON__)
		{
			polynInsert(l, p);
		}
		else
		{
			nodeFree(p);
		}
	}
	return l;
}

int polynInsert(listLinked *p, node *n)
{
	node *crusor = p->head;
	int counter = 1;
	if (crusor == NULL)
	{
		p->head = n;
		p->len++;
		return 0;
	}
	else if (crusor->data.expn > n->data.expn)
	{
		n->next = p->head;
		p->head = n;
		p->len++;
		return 0;
	}
	else if (crusor->data.expn == n->data.expn)
	{
		crusor->data.coef += n->data.coef;
		nodeFree(n);
		if (fabs(crusor->data.coef) < __DBL_EPSILON__)
		{
			p->head = crusor->next;
			nodeFree(crusor);
			return -counter;
		}
		return 0;
	}
	else
	{
		while (crusor->next != NULL)
		{
			if (crusor->next->data.expn > n->data.expn)
			{
				n->next = crusor->next;
				crusor->next = n;
				p->len++;
				return counter;
			}
			else if (crusor->next->data.expn == n->data.expn)
			{
				crusor->next->data.coef += n->data.coef;
				nodeFree(n);
				if (fabs(crusor->next->data.coef) < __DBL_EPSILON__)
				{
					n = crusor->next;
					crusor->next = crusor->next->next;
					nodeFree(n);
				}
				return -counter;
			}
			else
			{
				crusor = crusor->next;
				counter++;
			}
		}
	}
	crusor->next = n;
	p->len++;
	return counter;
}

void polynPrint(const listLinked *p)
{
	for (node *crusor = p->head; crusor != NULL; crusor = crusor->next)
	{
		printf("%+.2e x^%d ", crusor->data.coef, crusor->data.expn);
	}
	return;
}

listLinked *polynSum(const listLinked *_Pln1, const listLinked *_Pln2)
{
	listLinked *sum = listInit();
	node *temp = nodeAlloc();
	const node *crusor;
	for (crusor = _Pln1->head; crusor != NULL; crusor = crusor->next)
	{
		temp->data.coef = crusor->data.coef;
		temp->data.expn = crusor->data.coef;
		polynInsert(sum, temp);
	}
	for (crusor = _Pln2->head; crusor != NULL; crusor = crusor->next)
	{
		temp->data.coef = crusor->data.coef;
		temp->data.expn = crusor->data.coef;
		polynInsert(sum, temp);
	}
	return sum;
}

double polynValue(const listLinked *f, const double x)
{
	double ret_val = 0;
	const node *crusor;
	for (crusor = f->head; crusor != NULL; crusor = crusor->next)
	{
		ret_val += crusor->data.coef * pow(x, crusor->data.expn);
	}
	return ret_val;
}

