#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool strPalEt(const char *);

int main(void)
{
	/* Testing strings */
	char a[] = "a+b&b+a@";
	char b[] = "1+3&3-1@";
	char c[] = "&&&@";
	char d[] = "fa+b&b+a@";
	char e[] = "a+b&b+af@";
	char f[] = "&@";
	bool (*func)(const char *) = strPalEt;

	printf("\"a+b&b+a\":	");
	printf((func(a)?"true":"false"));
	putchar('\n');
	printf("\"1+3&3-1\":	");
	printf((func(b)?"true":"false"));
	putchar('\n');
	printf("\"&&&\":		");
	printf((func(c)?"true":"false"));
	putchar('\n');
	printf("\"fa+b&b+a\":	");
	printf((func(d)?"true":"false"));
	putchar('\n');
	printf("\"a+b&b+af\":	");
	printf((func(e)?"true":"false"));
	putchar('\n');
	printf("\"&\":		");
	printf((func(f)?"true":"false"));
	putchar('\n');
	return 0;
}

bool strPalEt(const char *str)
{
	const char *a = str;
	const char *b = str;
	while (*a != '@')
	{
		a++;
	}
	if (a == b || a == b + 1)
	{
		return true;
	}
	else
	{
		a--;
		while (a > b)
		{
			if (*a != *b)
			{
				return false;
			}
			a--;
			b++;
		}
		return true;
	}
}
