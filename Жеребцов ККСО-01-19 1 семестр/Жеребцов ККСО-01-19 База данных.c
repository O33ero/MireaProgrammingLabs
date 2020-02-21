/*ККСО-01-19 Жеребцов К.А. База данных.*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*Список команд*/
char command_surname[] = "surname";
char command_id[]      = "id";
char command_add[]     = "add";
char command_clear[]   = "clear";
char command_all[]     = "all";
char command_exit[]    = "exit";
char command_remove[]  = "remove";
char command_search[]  = "search";
char command_save[]    = "save";

int cmp(char* str1, char* str2)                                        // Сравнение двух строк
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

/*Структура для хранения данных о каждом студенте*/
struct students
{
	int id;                                                             // Персональный номер в базе
	char second_name[50];                                               // Фамилия
	char first_name[50];                                                // Имя
	char third_name[50];                                                // Отчество
	int birth_year;                                                     // Год рождения
	char group_name[5];                                                 // Название группы
};

int main()
{
	
	setlocale(LC_ALL, "Rus");
	int i;

	struct students data[1000];
	FILE* database;
	

	if ((database = fopen("data.txt", "r")) == NULL)                     // Открытие файла
	{
		printf("Не удалось открыть базу учеников.\n");					 // Файл не найден    
		system("pause");
		return 0;
	}


	struct students temp;

	// Обнуление всех id в базе (нулевый id означает свободный id в базе)
	for (i = 0; i < 1000; i++)
	{
		data[i].id = 0;
	}

	// Заполнение базы из файла .txt
	while (1)
	{
		
		if (feof(database) != 0)                                          // Файл закончился
		{
			break;
		}
		
		fscanf(database, "%d %s %s %s %d %s\n", &temp.id, temp.second_name, temp.first_name, temp.third_name, &temp.birth_year, temp.group_name);
		data[temp.id - 1] = temp;
	}
	fclose(database);

	printf("Открыта база данных студентов.\n\nДоступные команды:");
	printf("\nНайти по фамилии:                                 -search surname *Фамилия*");
	printf("\nНайти по персональному номеру:                    -search id *Число*");
	printf("\nДобавить нового студента:                         -add");
	printf("\nУдалить студента из базы по фамилии:              -clear surname *Фамилия*");
	printf("\nУдалить студента из базы по персональному номеру: -clear id *Число*");
	printf("\nВывести всю базу данных на экран:                 -all");
	printf("\nСохранить текущее состояние базы данных:          -save");
	printf("\nДля завершения работы с базой:                    -exit");
	printf("\nДля выхода без сохранения изменений:              -remove");
	printf("\n\n");

	
	while (1)
	{	
		int is_found = 0;                                       // Найден хотя бы 1 элемент
		char dash;                                              // Наличие тире перед командой
		char temp1[50] = "";                                    // Временная переменная для хранения параметров команды
		int temp_int;                                           // Временная переменная для хранения числовых параметров команды
		char command[60] = "";                                  // Команда
		scanf("%c%s", &dash, &command);

		// Неверный формат ввода команды
		if (dash != '-')
		{
			printf("Нарушен формат ввода команды. Все команды ничанаются с символа '-'.\n\n");
			gets(command);
		}
		else
		{
			// Поиск по базе
			if (cmp(command, command_search))
			{
				scanf("%s", &command);

				// Поиск по фамилии
				if (cmp(command, command_surname))
				{
					scanf("%s", &temp1);

					for (i = 0; i < 1000; i++)
					{
						if (data[i].id != 0 && cmp(temp1, data[i].second_name))
						{
							is_found++;
							printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
						}
					}
					printf("\n\n");

					if (is_found == 0)
					{
						printf("Совпадений с %s не найдено.", temp1);
					}
					printf("\n\n");
					gets(command);                                    // Забирает мусор из stdin
					continue;
				}

				// Поиск в базе по id
				if (cmp(command, command_id))
				{
					scanf("%d", &temp_int);

					for (i = 0; i < 1000; i++)
					{
						if (data[i].id == temp_int)
						{
							is_found++;
							printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
						}
					}

					if (is_found == 0)
					{
						printf("Совпадений с %d не найдено.", temp_int);
					}

					printf("\n\n");
					gets(command);                                    // Забирает мусор из stdin
					continue;
				}

				printf("Неизвестная команда %s", command);
				printf("\n\n");
				gets(command);                                       // Забирает мусор из stdin
				continue;
			}

			// Добавление нового
			if (cmp(command, command_add))
			{
				for (i = 0; i < 1000; i++)
				{
					if (data[i].id == 0)
					{
						break;
					}
				}

				if (i == 999)
				{
					printf("Превышен лимит в 1000 записей.");
					printf("\n\n");
					gets(command);                                 // Забирает мусор из stdin
					continue;
				}
				data[i].id = i + 1;

				printf("Введите фамилию:        ");
				scanf("%s", &temp1);
				sprintf(data[i].second_name, "%s", temp1);

				printf("Введите имя:            ");
				scanf("%s", &temp1);
				sprintf(data[i].first_name, "%s", temp1);

				printf("Введите отчество:       ");
				scanf("%s", &temp1);
				sprintf(data[i].third_name, "%s", temp1);

				printf("Введите год рождения:   ");
				scanf("%d", &temp_int);
				data[i].birth_year = temp_int;

				printf("Введите учебную группу: ");
				scanf("%s", &temp1);
				sprintf(data[i].group_name, "%s", temp1);

				printf("\nСтудент добавлен в базу:\n");
				printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);

				printf("\n\n");
				gets(command);                                    // Забирает мусор из stdin
				continue;
			}

			// Удаление из базы
			if (cmp(command, command_clear))
			{
				scanf("%s", &command);

				// Удаление по фамилии
				if (cmp(command, command_surname))
				{
					scanf("%s", &temp1);

					printf("Студенты с фамилией %s.\n", temp1);
					for (i = 0; i < 1000; i++)
					{
						if (data[i].id != 0 && cmp(temp1, data[i].second_name))
						{
							is_found++;
							printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
						}
					}

					if (is_found == 0)
					{
						printf("Совпадений с %s не найдено.", temp1);
						printf("\n\n");
						gets(command);
						continue;
					}

					printf("Введите номер студента, которого необходимо удалить или 0 для отмены: ");
					scanf("%d", &temp_int);

					if (temp_int != 0)
					{
						printf("\nСтудент %s %d удален.", data[temp_int - 1].second_name, data[temp_int - 1].id);
						data[temp_int - 1].id = 0;
					}
					else
					{
						printf("Отмена удаления.");
					}
					printf("\n\n");
					gets(command);
					continue;
				}

				// Удаление по id
				if (cmp(command, command_id))
				{
					scanf("%d", &temp_int);
					printf("Студент с номером %d.\n", temp_int);
					i = temp_int - 1;

					if (data[i].id == 0)
					{
						printf("Совпадений с %d не найдено.", temp_int);
						printf("\n\n");
						gets(command);
						continue;
					}
					printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);

					printf("Введите номер студента, для подтверждения удаления или 0 для отмены: ");
					scanf("%d", &temp_int);

					if (temp_int == i + 1)
					{
						printf("\nСтудент %s %d удален.", data[temp_int - 1].second_name, data[temp_int - 1].id);
						data[temp_int - 1].id = 0;
					}
					printf("\n\n");
					gets(command);
					continue;
				}

				printf("Неизвестная команда %s", command);
				printf("\n\n");
				gets(command);                                    // Забирает мусор из stdin
				continue;
			}

			// Вывод всей базы
			if (cmp(command, command_all))
			{
				for (i = 0; i < 1000; i++)
				{
					if (data[i].id != 0)
					{
						is_found++;
						printf("*%d %s %s %s %d %s*\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
					}
				}

				if (is_found == 0)
				{
					printf("Не найдено ни одной записи.\n");
					printf("\n\n");
					gets(command);                                // Забирает мусор из stdin
					continue;
				}

				printf("\n\n");
				gets(command);                                    // Забирает мусор из stdin
				continue;
			}

			// Выход с сохранением изменений
			if (cmp(command, command_exit))
			{
				printf("Новая база данных успешно сохранена.\n\n");
				database = fopen("data.txt", "w");

				for (i = 0; i < 1000; i++)
				{
					if (data[i].id != 0)
					{
						fprintf(database, "%d %s %s %s %d %s\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
					}
				}
				fclose(database);
				break;
			}

			// Сохранение текущего состояния базы
			if (cmp(command, command_save))
			{
				printf("Новая база данных успешно сохранена.\n\n");
				database = fopen("data.txt", "w");

				for (i = 0; i < 1000; i++)
				{
					if (data[i].id != 0)
					{
						fprintf(database, "%d %s %s %s %d %s\n", data[i].id, data[i].second_name, data[i].first_name, data[i].third_name, data[i].birth_year, data[i].group_name);
					}
				}
				fclose(database);

				printf("\n\n");
				gets(command);                                    // Забирает мусор из stdin
				continue;
			}

			// Выход без сохраниения изменений
			if (cmp(command, command_remove))
			{
				printf("Завершение работы без сохранения изменений.\n");
				break;
			}

			// Команда не распознана
			printf("Неизвестная команда %s.", command);
			printf("\n\n");
			gets(command);                                          // Забирает мусор из stdin
			continue;
		}
	}

	printf("\n");
	system("pause");
	return 0;
}
