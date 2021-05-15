/* stackLinked.h */
#ifndef _STACK_LINKED_H_
#define _STACK_LINKED_H_

#ifndef TYPE_ELEM_STACK_DEFINED
	typedef int typeElemStack;
	#define TYPE_ELEM_STACK_STD_ERR ((typeElemStack)(-1))
#endif

#define TYPE_ELEM_LIST_LINKED_DEFINED
typedef typeElemStack typeElemLinkedList;
#define TYPE_ELEM_LIST_LINKED_STD_ERR TYPE_ELEM_STACK_STD_ERR

#include "listLinked.h"

typedef struct ListLinked stack;

typeElemStack stackGetTop(stack *s);
errno_t stackPush(stack *s, typeElemStack e);
typeElemStack stackPop(stack *s);

inline stack *stackInit(void)
{
	return listInit();
}

inline void stackFree(stack *l)
{
	listFree(l);
	return;
}

inline typeElemStack stackGetTop(stack *s)
{
	if (s == NULL || s->head == NULL)
	{
		return TYPE_ELEM_STACK_STD_ERR;
	}
	else
	{
		return s->head->data;
	}
}

errno_t stackPush(stack *s, typeElemStack e)
{
	if (s == NULL)
	{
		return EFAULT;
	}
	else
	{
		node *n = nodeAlloc();

		if (n == NULL)
		{
			return ENOMEM;
		}
		else
		{
			n->data = e;
			n->next = s->head;
			s->head = n;
			return 0;
		}
	}
}

typeElemStack stackPop(stack *s)
{
	typeElemStack ret_val;
	node *n;

	if (s == NULL)
	{
		return TYPE_ELEM_STACK_STD_ERR;
	}
	else
	{
		n = s->head;
		ret_val = n->data;
		s->head = n->next;
		free(n);
		return ret_val;
	}
}

#endif /* _STACK_LINKED_H_ */
