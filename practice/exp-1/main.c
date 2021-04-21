typedef struct polynomial
{
	double coef;
	int expn;

} term, typeElem;

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "../../library/listLinked.h"

#ifndef _DEST_SIZE_
	/* The scale of the polynomial-pointer array */
	#define _DEST_SIZE_ 0xff
#endif
#ifndef _TEMP_SIZE_
	#define _TEMP_SIZE_ 0xf
#endif

/**
 * Predefined print strings
 */
#ifndef INTEGERS_ONLY
	#define INTEGERS_ONLY "Menu accepts integers only.\n"
#endif
#ifndef NO_FUNCTION
	#define NO_FUNCTION "Function not defined.\n"
#endif

listLinked *polynCreate(const int m);
/**
 * Return the location where p has been changed. 
 * Negative value suggests a deleted node.
 */
int polynInsert(listLinked *p, node *n);
void polynPrint(const listLinked *p);
/* Returning (summand += k * addend) */
listLinked *polynAdd(listLinked *summand, const listLinked *addend, const double k);
double polynValue(const listLinked *f, const double x);
int polynTermDel(listLinked *p, const int expn);

int main_t(void)
{
	listLinked *p = polynCreate(3);
	polynPrint(p);
	return 0;
}

int main(void)
{
	int key = -1;
	int temp[_TEMP_SIZE_] = {0};
	bool isReturn = false;
	node *p = NULL;

	listLinked *dest[_DEST_SIZE_] = {NULL};

	while (true)
	{
		printf("---------menu---------\n");
		printf(" 0. Exit\n");
		printf(" 1. Create polymonial\n");
		printf(" 2. Print polynomial\n");
		printf(" 3. Add\n");
		printf(" 4. Value\n");
		printf(" 5. Free\n");
		printf(" 6. Edit\n");
		printf("----------------------\n");
		// printf(" 7. Differential\n");
		// printf(" 8. Intergral\n");
		// printf(" 9. Multiply\n");
		// printf("10. Divide\n");
		// printf("11. Power\n");
		// printf("12. Max common factor\n");
		// printf("13. Min common multiple\n");
		// printf("----------------------\n");
		if (scanf("%d", &key))
		{
			switch (key)
			{
			case 0: // Exit
				return 0;
			case 1: // Create
				for (temp[0] = 0; temp[0] < _DEST_SIZE_; temp[0]++)
				{
					if (dest[temp[0]] == NULL)
					{
						break;
					}
				}
				printf("Create Polynomial_%d:\n", temp[0]);
				printf("Input the num of the terms: ");
				scanf("%d", &temp[1]);
				dest[temp[0]] = polynCreate(temp[1]);
				break;
			case 2: // Print
				printf("Input the numero of the polynomial to print: ");
				temp[0] = scanf("%d", &temp[1]);
				if (dest[temp[1]] == NULL)
				{
					printf("Not exist.\n");
				}
				else if (temp[1] >= _DEST_SIZE_ || dest[temp[1]] == NULL)
				{
					printf("Not a valid address.\n");
				}
				else
				{
					printf("Polyn_%d == ", temp[1]);
					polynPrint(dest[temp[1]]);
				}
				break;
			case 3: // Add (simple)
				for (temp[0] = 0; temp[0] < _DEST_SIZE_; temp[0]++)
				{
					if (dest[temp[0]] == NULL)
					{
						dest[temp[0]] = listInit();
						break;
					}
				}
				printf("Input the numero of an addend polynomial: ");
				scanf("%d", &temp[1]);
				printf("Input the numero of another addend polynomial: ");
				scanf("%d", &temp[2]);
				polynAdd(dest[temp[0]], dest[temp[1]], 1);
				polynAdd(dest[temp[0]], dest[temp[2]], 1);
				printf("Sum at Polyn_%d == ", temp[0]);
				polynPrint(dest[temp[0]]);
				break;
			case 4: // Value
				printf("Input the numero of a polynomial: ");
				scanf("%d", &temp[0]);
				printf("x = ");
				scanf("%d", &temp[1]);
				printf("f == %+.2e\n", polynValue(dest[temp[0]], temp[1]));
				break;
			case 5: // Free
				printf("Input the numero of a polynomial: ");
				scanf("%d", &temp[0]);
				if (dest[temp[0]] == NULL)
				{
					printf("Not exist.\n");
				}
				else
				{
					listFree(dest[temp[0]]);
					dest[temp[0]] = NULL;
				}
				break;
			case 6: // Edit
				printf("Input the numero of a polynomial: ");
				scanf("%d", &temp[0]);
				if (dest[temp[0]] == NULL)
				{
					printf("Not exist.\n");
				}
				else
				{
					printf("----------------------\n");
					printf(" 1. Add term\n");
					printf(" 2. Delete term\n");
					printf(" 3. Change term\n");
					printf("----------------------\n");
					scanf("%d", &temp[1]);
					switch (temp[1])
					{
					case 1:
						p = nodeAlloc();
						printf("Input exponent: ");
						scanf("%d", &p->data.expn);
						printf("Input coefficient: ");
						scanf("%lf", &p->data.coef);
						polynInsert(dest[temp[0]], p);
						break;
					case 2:
						printf("Input expn: ");
						scanf("%d", &temp[2]);
						polynTermDel(dest[temp[0]], temp[2]);
						break;
					case 3:
						p = nodeAlloc();
						printf("Input exponent: ");
						scanf("%d", &p->data.expn);
						printf("Input coefficient: ");
						scanf("%lf", &p->data.coef);
						polynTermDel(dest[temp[0]], p->data.expn);
						polynInsert(dest[temp[0]], p);
					default:
						break;
					}
				}
				break;
			case 7: // Diffrential
				break;
			case 8: // Intergral
				break;
			case 9: // Multiply
				break;
			case 10: // Divide
				break;
			case 11: // Power
				break;
			case 12: // MCF
				break;
			case 13: // MCM
				break;
			default: // Undefined
				printf(NO_FUNCTION);
				break;
			} // switch
		} // if input integer
		else
		{
			printf(INTEGERS_ONLY);
			fflush(stdin);
		} // else
	} // while true
}

