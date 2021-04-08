#ifndef _LIST_LINKED_H_
#define _LIST_LINKED_H_

#include <stdlib.h>
#include "errno.h"

typedef struct Node
{
	typeElem data;
	struct Node *next;

} node;

node *nodeAlloc(void);
void nodeFree(node *p);

typedef struct ListLinked
{
	node *head;
	int len;

} listLinked;

listLinked *listInit(void);
void listFree(listLinked *l);

node *nodeAlloc(void)
{
	node *l = (node *)malloc(sizeof(node));
	l->next = NULL;
	return l;
}

void nodeFree(node *p)
{
	if (p->next == NULL)
	{
		free(p);
	}
	else
	{
		nodeFree(p->next);
	}
	return;
}

listLinked *listInit(void)
{
	listLinked *l = (listLinked *)malloc(sizeof(listLinked));
	if (l == NULL)
	{
		return NULL;
	}
	l->len = 0;
	l->head = NULL;
	return l;
}

void listFree(listLinked *l)
{
	if (l->head == NULL)
	{
		free(l);
	}
	else
	{
		nodeFree(l->head);
	}
	return;
}

#endif
