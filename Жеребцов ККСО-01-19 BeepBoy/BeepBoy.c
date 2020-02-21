#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
const char beepform[] = "Beep_ID,Beep_func,Beep_prog,";
const char class_cs[] = "class";
const char using_cs[] = "using System.IO;\n";

int cmp(char* str1, char* str2)                                        // Сравнение двух строк
{
	int i;
	if (str1 == NULL || str2 == NULL)
	{
		return 0;
	}
	for (i = 0; i < 6; i++)
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}
char* cat(char* str1, char* str2)                                      // Склейка двух строк
{
	int i;
	char* result = NULL;
	result = (char*)calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));// Выделение памяти
	for (i = 0; i < strlen(str1); i++)
	{
		result[i] = str1[i];                                           // Вся первая строка
	}
	for (i = strlen(str1); i < strlen(str1) + strlen(str2); i++)
	{
		result[i] = str2[i - strlen(str1)];                            // К всей второй строке
	}
	return result;
}

char* word_searcher(char* ch, char* word)                              // Собирает слова по символам
{
	if ((ch[0] >= 'A' && ch[0] <= 'Z') || (ch[0] >= 'a' && ch[0] <= 'z') || (ch[0] >= '0' && ch[0] <= '9') || ch[0] == '_')
	{
		if (word == NULL)
		{
			word = (char*)calloc(1, sizeof(char));
		}
		else
		{
			word = (char*)realloc(word, strlen(word) + 1, sizeof(char));
		}
		word = cat(word, ch);
		return word;
	}
	else
	{
		free(word);

		return NULL;
	}
}


void new_beep_data(int id, char* func, char* programm)                   // Добавление нового BB в базу
{
	FILE* data_csv;
	data_csv = fopen("beepdata.csv", "a");

	fprintf(data_csv, "\n%d,%s,%s,", id, func, programm);
	fclose(data_csv);
}

