/*Жеребцов ККСО-01-19 Работяги*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Worker
{
	char name[32];
	int year;
	char post[16];
	int pay;
	char education[16];
};

int main()
{
	srand(time(NULL));
	/***Очень скучно от ваших задач***/
	char* names[] = { "Smith", "Johns", "Emmeli", "Penni", "Kuchelbecker", "Mister N", "Marie", "Tomas", "Jerry", "Pyrkin" };
	int years[] = { 1992, 2004, 1913, 2100, 2001, 1944, 2006, 1999, 2000, 1945 };
	char* posts[] = { "boss", "terminator", "garder", "driver", "medic", "traitor", "scout", "sherrif", "guard", "buffon" };
	int pays[] = { 1,2000, 0, 10, 10000, 100, 200, 30, 60, 81};
	char* educations[] = { "IT", "MGU", "HSE", "MEI", "NASA", "KKSO", "CyberNet(ik)", "SelfMade", "SportInstitution", "Garvard" };

	struct Worker data[10];

	for (int i = 0; i < 10; i++)
	{

		sprintf(data[i].name, "%s", names[rand() % 10]);
		data[i].year = years[rand() % 10];
		sprintf(data[i].post, "%s", posts[rand() % 10]); // Костыль #2
		data[i].pay = pays[rand() % 10];
		sprintf(data[i].education, "%s", educations[rand() % 10]);

	}

	printf("----- age > 60 ----- \n\n");

	for (int i = 0; i < 10; i++)
	{

		if ((2020 - data[i].year) > 60)
			printf("%s borns in %d, studied in %s and holds post %s, gets %d $.\n", data[i].name, data[i].year, data[i].education, data[i].post, data[i].pay);

	}

	return 0;
}
