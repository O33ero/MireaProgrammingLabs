/*Жеребцов ККСО-01-19 База данных маршрутов */
#include <stdio.h>
#include <malloc.h>

struct marshrut
{
	int number;
	char nameA[16];
	char nameB[16];
	double distance;
};


int cmp_const(char* str1, const char* str2)                            // Сравнение строки с константной строкой
{
	int i;
	if (str1 == NULL || str2 == NULL)
	{
		return 0;
	}
	for (i = 0; 1; i++)
	{

		if (str1[i] != str2[i])
		{
			return 0;
		}
		if (str1[i] == str2[i] && str1[i] == '\0')
		{
			break;
		}
	}
	return 1;
}

int cmp(char* str1, char* str2)                                         // Сравнение двух строк
{
	int i;
	if (str1 == NULL || str2 == NULL)
	{
		return 0;
	}
	for (i = 0; 1; i++)
	{

		if (str1[i] != str2[i])
		{
			return 0;
		}
		if (str1[i] == str2[i] && str1[i] == '\0')
		{
			break;
		}
	}
	return 1;
}

void cpy(char* str1, char* str2)				          // Копирование строки str1 в строки str2
{
	for (int i = 0; ; i++)
	{
		str2[i] = str1[i];
		if (str1[i] == '\0')
			break;
	}

}


void printway(struct marshrut a)                                           // Вывод маршрута                            
{
	printf("#%d  %s --%g--> %s\n", a.number, a.nameA, a.distance, a.nameB);
}


// Функцианал

// Самое короткое расстояние
void command_short(struct marshrut* data, int last_i)
{
	double min = data[0].distance;

	for (int i = 1; i <= last_i; i++)
	{
		if (data[i].distance < min)
			min = data[i].distance;
	}

	for (int i = 0; i <= last_i; i++)
	{
		if (data[i].distance == min)
			printway(data[i]);
	}

	printf("\n");

}

// Поиск среди пунктов отправления и прибытия
void command_fromto(struct marshrut* data, int last_i)
{
	int is_found = 0;
	char temp1[16] = "";                         // Временная переменная для хранения параметров команды                                            

	scanf("%16s", temp1);

	for (int i = 0; i <= last_i; i++)
	{
		if (cmp(temp1, data[i].nameA) || cmp(temp1, data[i].nameB))
		{
			printway(data[i]);
			is_found = 1;
		}
	}

	if (is_found == 0)
		printf("No matches.\n");

	printf("\n");

}

// Изменить номер маршрута
void command_change(struct marshrut* data, int last_i)
{
	int is_found = 0;
	int temp1_int, temp2_int;

	scanf("%d %d", &temp1_int, &temp2_int);

	// Проверка на корректность изменений
	for (int i = 0; i <= last_i; i++)                                    
	{
		if (data[i].number == temp2_int)
		{
			is_found = 1;
			break;
		}
	}

	if (is_found == 1)
	{
		printf("Cannot change number.");
		printf("\n\n");
		return;
	}

	for (int i = 0; i <= last_i; i++)
	{
		if (data[i].number == temp1_int)
		{
			is_found = 1;
			data[i].number = temp2_int;
			printf("Complete.\n\n");
			return;
		}
	}

	// Нет совпадений
	if (is_found == 0)
		printf("No matches.\n");

	printf("\n\n");

}

// Вывод всех маршрутов в порядке ввода
void command_all(struct marshrut* data, int last_i)
{
	for (int i = 0; i <= last_i; i++)
	{
		printway(data[i]);
	}
	printf("\n");
}

// Вывод всех маршрутов в порядке возрастания номера маршрута
void command_number(struct marshrut* data, int last_i)
{
	struct marshrut temp[10];

	// Копирование структуры во временную структуру
	for (int i = 0; i <= last_i; i++)
	{
		temp[i].distance = data[i].distance;
		cpy(data[i].nameA, temp[i].nameA);
		cpy(data[i].nameB, temp[i].nameB);
		temp[i].number = data[i].number;
	}

	// Сортировка номеров структуры
	struct marshrut t;
	for (int i = 0; i < last_i; i++)
	{
		for (int j = 0; j <= last_i; j++)
		{
			if (temp[i].number > temp[i + 1].number)
			{
				t = temp[i];
				temp[i] = temp[i + 1];
				temp[i + 1] = t;
			}
		}
	}

	// Вывод временной структуры
	for (int i = 0; i <= last_i; i++)
	{
		printway(temp[i]);
	}
	printf("\n");
}

int main()
{



	struct marshrut data[10]; // База данных из 10 маршрутов
	struct marshrut temp;     // Временная структура

	int last_i;               // Индекс последней записи в базе



	printf("Start ---Distance--> Finish");
	printf("\t\t(To complete input routes type 0.)\n\n");

	for (int i = 0; i < 11; i++)
	{
		// Ввод маршрутов и запись в базу
		scanf("%16s", temp.nameA);
		if (temp.nameA[0] == '0' || i == 10)
		{
			last_i = i - 1;
			break;
		}

		scanf(" %lf %16s", &temp.distance, temp.nameB);

		temp.number = i + 1;
		data[i] = temp;
	}

	printf("\n\n");
	printf("-----------------------------------------------------------");
	printf("\nSearch shortest way:                                 -short");
	printf("\nSearch among departure and arrival point:            -fromto *name*");
	printf("\nChange route number:                                 -change *old *new");
	printf("\nPrint all data:                                      -all");
	printf("\nPrint all number routes in ascending order:          -number");
	printf("\nExit:                                                -exit");
	printf("\n\n");

	while (last_i != -1)
	{
		char dash;                                              // Наличие тире перед командой
		double temp1_int, temp2_int;                            // Временная переменная для хранения числовых параметров команды
		char command[16] = "";									// Команда
		fgets(command, 16, stdin);                              // Забирает мусор из ввода
		scanf("%c%16s", &dash, command);

		// Неверный формат ввода команды
		if (dash != '-')
		{
			printf("Error. All commands begin by symbol '-'.\n\n");
			continue;
		}
		else
		{

			// Поиск самого короткого маршрута
			if (cmp_const(command, "short"))
			{
				command_short(data, last_i);
				continue;
			}

			// Поиск среди пунктов отправления
			if (cmp_const(command, "fromto"))
			{
				command_fromto(data, last_i);
				continue;
			}

			//Изменить номер маршрута
			if (cmp_const(command, "change"))
			{
				command_change(data, last_i);
				continue;
			}

			//Вывод всех маршрутов
			if (cmp_const(command, "all"))
			{
				command_all(data, last_i);
				continue;
			}

			//Вывод в порядке убывания номеров маршрутов
			if (cmp_const(command, "number"))
			{
				command_number(data, last_i);
				continue;
			}

			//Выход
			if (cmp_const(command, "exit"))
			{
				break;
			}

			//Команда не найдена
			printf("Unknown command.\n\n");
		}
	}


	return 0;
}
