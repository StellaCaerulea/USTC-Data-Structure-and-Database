/* bracket.c */

#include <stdbool.h>
#include <stdio.h>

#define TYPE_ELEM_DEFINED
typedef char typeElem;
#define TYPE_ELEM_STD_ERR ((typeElem)(-1))

#include "../../library/stackLinked.h"

// #define bracket(x)	\
// 	x == 0 ?	'{' :	x == 1 ?	'}' : 		\
// 	x == 2 ?	'[' :	x == 3 ?	']' : 		\
// 	x == 4 ?	'(' :	x == 5 ?	')' : '\0'

#define legality(str) printf(bracketLegalityStrict(str) ? "true\n" : "false\n")

const char bracket[] = {'{', '[', '(', ')', ']', '}'};

bool bracketLegalityStrict(char *str);

int main(void)
{
	char a[] = "3*{2+[2*5/(2+9)]}";
	char b[] = "3*(2+6/[2*9])";
	char c[] = "()[()]";
	char d[] = "()([])";
	char e[] = "()[]";
	char f[] = "()[(]";
	char g[] = "()[()";

	legality(a); // true
	legality(b); // false
	legality(c); // true
	legality(d); // false
	legality(e); // true
	legality(f); // false
	legality(g); // false

	return 0;
}

bool bracketLegalityStrict(char *str)
{
	stack *s = listInit();
	int priority = 0;
	char temp = '\0';

	for (char *c = str; *c != '\0'; c++)
	{
		for (int i = 0; i < sizeof(bracket) / sizeof(char); i++)
		{
			if (*c != bracket[i])
			{
				continue;
			}
			else if (i <= 2 && priority <= i) // Here ERROR fixed
			{
				priority = i;
				stackPush(s, *c);
				break;
			}
			else if (stackPop(s) == bracket[sizeof(bracket) / sizeof(char) - i - 1])
			{
				temp = stackGetTop(s);
				priority =
					(temp == '{') ? 1 :
					(temp == '[') ? 2 :
					(temp == '(') ? 3 : 0;
				break;
			}
			else
			{
				// printf("aaaa\n");
				return false;
			}
		}
	}
	if (s->head == NULL)
	{
		return true;
	}
	else
	{
		// putchar(s->head->data); putchar('\n');
		return false;
	}
}
