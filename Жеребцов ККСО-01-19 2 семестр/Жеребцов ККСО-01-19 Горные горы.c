/*Жеребцов ККСО-01-19 Горные горы*/
#include <stdio.h>
#include <malloc.h>

struct Mountain
{
	char* name;
	int height;
};




int main()
{
	struct Mountain data[15];

	int h;
	char name[15][32];       // 15 строк (указателей) по 32 символа



	for (int i = 0; i < 15; i++)
	{
		scanf("%32s %d", name[i], &h);


		data[i].name = name[i];
		data[i].height = h;

	}

	printf("----- height > 3000 -----\n\n");

	for (int i = 0; i < 15; i++)
	{
		if (data[i].height > 3000)
		{
			printf("Mountain %s has height %d.\n", data[i].name, data[i].height);
		}
	}

	return 0;
}