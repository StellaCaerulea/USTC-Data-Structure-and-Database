/* stackLinked.h */
#ifndef _STACK_LINKED_H_
#define _STACK_LINKED_H_

#ifndef TYPE_ELEM_DEFINED
	typedef int typeElem;
	#define TYPE_ELEM_STD_ERR ((typeElem)(-1))
#endif

#include "listLinked.h"

typedef struct ListLinked stack;

typeElem stackGetTop(stack *s);
errno_t stackPush(stack *s, typeElem e);
typeElem stackPop(stack *s);

inline stack *stackInit(void)
{
	return listInit();
}

inline void stackFree(stack *l)
{
	listFree(l);
	return;
}

inline typeElem stackGetTop(stack *s)
{
	if (s == NULL || s->head == NULL)
	{
		return TYPE_ELEM_STD_ERR;
	}
	else
	{
		return s->head->data;
	}
}

errno_t stackPush(stack *s, typeElem e)
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

typeElem stackPop(stack *s)
{
	typeElem ret_val;
	node *n;

	if (s == NULL)
	{
		return TYPE_ELEM_STD_ERR;
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

#endif