char* new_beep_boy(int id, char* func, char* programm)                  // Создание строки с новым BB, которая запишется в файл
{

	char* result = NULL;
	result = (char*)calloc(50, sizeof(char));
	sprintf(result, "\nBB(%d,\"%s\",\"%s\");\n", id, func, programm);
	return result;
}
int main()
{
	LPCWSTR name_dir = L".\\c-file\\*";                                 // Строка с адресом директории с файлами. LPCWSTR - для функции FindFirstFile()
	HANDLE search_file;                                                 //
	WIN32_FIND_DATA dir;                                                //
	search_file = FindFirstFile(name_dir, &dir);                        // Находит первый файл в директории

	FILE* file;                                                         // Поток из файла

	char* name_file = NULL;                                             // Адрес файла
	char* programm = NULL;                                              // Имя файла с форматом
	int* buffer = NULL;                                                 // Буффер перезаписи
	char* word = NULL;                                                  // Последнее слово из файла
	char* str = NULL;                                                   // Буффер строки
	int* ch = NULL;                                                     // Буффер последнего символа из файла

	char prev_ch = '?';
	int comment = 0;
	int c_file = 0;   // 1 - c                                          // Параметр формата файла 
	                  // 2 - c++
	                  // 3 - c#


	ch = (int*)calloc(2, sizeof(int));
	buffer = (int*)calloc(2, sizeof(int));

	FindNextFile(search_file, &dir);                                    // Поиск следующего файла в директории

	FILE* new_file;                                                     // Поток нового файла, в который перезаписывается исходный

	FILE* func_file;                                                    // Поток из файла с функциями, для каждого языка свой файл

	FILE* data_csv;                                                     // Поток в файл с базой BB

	if ((data_csv = fopen("beepdata.csv", "r+")) == NULL)               // Открытие файла с базой BB
	{
		data_csv = fopen("beepdata.csv", "a");
		fprintf(data_csv, "%s", beepform);
	}
	fclose(data_csv);

	FILE* prev_id;                                                      // Поток из файла для хранения сквозного id
	int id = 0;

	if ((prev_id = fopen("prev_id.txt", "r+")) == NULL)                 // Узнает ID нового BB
	{
		printf("ID_file is not found. ID new BB is 100\n");
	}
	else
	{
		fscanf(prev_id, "%d", &id);
		fclose(prev_id);
	}

	int func_is_add = 0;                                                // Количество добавленых функций в программу (всегда <= 1)
	int using_is_add = 0;                                               // Количество подключенных функция (для файлов C#, всегда <= 1)


	/* Начинаяется основный блок программы.
	   Состоит из нескольких циклов:
	   1) Перебор файлов
	   2) Перебор символов
	   3) Перебор символов после ключевых слов
	   После прохождения этих этапов(циклов) программа добавляет нового BB */


	while (FindNextFile(search_file, &dir) != NULL)                     // 1. Перебор файлов
	{
		char directory[] = ".\\c-file\\";                               // Сбор строки адреса открытого файла      
		name_file = (char*)malloc(sizeof(dir.cFileName), sizeof(char)); // Память для адреса файла
		programm = name_file;
		sprintf(name_file, "%ws", dir.cFileName);                       // Переводит WCHAR в char
		name_file = cat(directory, name_file);                          // Приклеивает к адресу папки название файла



		if ((file = fopen(name_file, "r")) == NULL)                     // Открытие файла
		{
			printf("Cannot open %s.\n", name_file);                     // Файл не найден    
		}
		else {															// Файл открыт



			                                                           // Формат открытого файла
			switch (name_file[strlen(name_file) - 1])                  // Проверяет, какой формат файла
			{
			case 'c':
				c_file = 1;
				break;
			case 'p':
				c_file = 2;
				break;
			case 's':
				c_file = 3;
				break;
			}


			new_file = fopen(".\\c-file\\1.txt", "a");                 // Открытие нового файла, в который будет происходить перезапись
			
											
																	  
			// Ответвление для файлов .c
			if (c_file == 1) {
				while ((ch[0] = fgetc(file)) != EOF)                   // 2. Перебор символов
				{
					fputc(ch[0], new_file);
				next_c:
					if (ch[0] == '>' && func_is_add == 0)              // Ключевое слово (отвитвление) для добавление функции
					{
						while ((ch[0] = fgetc(file)) != EOF)           // 3. Перебор символов после ключевых слов
						{
							if (ch[0] == ' ' || ch[0] == '\t' || ch[0] == '\n')
							{
								fputc(ch[0], new_file);
							}
							else
							{
								if (ch[0] == '#')
								{
									fputc(ch[0], new_file);
									break;
								}
								else                                    // Три этапа пройдено, функция добавлена
								{
									func_is_add++;

									if ((func_file = fopen("func_beep_c.txt", "r")) == NULL)
									{
										fputc(ch[0], new_file);
										printf("Function file for C not found.\n");
										break;
									}
									else
									{
										while ((buffer[0] = fgetc(func_file)) != EOF)
										{
											fputc(buffer[0], new_file);
										}
										fclose(func_file);
										fputc(ch[0], new_file);
										break;
									}
								}
							}
						}
					}
					if (ch[0] == '(')                                   // Ключевое слово для добавление нового BB
					{
						comment = 0;
						while ((ch[0] = fgetc(file)) != EOF)            // 3. Перебор символов после ключевого слова
						{
							fputc(ch[0], new_file);
							if (ch[0] == ')')
							{
								while ((ch[0] = fgetc(file)) != EOF)
								{
									fputc(ch[0], new_file);
									if (ch[0] == '{')
									{
										if (word != NULL)               // Три эпата пройдено, можно добавлять нового BB   
										{
											printf("Added new BB_%d in %s.\n", id, programm);
											new_beep_data(id, word, programm);

											str = new_beep_boy(id, word, programm);
											fputs(str, new_file);
											fflush(new_file);

											id++;
											prev_id = fopen("prev_id.txt", "w");
											fprintf(prev_id, "%d", id);
										}
										free(word);
										word = NULL;
										goto next_c;

									}
									else
									{
										if (ch[0] == '/' && prev_ch == '/')
										{
											comment++;
										}
										else
										{	
											if (ch[0] != ' ' && ch[0] != '\n' && ch[0] != '/' && comment == 0)
											{
												free(word);
												word = NULL;
												goto next_c;
											}
										}

									}
									prev_ch = ch[0];
								}
							}

						}
					}
					else
					{
						word = word_searcher(ch, word);                           // Собирается последнее слово
					}
				}
			}

			// Ответвление для файлов .cpp
			if (c_file == 2) {
				while ((ch[0] = fgetc(file)) != EOF)                   // 2. Перебор символов
				{

					fputc(ch[0], new_file);
					next_cpp:
					if (ch[0] == '>' && func_is_add == 0)              // Ключевое слово для добавления функции
					{
						while ((ch[0] = fgetc(file)) != EOF)           // 3. Перебор символов после ключевого слова
						{
							if (ch[0] == ' ' || ch[0] == '\t' || ch[0] == '\n')
							{
								fputc(ch[0], new_file);
							}
							else
							{
								if (ch[0] == '#')
								{
									fputc(ch[0], new_file);
									break;
								}
								else
								{
									func_is_add++;

									if ((func_file = fopen("func_beep_cpp.txt", "r")) == NULL)
									{
										fputc(ch[0], new_file);
										printf("Function file for C++ not found.\n");
										break;
									}
									else
									{
										while ((buffer[0] = fgetc(func_file)) != EOF)
										{
											fputc(buffer[0], new_file);
										}
										fclose(func_file);
										fputc(ch[0], new_file);
										break;
									}
								}
							}
						}
					}
					if (ch[0] == '(')                                      // Ключевое слово для добавления нового BB
					{
						comment = 0;
						while ((ch[0] = fgetc(file)) != EOF)               // 3. Перебор символов после ключевого слова
						{
							fputc(ch[0], new_file);
							if (ch[0] == ')')
							{
								while ((ch[0] = fgetc(file)) != EOF)
								{
									fputc(ch[0], new_file);
									if (ch[0] == '{')
									{
										if (word != NULL)                  // Три эпата пройдено, можно добавлять нового BB   
										{
											printf("Added new BB_%d in %s.\n", id, programm);
											new_beep_data(id, word, programm);

											str = new_beep_boy(id, word, programm);
											fputs(str, new_file);
											fflush(new_file);

											id++;
											prev_id = fopen("prev_id.txt", "w");
											fprintf(prev_id, "%d", id);
										}
										free(word);
										word = NULL;
										goto next_cpp;

									}
									else
									{
										if (ch[0] == '/' && prev_ch == '/')
										{
											comment++;
										}
										else
										{
											if (ch[0] != ' ' && ch[0] != '\n' && ch[0] != '/' && comment == 0)
											{
												free(word);
												word = NULL;
												goto next_cpp;
											}
										}

									}
									prev_ch = ch[0];
								}
							}

						}
					}
					else
					{
						word = word_searcher(ch, word);                           // Собирается последнее слово
					}
				}
			}

			// Ответвление для фалов .cs
			if (c_file == 3)
			{
				while ((ch[0] = fgetc(file)) != EOF)                          // 2. Перебор символов
				{	
					if (using_is_add == 0)                                    // В начало добавляется заголовочный файл
					{
						fputs(using_cs, new_file);
						using_is_add = 1;
					}
					fputc(ch[0], new_file);
					next_cs:
					
					if (func_is_add == 0 && cmp(word, class_cs))              // Ключевое слово для добавления функции
					{
						while ((ch[0] = fgetc(file)) != EOF)                  // 3. Перебор символов после ключевого слова
						{
							if (ch[0] == '{')
							{
								fputc(ch[0], new_file);
								func_is_add++;

								func_file = fopen("func_beep_cs.txt", "r");

								while ((buffer[0] = fgetc(func_file)) != EOF)
								{
									fputc(buffer[0], new_file);
								}
								fclose(func_file);
								break;
							}
							fputc(ch[0], new_file);
						}

					}
					// Добавление нового BeepBoy
					if (ch[0] == '(')                                          // Ключевое слово для добавления нового BB
					{
						comment = 0;
						while ((ch[0] = fgetc(file)) != EOF)                   // 3. Перебор символов после ключевого слова
						{
							fputc(ch[0], new_file);
							if (ch[0] == ')')
							{
								while ((ch[0] = fgetc(file)) != EOF)
								{
									fputc(ch[0], new_file);
									if (ch[0] == '{')
									{
										if (word != NULL)                      // Три эпата пройдено, можно добавлять нового BB   
										{
											printf("Added new BB_%d in %s.\n", id, programm);
											new_beep_data(id, word, programm);

											str = new_beep_boy(id, word, programm);
											fputs(str, new_file);
											fflush(new_file);

											id++;
											prev_id = fopen("prev_id.txt", "w");
											fprintf(prev_id, "%d", id);
										}
										free(word);
										word = NULL;
										goto next_cs;

									}
									else
									{
										if (ch[0] == '/' && prev_ch == '/')
										{
											comment++;
										}
										else
										{
											if (ch[0] != ' ' && ch[0] != '\n' && ch[0] != '/' && comment == 0)
											{
												free(word);
												word = NULL;
												goto next_cs;
											}
										}

									}
									prev_ch = ch[0];
								}
							}

						}
					}
					else
					{
						word = word_searcher(ch, word);                           // Собирается последнее слово
					}
					
				}
			}
			




			fclose(file);                                                        // Исходный файл закрывается
			remove(name_file);                                                   // Исходный файл уничтожается, всё переписано в новый файл
			fclose(new_file);                                                    // Новый файл закрывается
			rename(".//c-file//1.txt", name_file);                               // Исходный файл подменяется на новый файл со встренными BB

			func_is_add = 0;                                                     // Счетчики добавленых функций закрывается
			using_is_add = 0;
		}


		
		printf("\n");              
		free(name_file);                                                        // Освобождается память
	}

	/* После перебора всех файлов, на месте старых файлов
	   появляются новые, модифицированные файлы того же формата,
	   что были и исходные.                                     */



	system("pause");
	return 0;
}