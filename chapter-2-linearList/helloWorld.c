#define LIST_SIZE_INITIAL (0x80)
#define typeElem int

#define GET_VAL(A, B) (B)get_val(A)

#include "linearList.h"
#include <stdio.h>

int main(void)
{
	listLinearSeq *pointer = listLinearSeqInit();
	if (pointer == NULL)
	{
		printf("Ah fuck U.\n");
		return ENOMEM;
	}
	else
	{
		for (int i = 0; i < LIST_SIZE_INITIAL; i++)
		{
			*(pointer->elem + i * sizeof(typeElem)) = (typeElem)i;
			printf("%2x", *(pointer->elem + i * sizeof(typeElem)) = (typeElem)i);
			if ((i + 1) & 7)
			{
				putchar(' ');
			}
			else
			{
				putchar('\n');
			}
		}
		listLinearSeqFree(pointer);
		return 0;
	}
}
