/* listLinked.h */
#ifndef _LIST_LINKED_H_
#define _LIST_LINKED_H_

#include <stdlib.h>
#include "errno.h"

#ifndef TYPE_ELEM_LIST_LINKED_DEFINED
	typedef int typeElemLinkedList;
	#define TYPE_ELEM_LIST_LINKED_STD_ERR ((typeElem)(-1))
#endif

typedef struct Node
{
	typeElemLinkedList data;
	struct Node *next;

} node;

node *nodeAlloc(void);
void nodeFreeChain(node *p);

typedef struct ListLinked
{
	node *head;
	int len;

} listLinked;

listLinked *listInit(void);
void listFree(listLinked *l);

/* Create a node which's next is NULL */
node *nodeAlloc(void)
{
	node *l = (node *)malloc(sizeof(node));
	if (l != NULL)
	{
		l->next = NULL;
	}
	return l;
}

/* Free p and all nodes after it.
 * For freeing itself, simply use free() instead. */
void nodeFreeChain(node *p)
{
	if (p == NULL)
	{
		return;
	}
	else if (p->next == NULL)
	{
		free(p);
	}
	else
	{
		nodeFreeChain(p->next);
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
		nodeFreeChain(l->head);
	}
	return;
}

#endif /* _LIST_LINKED_H_ */
