/*Жеребцов ККСО-01-19 Скобки*/
#include <stdio.h>
#include <locale.h>



int main()
{
	setlocale(LC_ALL, "Rus");

	int count_left = 0, count_right = 0;
	int first_position_right = -1;

	char str[60];
	fgets(str, 60, stdin);


	for (int i = 0; str[i] != '\0' || i < 60; i++)
	{
		if (str[i] == '(')
		{
			count_left++;

			continue;
		}

		if (str[i] == ')')
		{
			count_right++;
			if (first_position_right == -1)
			{
				first_position_right = i;
			}

			continue;
		}
	}

	if (count_left == count_right)
	{
		printf("\nyes\n");
	}
	else
	{
		if (count_left > count_right)
		{
			printf("\nno\nexcess left bracket: count = %d", count_left);
		}
		else
		{
			printf("\nno\nexcess right bracket: first position = %d", first_position_right + 1);
		}
	}


	return 0;
}