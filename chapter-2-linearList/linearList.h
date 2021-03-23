/** linearList.h
 * This file has no copyright assigned and is placed in the Public Domain.
 */
#ifndef _LINEAR_LIST_H_
#define _LINEAR_LIST_H_

#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

/* This should be defined as a proper element type in the C file.  */

#ifndef typeElem
#define typeElem int
#endif

#ifndef LIST_SIZE_INITIAL
#define LIST_SIZE_INITIAL (0x100)
#endif

#ifndef LIST_SIZE_INCREMENT
#define LIST_SIZE_INCREMENT (0x10)
#endif

typedef struct ListLinearSeq
{
	int length;
	int size;
	typeElem *elem;

} listLinearSeq;

listLinearSeq *listLinearSeqInit(void);
void listLinearSeqFree(listLinearSeq *list);
void listLinearSeqClear(listLinearSeq *list);
bool listLinearSeqIsEmpty(listLinearSeq *list);
errno_t listLinearSeqGetElem(listLinearSeq *list, int locator, typeElem *ret_val);
int listLinearSeqLocateElem(listLinearSeq *list, bool (*compare)(typeElem ref, typeElem obj));
typeElem *listLinearSeqPrior(listLinearSeq *list, typeElem elem);
typeElem *listLinearSeqNext(listLinearSeq *list, typeElem elem);
errno_t listLinearSeqInsert(listLinearSeq *list, int locator, typeElem elem);
errno_t listLinearSeqDelete(listLinearSeq *list, int locator);
errno_t listLinearSeqTraverse(listLinearSeq *list, errno_t(*check)(typeElem elem));

/* Initialize an empty list. */
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
			return NULL;
		}
		else
		{
			return list;
		}
	}
}

/* Abandon a existing list. */
void listLinearSeqFree(listLinearSeq *list)
{
	if (list != NULL)
	{
		free(list->elem);
		free(list);
	}
	return;
}

#endif