listLinked *polynCreate(const int m)
{
	if (m <= 0)
	{
		printf("What ru doin'?\n");
		return NULL;
	}
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
			free(p);
		}
	}
	return l;
}

int polynInsert(listLinked *p, node *n)
{
	node *crusor = p->head;
	int counter = 1;
	if (crusor == NULL) // 0 to 1
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
	else if (crusor->data.expn == n->data.expn) // 
	{
		crusor->data.coef += n->data.coef;
		free(n);
		if (fabs(crusor->data.coef) < __DBL_EPSILON__)
		{
			p->head = crusor->next;
			free(crusor);
			if (p->head == NULL)
			{
				free(p);
			}
			return -1;
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
				free(n);
				if (fabs(crusor->next->data.coef) < __DBL_EPSILON__)
				{
					n = crusor->next;
					crusor->next = n->next;
					free(n);
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
	putchar('\n');
	return;
}

listLinked *polynAdd(listLinked *summand, const listLinked *addend, const double k)
{
	node *temp = NULL;
	if (summand == addend)
	{
		if (k == -1.0)
		{
			listFree(summand);
			return NULL;
		}
		else
		{
			for (node *crusor = summand->head; crusor != NULL; crusor = crusor->next)
			{
				crusor->data.coef += k * crusor->data.coef;
			}
			return summand;
		}
	}
	else
	{
		for (const node *crusor = addend->head; crusor != NULL; crusor = crusor->next)
		{
			temp = nodeAlloc();
			temp->data.coef = k * crusor->data.coef;
			temp->data.expn = crusor->data.expn;
			polynInsert(summand, temp);
		}
		return summand;
	}
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

int polynTermDel(listLinked *p, const int expn)
{
	if (p == NULL)
	{
		return 0;
	}
	node *q = p->head;
	node *r = NULL;
	int counter = 1;
	if (q->data.expn == expn)
	{
		p->head = q->next;
		free(q);
		return 0;
	}
	while (q->next != NULL && q->next->data.expn != expn)
	{
		q = q->next;
		++counter;
	}
	if (q->next == NULL)
	{
		return -1;
	}
	else
	{
		r = q->next;
		q->next = r->next;
		free(r);
		return counter;
	}
}
