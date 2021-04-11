// TBC

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE_INIT (0x100)
#define STACK_SIZE_INCREMENT (0x10)

typedef char SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int size;

} stackSq;

errno_t stackInit