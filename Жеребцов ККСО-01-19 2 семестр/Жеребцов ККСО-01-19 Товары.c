/*Жеребцов ККСО-01-19 Товары*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Item
{
	char name[32];
	int count;
	float price;
	char produce[32];
	char date[12];
};

int main()
{
	srand(time(NULL));
	/***Очень скучно от ваших задач***/
	char* words[] = { "Green", "Smart", "Windy", "Clown", "Illigal", "Wireless", "Bald", "Granny's", "Little", "Atomic" };
	char* names[] = { "milk", "cow", "door", "cards", "money", "pistol", "cannon", "salt", "keyboard", "bike" };
	int counts[] = { 12, 4, 13, 100, 1001, 144, 256, 1, 2, 26 };
	float prices[] = { 12000, 2000, 200, 9, 12, 6100, 441, 256, 65, 25 };
	char* producers[] = { "Microsoft", "VAZ", "APPLE", "Xiaomi", "Domik v derevne", "Blizzard", "Volga", "IKEA", "MIREA", "HomeMade" };
	char* dates[] = { "1.9.2000", "1.1.2010", "3.3.2030", "monday", "13.10.2001", "1.12.2020", "30.2.2010", "31.9.2000", "11.2.1992", "4.12.2001" };
	
	struct Item data[10];
	struct Item temp;

	for (int i = 0; i < 10; i++)
	{

		sprintf(data[i].name, "%s %s", words[rand() % 10], names[rand() % 10]); //Костыль #1
		data[i].count = counts[rand() % 10];
		data[i].price = prices[rand() % 10];
		sprintf(data[i].produce, "%s", producers[rand() % 10]); // Костыль #2
		sprintf(data[i].date, "%s", dates[rand() % 10]);

		printf("%s in counts = %d and price = %g produce by %s delivered on %s.\n", data[i].name, data[i].count, data[i].price, data[i].produce, data[i].date);
	}

	printf("\n----- count > 5 ----- \n\n");

	for (int i = 0; i < 10; i++)
	{

		if (data[i].count > 5)
			printf("%s in counts = %d and price = %g produce by %s delivered on %s.\n", data[i].name, data[i].count, data[i].price, data[i].produce, data[i].date);
	}

	return 0;
}
