#include <stdbool.h>
#include "../../library/treeBin.h"

#define _DEST_SIZE_ 0xff
#define _TEMP_SIZE_ 0xf

#define NO_FUNC "Function not defined.\n"
#define DEST_IN "Input a tree numero: "

int main(void)
{
	char str[] = "abdg   eh   c fi   ";
	treeBin *tree = treeBinCreate(str);
	treeBinPrint(tree, 0);
	treeBinTraverseNLR(tree, _treeBinFuncDefault);
	putchar('\n');
	treeBinTraverseLNR(tree, _treeBinFuncDefault);
	putchar('\n');
	treeBinTraverseLRN(tree, _treeBinFuncDefault);
	putchar('\n');
	printf("Node amount: %d\n", treeBinCountNode(tree));
	printf("Leaf amount: %d\n", treeBinCountLeaf(tree));
	printf("Height: %d\n", treeBinHeight(tree));
	printf("Width: %d\n", treeBinWidth(tree));
	treeBin *treah = treeBinDuplicate(tree);
	treeBinPrint(treah, 0);
	treeBin *eert = treeBinMirror(tree);
	treeBinPrint(eert, 0);
	treeBinFree(tree);
	treeBinPrint(NULL, 0);
	return 0;
}
