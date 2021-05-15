#define TYPE_ELEM_LIST_LINKED_DEFINED
typedef struct polynomial
{
	double coef;
	int expn;

} term, typeElemLinkedList;

const term termErr = {0.0/0.0, -1}; 
#define TYPE_ELEM_LIST_LINKED_STD_ERR termErr;

#include <stdio.h>
#include "../../library/abbr.h"
#include "../../library/errno.h"
#include "../../library/listLinked.h"

/* The scale of the polynomial-pointer array */
#define _DEST_SIZE_ 0xff
/* The scale of the temprature integer array */
#define _TEMP_SIZE_ 0xf

/**
 * Predefined print strings
 */
#define NO_FUNC "Function not defined.\n"
#define INTONLY "Menu accepts integers only.\n"
#define EXPN_IN "exponent = "
#define COEF_IN "coefficient = "
#define DEST_IN "Input a polynomial numero: "
#define INVALIN "Invalid input.\n"

/* Create a polynomial. */
listLinked *polynCreate(const int m);
/**
 * Return the location where p has been changed. 
 * Negative value suggests a deleted node.
 */
int polynInsert(listLinked *p, node *n);
/* Print the polynomial on stdout. */
void polynPrint(const listLinked *p);
/* Returning (summand += k * addend). */
listLinked *polynAdd(listLinked *summand, const listLinked *addend, const double k);
double polynValue(const listLinked *f, const double x);
errno_t polynTermDel(listLinked *p, const int expn);
listLinked *polynDiff(listLinked *primitive);
listLinked *polynInt(listLinked *intergrand);
listLinked *polynMult(const listLinked *f, const listLinked *g);
/**
 * Return the quotient directly and remainder in *rem;
 * *divd as dividend, *divs as devisor.
 */
listLinked *polynDiv(const listLinked *divd, const listLinked *divs, listLinked *rem);
listLinked *polynPow(const listLinked *f, const int y);
listLinked *polynMCF(const listLinked *f, const listLinked *g);
listLinked *polynMCM(const listLinked *f, const listLinked *g);

int main(void)
{
	int key = -1;
	int temp[_TEMP_SIZE_] = {0};
	// bool isReturn = false;
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
		// printf("----------------------\n");
		printf(" 7. Differential\n");
		printf(" 8. Intergral\n");
		printf(" 9. Multiply\n");
		// printf("10. Divide\n");
		// printf("11. Power\n");
		// printf("12. Max common factor\n");
		// printf("13. Min common multiple\n");
		printf("----------------------\n");
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
				printf(DEST_IN);
				temp[0] = scanf("%d", &temp[1]);
				if (dest[temp[1]] == NULL)
				{
					printf("Not exist.\n");
				}
				else if (temp[1] >= _DEST_SIZE_ || dest[temp[1]] == NULL)
				{
					printf(INVALIN);
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
				printf(DEST_IN);
				scanf("%d", &temp[1]);
				printf(DEST_IN);
				scanf("%d", &temp[2]);
				polynAdd(dest[temp[0]], dest[temp[1]], 1);
				polynAdd(dest[temp[0]], dest[temp[2]], 1);
				printf("Sum at Polyn_%d == ", temp[0]);
				polynPrint(dest[temp[0]]);
				break;
			case 4: // Value
				printf(DEST_IN);
				scanf("%d", &temp[0]);
				if (dest[temp[0]] == NULL)
				{
					printf(INVALIN);
				}
				else
				{
					printf("x = ");
					scanf("%d", &temp[1]);
					printf("f(%d) == %+.2e\n", temp[1], polynValue(dest[temp[0]], temp[1]));
				}
				break;
			case 5: // Free
				printf(DEST_IN);
				scanf("%d", &temp[0]);
				if (dest[temp[0]] == NULL)
				{
					printf(INVALIN);
				}
				else // select existing polynomial
				{
					listFree(dest[temp[0]]);
					dest[temp[0]] = NULL;
				}
				break;
			case 6: // Edit
				printf(DEST_IN);
				scanf("%d", &temp[0]);
				if (dest[temp[0]] == NULL)
				{
					printf(INVALIN);
				}  // if calling for NULL polynomial
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
						printf(EXPN_IN);
						scanf("%d", &p->data.expn);
						printf(COEF_IN);
						scanf("%lf", &p->data.coef);
						polynInsert(dest[temp[0]], p);
						break;
					case 2:
						printf(EXPN_IN);
						scanf("%d", &temp[2]);
						polynTermDel(dest[temp[0]], temp[2]);
						break;
					case 3:
						p = nodeAlloc();
						printf(EXPN_IN);
						scanf("%d", &p->data.expn);
						printf(COEF_IN);
						scanf("%lf", &p->data.coef);
						polynTermDel(dest[temp[0]], p->data.expn);
						polynInsert(dest[temp[0]], p);
					default:
						break;
					} // switch in suboptions
				} // else input valid int
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
			case 12: // Max common factor
				break;
			case 13: // Min common multiple
				break;
			default: // Undefined
				printf(NO_FUNC);
				break;
			} // switch
		} // if input integer
		else
		{
			printf(INTONLY);
			fflush(stdin);
		} // else not integer
	} // while true
}

listLinked *polynCreate(const int m)
{
	listLinked *l = NULL;
	node *p = NULL;

	if (unlikely(m <= 0))
	{
		printf(INVALIN);
		return NULL;
	}
	else
	{
		l = listInit();

		for (int i = 0; i < m; i++)
		{
			p = nodeAlloc();

			printf(EXPN_IN);
			scanf("%d", &p->data.expn);
			printf(COEF_IN);
			scanf("%lf", &p->data.coef);

			if (likely(p->data.coef != 0.0)) // safe since just initialized
			{
				printf("%+.2e x^%d\n", p->data.coef, p->data.expn);
				polynInsert(l, p);
			}
			else
			{
				free(p);
			}
		}
		return l;

	} // else
}

