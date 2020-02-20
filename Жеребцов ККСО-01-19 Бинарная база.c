#include <stdio.h>
#include <malloc.h>
struct students
{
	char str[16];
	unsigned int group;
	int mark[3];
	unsigned short pay;
};


int main()
{

	int ch;
	int count = 0;

	char str[16];      // Строка имени
	unsigned int group;// Номер группы
	char markchar[3];  // Оценки (1 байт) (по условию оценка <= 100, 
	int markint[3];    // для кодирования 100 достаточно 1 байта)
	unsigned short pay;// Степендия
	char ch1;          // Между оценками и степендией стоит 1 байт, равный 0

	struct students* data = NULL;


	FILE* file = fopen("task.bin", "rb");

	/*Что мы знаем про бинарный файл:
		 - Фамилия      16 байт
		 - Номер группы 2 байта
		 - Оценки       3 раза по 1 байту
		 - Разделение   1 байт, равный 0
		 - Степендия    2 байта

	*/
	while ((ch = fgetc(file)) != EOF)
	{	
		///// Парсинг бинарного файла /////
		fseek(file, -1, SEEK_CUR);                   // Возвращает один символ, потерянный при проверке    
		fread(str, sizeof(char), 16, file);          // ФамилияИО     (16 байт)
		fread(&group, sizeof(unsigned int), 1, file);// Номер группы  (2 байта)
		fread(&markchar[0], sizeof(char), 1, file);  // Оценка     (3 * 1 байт)
		fread(&markchar[1], sizeof(char), 1, file);
		fread(&markchar[2], sizeof(char), 1, file);
		fread(&ch1, sizeof(char), 1, file);          // 1 разделительный байт (с ним работает, без него - нет)
		markint[0] = (int)markchar[0];               // 1 байт -> в int
		markint[1] = (int)markchar[1];
		markint[2] = (int)markchar[2];
		fread(&pay, sizeof(unsigned short), 1, file);// Степендия     (2 байта)
		


		///// Добавление студента в базу /////
		data = (struct students*) realloc(data, sizeof(struct students) * (count + 1));

		for (int i = 0; i < 16; i++)
		{
			data[count].str[i] = str[i];
		}

		data[count].group = group;

		data[count].mark[0] = markint[0];
		data[count].mark[1] = markint[1];
		data[count].mark[2] = markint[2];

		data[count].pay = pay;

		count++;
	//	printf("%s %d %d %d %d %d\n", str, group, markint[0], markint[1], markint[2], pay);
	}

	fclose(file);
	printf("//SURNAME      //GROUP //MARKS    //PAY  //NEW PAY\n");

	///// Перепись нового файла /////
	file = fopen("result.bin", "wb");

	for (int i = 0; i < count; i++)
	{
		if (data[i].mark[0] >= 50 && data[i].mark[1] >= 50 && data[i].mark[2] >= 50)
		{
			printf("%-16s %4d %3d %3d %3d %4d", data[i].str, data[i].group, data[i].mark[0], data[i].mark[1], data[i].mark[2], data[i].pay);

			data[i].pay = data[i].pay * 1.3;

			printf(" --> %4d\n",data[i].pay);
		}
		else
		{
			printf("%-16s %4d %3d %3d %3d %4d\n", data[i].str, data[i].group, data[i].mark[0], data[i].mark[1], data[i].mark[2], data[i].pay);
		}


		// Как считывали, так и записываем
		ch1 = '\0';
		fwrite(data[i].str, sizeof(char), 16, file);
		fwrite(&data[i].group, sizeof(unsigned int), 1, file);
		fwrite(&data[i].mark[0], sizeof(char), 1, file);
		fwrite(&data[i].mark[1], sizeof(char), 1, file);
		fwrite(&data[i].mark[2], sizeof(char), 1, file);
		fwrite(&ch1, sizeof(char), 1, file);
		fwrite(&data[i].pay, sizeof(unsigned short), 1, file);
	}

	fclose(file);
	free(data);
	return 0;
}
