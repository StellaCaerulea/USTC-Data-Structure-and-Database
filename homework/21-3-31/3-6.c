#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool strPalEt(const char *);

int main(void)
{
	/* Testing strings */
	char a[] = "a+b&b+a";
	char b[] = "1+3&3-1";
	char c[] = "&&&";
	char d[] = "fa+b&b+a";
	char e[] = "a+b&b+af";
	char f[] = "&";

	printf("\"a+b&b+a\":	");
	printf((strPalEt(a)?"true":"false"));
	putchar('\n');
	printf("\"1+3&3-1\":	");
	printf((strPalEt(b)?"true":"false"));
	putchar('\n');
	printf("\"&&&\":		");
	printf((strPalEt(c)?"true":"false"));
	putchar('\n');
	printf("\"fa+b&b+a\":	");
	printf((strPalEt(d)?"true":"false"));
	putchar('\n');
	printf("\"a+b&b+af\":	");
	printf((strPalEt(e)?"true":"false"));
	putchar('\n');
	printf("\"&\":		");
	printf((strPalEt(f)?"true":"false"));
	putchar('\n');
	return 0;
}

bool strPalEt(const char *str)
{
	char *top = str;
	char *crusor = NULL;
	if (*str == '&' && *(str + 1) == '\0')
	{
		return true;
	}
	while (*top != '\0' && *top != '&')
	{
		top++;
	}
	if (*top == '\0' || top == str)
	{
		return false;
	}
	crusor = top;
	while (*crusor == *top)
	{
		crusor++;
		top--;
		if (top == str)
		{
			return (*(crusor + 1) == '\0');
		}
	}
	return false;
}
