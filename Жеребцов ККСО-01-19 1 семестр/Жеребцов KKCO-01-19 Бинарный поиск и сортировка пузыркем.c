
#include <stdio.h>
#include <time.h>

int main() {

	srand(time(NULL));                 // Рандомайзер
	int n, x, i, j, temp, error = 0;   /* n     - размер массива
										* x     - искомое число
										* i,j   - переменные для цикла for
										* temp  - временная переменная
										* error - ошибки в поиске числа x в массиве */
	scanf("%d %d", &n, &x);
	int arr[2 * n];                    // Размер массива - 2 * n

	printf("Original array:\n");
	for (i = 0; i < 2 * n; i++)        // Заполнение массива
	{
		arr[i] = rand() % (2 * n);     // Заполняет массив случайными числами в диапазоне [0;2n)     

		temp = arr[i];
		printf("%d ", temp);
	}
	printf("\n\n");



	
	for (i = 0; i < 2 * n; i++)			///////////////////////////////////
	{
		for (j = 0; j < 2 * n - 1; j++)
		{
			if (arr[j + 1] < arr[j])
			{							// Сортировка пузырком ////////////
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}									///////////////////////////////////

	
	
	
	printf("Sorted array:\n");
	for (i = 0; i < 2 * n; i++)         // Вывод сортированного массива 
	{
		temp = arr[i];
		printf("%d ", temp);
	}
	printf("\n\n");
	
	
	//////////////// Бинарный поиск ////////////////
	int left_l = 0, right_l = 2 * n, pos_x, middle = n;
										/* left_l  - левый предел рассматриваемой части массива
										 * right_l - правый предел рассматриваемой части массива
										 * pos_x   - позиция x в сортированном массиве
										 * middle  - значение в середине рассматриваемой части массива */
	while (1)  
	{
		if (right_l - left_l <= 1)      // Не может найти x в массиве 
		{	
			error++;
			printf("Error. Cannot find %d.\n", x);
			break;
		}
		if (arr[middle] == x)			// Нашел x в массиве
		{
			pos_x = middle;
			break;
		}

		if (arr[middle] > x)            // x находится левее центра массива
		{
			right_l = middle;
			middle = (left_l + right_l) / 2;
		}
		else                            // x находится правее центра массива
		{
			left_l = middle;
			middle = (left_l + right_l) / 2;
		}
	}
	/////////////////////////////////////////////////
	
	
	left_l = pos_x;                     // Левый предел диапазона x в массиве
	right_l = pos_x;					// Правый предел диапазона x в массиве
	while (!error)
	{
		if (left_l > 0)
		{
			if (arr[left_l - 1] == x)   // Левый элемент равен x
			{
				left_l = left_l - 1;
			}
			else                        // Слева больше нет значений равных x
			{
				break;
			}
		}
		else                            // Первый элемент массива равен x
		{
			break;
		}
	}

	while (!error)
	{
		if (right_l < 2* n - 1)       
		{
			if (arr[right_l + 1] == x)  // Правый элемент равен x
			{
				right_l = right_l + 1;
			}
			else                        // Слева больше нет значений равных x
			{
				break;
			}
		}
		else                            // Последний элемент равен x
		{
			break;
		}
	}
	
	
	
	
	if (!error)
	{
		if (left_l == right_l)          // Только один элемент x в массиве
		{
			printf("Position: %d\n\n", left_l);
		}
		else                            // Диапазон x в массиве [left_l; right_l] 
		{
			printf("Range: %d to %d\n\n", left_l + 1, right_l + 1);
		}
	}





	return 0;
}
