/*Жеребцов ККСО-01-19 НОД и НОК*/
#include <stdio.h>
#include <locale.h>

int gcd(int a, int b)
{
	if (a < b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}

	int r;
	while ((a % b) != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return b;
}

int main()
{
	setlocale(LC_ALL, "Rus");


	int a, b;


	printf("Введите два числа: ");
	scanf("%d %d", &a, &b);

	printf("\n(%d,%d) = %d\n", a, b, gcd(a, b));        // Алгоритм Евклида
	printf("[%d,%d] = %d\n", a, b, (a * b) / gcd(a, b));// НОК(a,b) = (a*b) / НОД(a,b)
	return 0;
}