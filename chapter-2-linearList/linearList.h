/** linearList.h -- TO BE FINISHED
 * This file has no copyright assigned and is placed in the Public Domain.
 * Latest update: Apr.4th 2021, Stella Caerulea
 * ========================================================================== *
 * This piece of code has not been strictly tested. If you find any bug, feel
 * free to launch a Pull Request.
 */
#ifndef _LINEAR_LIST_H_
#define _LINEAR_LIST_H_

#include "..\library\errno.h"
#include <stdlib.h>
#include <stdbool.h>

/**
 * Default Value
 */
// typedef int elemType;

#ifndef LIST_SIZE_INITIAL
#define LIST_SIZE_INITIAL (0x100)
#endif

#ifndef LIST_SIZE_INCREMENT
#define LIST_SIZE_INCREMENT (0x10)
#endif

typedef enum TriPhase
{
	phsNeg = -1,
	phsNul = 0,
	phsPos = 1

} triPhase;

triPhase typeElemCompInt(typeElem elem1, typeElem elem2);

typedef struct ListLinearSeq
{
	int length;
	int size;
	typeElem *elem;

} listLinearSeq;

/* Initialize an empty list. */
listLinearSeq *listLinearSeqInit(void);
/* Abandon a existing list. */
void listLinearSeqFree(listLinearSeq *list);
/* Reset (*list) to a empty list. */
errno_t listLinearSeqClear(listLinearSeq *list);
/* Return true if and only if the length of the list is 0. */
bool listLinearSeqIsEmpty(const listLinearSeq *list);
/* Return the length of the list. */
int listLinearSeqLength(const listLinearSeq *list);
/* Copy the (locator)-th element to (*ret_val),
 * return EPERN for NULL ret_val, EINVAL for invalid locator. */
errno_t listLinearSeqGetElem(const listLinearSeq *list, const int locator, typeElem *ret_val);
/* Null. */
int listLinearSeqLocateElem(const listLinearSeq *list, const typeElem elem,
							triPhase (*compare)(typeElem, typeElem), triPhase obj);
/* Deleted foolish function */
// typeElem *listLinearSeqPrior(const listLinearSeq *list, const typeElem elem);
/* Deleted foolish function */
// typeElem *listLinearSeqNext(const listLinearSeq *list, const typeElem elem);
/*  */
errno_t listLinearSeqInsert(listLinearSeq *list, const int locator, const typeElem elem);
errno_t listLinearSeqDelete(listLinearSeq *list, const int locator);
/* Null. */
errno_t listLinearSeqTraverse(listLinearSeq *list, errno_t (*check)(typeElem elem));

triPhase typeElemCompInt(typeElem elem1, typeElem elem2)
{
	if (elem1 == elem2)
	{
		return phsNul;
	}
	else if (elem1 < elem2)
	{
		return phsNeg;
	}
	else
	{
		return phsPos;
	}
}

listLinearSeq *listLinearSeqInit(void)
{
	listLinearSeq *list;

	list = (listLinearSeq *)malloc(sizeof(listLinearSeq));
	if (list == NULL)
	{
		return NULL;
	}
	else
	{
		list->length = 0;
		list->size = LIST_SIZE_INITIAL;
		list->elem = (typeElem *)malloc(LIST_SIZE_INITIAL * sizeof(typeElem));
		if (list->elem == NULL)
		{
			free(list);
			return NULL;
		}
		else // (list->elem != NULL)
		{
			return list;
		}
	}
}

inline void listLinearSeqFree(listLinearSeq *list)
{
	if (list != NULL)
	{
		if (list->elem != NULL)
		{
			free(list->elem);
		}
		free(list);
	}
	return;
}

errno_t listLinearSeqClear(listLinearSeq *list)
{
	if (list == NULL)
	{
		return EPERM;
	}
	else // (list != NULL)
	{
		free(list->elem);
		list->length = 0;
		list->size = LIST_SIZE_INITIAL;
		list->elem = (typeElem *)malloc(LIST_SIZE_INITIAL * sizeof(typeElem));
		if (list->elem == NULL)
		{
			return ENOMEM;
		}
		else // success
		{
			return 0;
		}
	}
}

inline bool listLinearSeqIsEmpty(const listLinearSeq *list)
{
	return (list->length == 0);
}

inline int listLinearSeqLength(const listLinearSeq *list)
{
	return list->length;
}

errno_t listLinearSeqGetElem(const listLinearSeq *list, const int locator, typeElem *ret_val)
{
	if (locator >= list->length || locator < 0)
	{
		return EINVAL;
	}
	else if (ret_val == NULL)
	{
		return EPERM;
	}
	else
	{
		*ret_val = *(list->elem + locator);
		return 0;
	}
}

int listLinearSeqLocateElem(const listLinearSeq *list, const typeElem elem,
							triPhase (*compare)(typeElem, typeElem), const triPhase obj)
{
	for (int i = 0; i < list->length; i++)
	{
		if (obj == compare(elem, *(list->elem + i)))
		{
			return i;
		}
	}
	return -1; // Failed to locate acceptable element.
}

// typeElem *listLinearSeqPrior(const listLinearSeq *list, const typeElem elem)
// {
// 	/* In fact the elements cannot be assumed as integer type.
// 	 * Function pointer should be used here instead. */
// 	if (typeElemCompInt(*(list->elem), elem))
// 		return NULL; // The first element has no prior element.
// 	for (int i = 1; i < list->length; i++)
// 		if (typeElemCompInt(*(list->elem + i * sizeof(typeElem)), elem) == 0)
// 			return *(list->elem + (i - 1) * sizeof(typeElem));
// 	return NULL; // Not found.
// }

// typeElem *listLinearSeqNext(const listLinearSeq *list, const typeElem elem)
// {
// 	if (typeElemCompInt(*(list->elem), elem))
// 		return NULL; // The first element has no prior element.
// 	for (int i = 1; i < list->length; i++)
// 		if (typeElemCompInt(*(list->elem + i * sizeof(typeElem)), elem) == 0)
// 			return *(list->elem + (i + 1) * sizeof(typeElem));
// 	return NULL; // Not found.
// }

errno_t listLinearSeqInsert(listLinearSeq *list, const int locator, const typeElem elem)
{
	return 0;
}

errno_t listLinearSeqDelete(listLinearSeq *list, const int locator)
{
	return 0;
}

errno_t listLinearSeqTraverse(listLinearSeq *list, errno_t (*check)(typeElem elem))
{
	return 0;
}

/**
 * Default Value
 */
// triPhase (*const typeElemEqual)(typeElem obj, typeElem ref) = typeElemEqualInt;

#endif
