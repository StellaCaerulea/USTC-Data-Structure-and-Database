#ifndef _TREE_BIN_H_
#define _TREE_BIN_H_

#include <stdio.h>

#ifndef TREE_BIN_TYPE_ELEM_DEFINED
	typedef char typeElemTree;
#endif

typedef struct TreeBin
{
	typeElemTree data;
	struct TreeBin *lchild, *rchild;

} treeBin;

#define TYPE_ELEM_STACK_DEFINED
typedef treeBin *typeElemStack;
#define TYPE_ELEM_STACK_STD_ERR NULL

#define TYPE_ELEM_Q_DEFINED
typedef treeBin *typeElemQ;
#define TYPE_ELEM_Q_STD_ERR NULL

#include <stdlib.h>
#include <errno.h>
#include "stackLinked.h"
#include "queueLinked.h"

treeBin *treeBinCreate(char *);
void treeBinPrint(treeBin *, int lvl);
errno_t treeBinTraverseNLR(treeBin *, int (*)(typeElemTree));
errno_t treeBinTraverseLNR(treeBin *, int (*)(typeElemTree));
errno_t treeBinTraverseLRN(treeBin *, int (*)(typeElemTree));

int treeBinCountNode(treeBin *);
int treeBinCountLeaf(treeBin *);
int treeBinHeight(treeBin *);
int treeBinWidth(treeBin *);

treeBin *treeBinDuplicate(treeBin *);
treeBin *treeBinMirror(treeBin *);
void treeBinFree(treeBin *);

errno_t _treeBinFuncDefault(typeElemTree);
errno_t _treeBinFuncNUll(typeElemTree);

treeBin *treeBinCreate(char *str)
{
	treeBin *node;
	int flag = 0;
	int locator = 0;

	switch (*str)
	{
	case '\0':
	case ' ':
		node = NULL;
		break;
	default:
		node = (treeBin *)malloc(sizeof(treeBin));
		node->data = *str;
		do
		{
			flag += (*(str + locator) == ' ')? -1: 1;
			++locator;
		} while (flag != 0);
		node->lchild = treeBinCreate(str + 1);
		node->rchild = treeBinCreate(str + locator);
		break;
	}
	return node;
}

void treeBinPrint(treeBin *t, int lvl)
{
	for (int i = 0; i < lvl; i++)
	{
		putchar('\t');
	}

	if (t == NULL)
	{
		printf("NULL\n");
	}
	else
	{
		putchar(t->data);
		putchar('\n');
		if (t->lchild == NULL && t->rchild == NULL)
		{
			return;
		}
		else
		{
			treeBinPrint(t->lchild, lvl + 1);
			treeBinPrint(t->rchild, lvl + 1);
		}
	}
	return;
}

errno_t treeBinTraverseNLR(treeBin *t, errno_t (*func)(typeElemTree))
{
	errno_t ret_val = 0;

	if (t != NULL)
	{
		if (func(t->data) != 0 ||
		treeBinTraverseNLR(t->lchild, func) != 0 ||
		treeBinTraverseNLR(t->rchild, func) != 0)
		{
			return -EPERM;
		}
	}
	else
	{
		return 0;
	}
	
}

errno_t treeBinTraverseLNR(treeBin *t, errno_t (*func)(typeElemTree))
{
	errno_t ret_val = 0;

	if (t != NULL)
	{
		if (treeBinTraverseLNR(t->lchild, func) != 0 |
		func(t->data) != 0 ||
		treeBinTraverseLNR(t->rchild, func) != 0)
		{
			return -EPERM;
		}
	}
	else
	{
		return 0;
	}
	
}

errno_t treeBinTraverseLRN(treeBin *t, errno_t (*func)(typeElemTree))
{
	errno_t ret_val = 0;

	if (t != NULL)
	{
		if (treeBinTraverseLRN(t->lchild, func) != 0 ||
		treeBinTraverseLRN(t->rchild, func) != 0 ||
		func(t->data) != 0)
		{
			return -EPERM;
		}
	}
	else
	{
		return 0;
	}
	
}

errno_t treeBinTraverseLevel(treeBin *t, errno_t (*func)(typeElemTree))
{
	errno_t ret = 0;
	int counter = 0;
	if (t != NULL)
	{
		queueLinked *q = queueInit();
		ret = func(t->data);
		queueEn(q, t);
		while (q->front != NULL)
		{
			for (int i = 0; q->front != NULL; i++)
			{
				t = queueDe(q);
				ret = func(t->data);
				if (t->lchild != NULL)
				{
					queueEn(q, t->lchild);
				}
				if (t->rchild != NULL)
				{
					queueEn(q, t->rchild);
				}
			}
		}
		return 0;
	}
	else
	{
		return -EPERM;
	}
	
}

int treeBinCountNode(treeBin *t)
{
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		return treeBinCountNode(t->lchild) + treeBinCountNode(t->rchild) + 1;
	}
}

int treeBinCountLeaf(treeBin *t)
{
	if (t == NULL)
	{
		return 0;
	}
	else if (t->lchild == NULL && t->lchild == NULL)
	{
		return 1;
	}
	else
	{
		return treeBinCountLeaf(t->lchild) + treeBinCountLeaf(t->rchild);
	}
}

int treeBinHeight(treeBin *t)
{
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		int l = treeBinHeight(t->lchild);
		int r = treeBinHeight(t->rchild);
		return ((l > r) ? l : r) + 1;
	}
}

int treeBinWidth(treeBin *t)
{
	int ret_val = 0;
	int counter = 0;
	int temp = 0;
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		queueLinked *q = queueInit();
		queueEn(q, t);
		++counter;
		while (q->front != NULL)
		{
			ret_val = (ret_val > counter) ? ret_val : counter;
			temp = counter;
			for (int i = 0; i < temp; i++)
			{
				t = queueDe(q);
				--counter;
				if (t->lchild != NULL)
				{
					queueEn(q, t->lchild);
					++counter;
				}
				if (t->rchild != NULL)
				{
					queueEn(q, t->rchild);
					++counter;
				}
			}
		}
		return ret_val;
	}
}

treeBin *treeBinDuplicate(treeBin *t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else
	{
		treeBin *ret_val = (treeBin *)malloc(sizeof(treeBin));
		ret_val->data = t->data;
		ret_val->lchild = treeBinDuplicate(t->lchild);
		ret_val->rchild = treeBinDuplicate(t->rchild);
		return ret_val;
	}
}

treeBin *treeBinMirror(treeBin *t)
{
	if (t == NULL)
	{
		return NULL;
	}
	else
	{
		treeBin *ret_val = (treeBin *)malloc(sizeof(treeBin));
		ret_val->data = t->data;
		ret_val->rchild = treeBinMirror(t->lchild);
		ret_val->lchild = treeBinMirror(t->rchild);
		return ret_val;
	}
}

void treeBinFree(treeBin *t)
{
	if (t == NULL)
	{
		return;
	}
	else if (t->lchild == NULL && t->rchild == NULL)
	{
		free(t);
		return;
	}
	else
	{
		treeBinFree(t->lchild);
		treeBinFree(t->rchild);
		return;
	}
}

inline errno_t _treeBinFuncDefault(typeElemTree elem)
{
	putchar(elem);
	return 0;
}

inline errno_t _treeBinFuncNUll(typeElemTree elem)
{
	return 0;
}

#endif
