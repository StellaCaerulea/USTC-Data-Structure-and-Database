/** isSet.cpp
 * Since this file is not created by us,
 * it is not published under the Unlicense.
*/
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

bool isList(char *str, int (*arr)[201], int start, int en);

bool isSet(char *str, int (*arr)[201], int start, int en)
{
	if (start > en || start == en)
		return false;
	if (str[start] != '{' || str[en] != '}')
		return false;
	if ((en - start) == 1)
		return true;
	if ((en - start) == 2)
		return true;
	++start;
	--en;
	return isList(str, arr, start, en);
}

bool isList(char *str, int (*arr)[201], int start, int en)
{
	if (start > en)
		return false;
	if (start == en)
		return true;
	if (arr[start][en] == 1)
		return true;
	if (arr[start][en] == -1)
		return false;
	if (str[start] == '{' && str[en] == '}')
		if (isSet(str, arr, start, en))
		{
			arr[start][en] = 1;
			return true;
		}
	int i = start;
	for (; i <= en; ++i)
	{
		if (str[i] == ',')
		{
			if (isList(str, arr, start, i - 1) && isList(str, arr, i + 1, en))
			{
				arr[start][en] = 1;
				return true;
			}
		}
	}
	arr[start][en] = -1;
	return false;
}

int main(void)
{
	bool flag;
	int T, len;
	cin >> T; // the number of inputs
	cin.get();
	char *ch;
	ch = new char[201];
	for (int i = 1; i <= T; ++i)
	{
		int p[201][201] = {0};
		scanf("%s", ch);
		len = strlen(ch);
		flag = isSet(ch, p, 0, len - 1);
		printf("Word #");
		printf("%d", i);
		if (flag)
			printf(": Set");
		else
			printf(": No Set");
		if (i != T)
			cout << endl;
	}
	delete[] ch;
	return 0;
}
