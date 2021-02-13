#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int main()
{
	FILE *f;
	f = fopen("/dev/input/event2", "r"); // Event-файл для клавиатуры

	struct input_event k, u1, u2; // Структура с ппоследней нажатой кнопкой

	unsigned long int first_time; // Первая нажатая кнопка
	int first_code = 0;

	unsigned long int last_time; // Последняя (на данный момент) нажатая кнопка
	int last_code = 0;

	unsigned long int count = 0; // Кол-во нажатий от начала работы

	while (1)
	{
		fread(&k, sizeof(k), 1, f);
		fread(&u1, sizeof(k), 1, f);
		fread(&u2, sizeof(k), 1, f);

		fread(&k, sizeof(k), 1, f);
		fread(&u1, sizeof(k), 1, f);
		fread(&u2, sizeof(k), 1, f);

		if (k.value == 1)
			break;

		if (first_code == 0)
		{
			first_code = k.value;
			first_time = k.time.tv_sec;
		}

		last_code = k.value;
		last_time = k.time.tv_sec;

		count += 1;

		system("clear");
		printf("***\n c = %ld, t = %ld ", count, last_time - first_time);

		float t = (float)(last_time - first_time);
		float c = (float)count;

		printf("\n***\n Action per second = %f ", c / t);
		printf("\n***\n Press ESC or CTR+Z to exit... \n***\n");
	}

	fclose(f);
	return 0;
}