int polynInsert(listLinked *p, node *n)
{
	/**
	 * Warning: Grossing if-else statements and up-to-6-layer indentation.
	 * Prepare a vernier caliper to read this function.
	*/
	node *crusor = NULL;
	int counter = 0;

	if (unlikely(p == NULL || n == NULL))
	{
		return INT_MIN;
	}
	else
	{
		crusor = p->head;
		counter = 1;

		if (unlikely(crusor == NULL)) // 0 to 1
		{
			p->head = n;
			p->len++;

			return 0;
		}
		else if (crusor->data.expn < n->data.expn)
		{
			n->next = p->head;
			p->head = n;
			p->len++;

			return 0;
		}
		else if (crusor->data.expn == n->data.expn)
		{
			if (_equal(crusor->data.coef, -(n->data.coef)))
			{
				free(n);
				p->head = crusor->next;
				free(crusor);

				if (p->head == NULL)
				{
					free(p);
				}

				return -1;
			}
			else
			{
				crusor->data.coef += n->data.coef;
				free(n);

				return 1;
			}
		}
		else
		{
			while (crusor->next != NULL)
			{
				if (crusor->next->data.expn < n->data.expn)
				{
					n->next = crusor->next;
					crusor->next = n;
					p->len++;

					return counter;
				}
				else if (crusor->next->data.expn == n->data.expn)
				{
					if (_equal(crusor->next->data.coef, n->data.coef))
					{
						free(n);
						n = crusor->next;
						crusor->next = n->next;
						free(n);

						return -counter;
					}
					else
					{
						crusor->next->data.coef += n->data.coef;
						free(n);

						return counter;
					}
				}
				else
				{
					crusor = crusor->next;
					counter++;
				}

			} // while (crusor->next != NULL)

			crusor->next = n;
			p->len++;

			return counter;

		} // else (crusor->data.expn != n->data.expn)

	} // else (p != NULL && n != NULL)
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
		if (_equal(k, -1.0))
		{
			listFree(summand);
			summand = NULL;
		}
		else
		{
			for (node *crusor = summand->head; crusor != NULL; crusor = crusor->next)
			{
				crusor->data.coef += k * crusor->data.coef;
			}
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
	}

	return summand;
}

double polynValue(const listLinked *f, const double x)
{
	double ret_val = 0.0;
	const node *crusor = NULL;

	if (unlikely(f == NULL))
	{
		ret_val = nan("");
	}
	else
	{
		for (crusor = f->head; crusor != NULL; crusor = crusor->next)
		{
			ret_val += crusor->data.coef * pow(x, crusor->data.expn);
		}
	}

	return ret_val;
}

errno_t polynTermDel(listLinked *p, const int expn)
{
	node *q = p->head;
	node *r = NULL;

	if (unlikely(p == NULL))
	{
		return -EPERM;
	}
	else if (q->data.expn == expn)
	{
		p->head = q->next;
		free(q);

		return 0;
	}
	while (q->next != NULL && q->next->data.expn != expn)
	{
		q = q->next;
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

		return 0;
	}
}

listLinked *polynDiff(listLinked *primitive)
{
	listLinked *ret_val = listInit();
	node *q = NULL;

	if (unlikely(primitive == NULL || ret_val == NULL))
	{
		return NULL;
	}
	for (node *p = primitive->head; p != NULL; p = p->next)
	{
		if (p->data.expn > 0)
		{
			q = nodeAlloc();
			q->data.coef = p->data.coef * (float)(p->data.expn);
			q->data.expn = p->data.expn - 1;
			polynInsert(ret_val, q);
		}
	}

	return ret_val;
}

listLinked *polynInt(listLinked *intergrand)
{
	listLinked *ret_val = listInit();
	node *q = NULL;

	if (unlikely(intergrand == NULL || ret_val == NULL))
	{
		return NULL;
	}
	else
	{
		for (node *p = intergrand->head; p != NULL; p = p->next)
		{
			q = nodeAlloc();
			q->data.coef = p->data.coef / (float)(p->data.expn);
			q->data.expn = p->data.expn + 1;
			polynInsert(ret_val, q);
		}

		return ret_val;
	}
}

listLinked *polynMult(const listLinked *f, const listLinked *g)
{
	listLinked *ret_val = listInit();

	if (unlikely(f == NULL || g == NULL || ret_val == NULL))
	{
		return NULL;
	}
	else
	{
		for (node *p = f->head; p != NULL; p = p->next)
		{
			for (node *q = g->head; q != NULL; q = q->next)
			{
				node *r = nodeAlloc();
				r->data.coef = p->data.coef * q->data.coef;
				r->data.expn = p->data.expn + q->data.expn;
				polynInsert(ret_val, r);
			}
		}

		return ret_val;
	}
}

listLinked *polynDiv(const listLinked *divd, const listLinked *divs, listLinked *rem)
{
	return NULL;
}

listLinked *polynPow(const listLinked *f, const int y)
{
	listLinked *_polynPowInn(listLinked *, const listLinked *, const int);

	return NULL;
}

static listLinked *_polynPowInn(listLinked *o, const listLinked *f, const int y)
{
	listLinked *temp = NULL;

	if (y == 0)
	{
		return o;
	}
	else
	{
		temp = polynMult(o, f);
		listFree(o);

		return _polynPowInn(temp, f, y - 1);
	}
}

listLinked *polynMCF(const listLinked *f, const listLinked *g)
{
	return NULL;
}

listLinked *polynMCM(const listLinked *f, const listLinked *g)
{
	return NULL;
}
