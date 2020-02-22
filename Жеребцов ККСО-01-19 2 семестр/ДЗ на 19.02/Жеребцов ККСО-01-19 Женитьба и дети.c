/*Жеребцов ККСО-01-19 Женитьба и дети*/
#include <stdio.h>

struct Person
{
	char surname[16];
	char married;
	char children;
};


int main()
{
	struct Person data[25];

	printf("Surname / Married (y or n) / Children (y or n)\n\n");

	for (int i = 0; i < 25; i++)
	{
		scanf("%s %c %c", data[i].surname, &data[i].married, &data[i].children);
	}

	printf("----- Married and Children -----\n\n");

	for (int i = 0; i < 25; i++)
	{
		if (data[i].married == 'y' && data[i].children == 'y')
		{
			printf("Mr/Mrs %s married and has children\n", data[i].surname);
		}
	}

	return 0;
}