/** helloWorld.c
 * This file has no copyright assigned and is placed in the Public Domain.
 * Latest update: Apr.4th 2021, Stella Caerulea
 * ========================================================================== *
 * This file is a random work to test if the basic functions work well.
 */
#include <stdio.h>
#include <stdbool.h>
#include "..\library\errno.h"

#define LIST_SIZE_INITIAL (0x40)
typedef int typeElem;
#include ".\linearList.h"
// triPhase (*const typeElemEqual)(typeElem obj, typeElem ref) = typeElemEqualInt;

int main(void)
{
	listLinearSeq *pointer = listLinearSeqInit();
	triPhase (*cmpLct)() = typeElemCompInt;
	typeElem ret_val = 0;
	typeElem *p = &ret_val; 

	if (pointer == NULL)
	{
		printf("Ah fuck U.\n");
		return ENOMEM;
	}
	else
	{
		for (int i = 0; i < LIST_SIZE_INITIAL; i++)
		{
			*(pointer->elem + i) = (typeElem)i;
			printf("%2x", *(pointer->elem + i) = (typeElem)i);
			if ((i + 1) & 7)
			{
				putchar(' ');
			}
			else
			{
				putchar('\n');
			}
		}
		pointer->length = LIST_SIZE_INITIAL;
		printf("\n=============\n");
		printf("ans = %x\n", listLinearSeqLocateElem(pointer, 0x17, cmpLct, phsNul));
		listLinearSeqGetElem(pointer, 0x17, p);
		printf("ans = %d\n", *p);
		printf("ans = %d\n", typeElemCompInt(*(pointer->elem + 0x17), 0x17));
		printf("elem = %p\n", pointer->elem);
		listLinearSeqFree(pointer);
		return 0; // Good habit.
	}
}
