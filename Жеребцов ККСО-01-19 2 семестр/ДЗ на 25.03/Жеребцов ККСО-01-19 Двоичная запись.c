/*Жеребцов ККСО-01-19 Двоичная запись*/
#include <stdio.h>

void add(char* str, char ch)
{
	char buff;
	for (int i = 0; i < 32; i++)
	{
		buff = str[i];
		str[i] = ch;
		ch = buff;
	}
}


int main()
{
	int a;
	char str[32] = "";
	scanf("%d", &a);

	

	for (int p = 1; p <= a; p = p * 2)
	{
		if (p == (a & p))                         // Если есть 2^p, то добавь 1 в двоичную запись
		{
			add(str, '1');
		}
		else                                      // Или 0 в противном случае
		{
			add(str, '0');
		}
	}


	printf("%d = %s", a, str);
	return 0;
}