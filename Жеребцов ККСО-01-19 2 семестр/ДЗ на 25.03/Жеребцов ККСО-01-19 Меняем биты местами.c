﻿/*Жеребцов ККСО-01-19 Меняем биты местами*/
#include <stdio.h>

int pow2(int a)
{
	if (a == 0)
		return 1;
	else
		return 2 * pow2(a - 1);
}

int main()
{
	int n, l, r;			// Само число и позиции битов, которые надо поменять местами
	int left, right;		// Конкретные биты (0 или 1), которые стоят на позяциях l и r 
	scanf("%d %d %d", &n, &l, &r);

							// Посмотрим: какие биты расположены на позициях r и l. Используем для этого маску.
	int mask = pow2(l);	    // Маска состоит из одного значимого бита. Он находится на позиции, которую надо проверить (r или l).
	if ((n & mask) == mask) // Если при наложении маски на один бит получается маска, то этот бит равен 1
		left = 1;
	else
		left = 0;

	mask = pow2(r);         // Аналогичная операция для другого бита
	if ((n & mask) == mask)
		right = 1;
	else
		right = 0;


	printf("\n%d -> ", n);


	if (left != right)      // Если биты одни и те же, то всё ОК. Если разные, то, очевидно, меняем их местами
	{
		if (left == 0)      // Если стоит 0, то прибавляем степень 2,
			n = n + pow2(l);
		else                // И отнимаем в противном случае
			n = n - pow2(l);

		if (right == 0)
			n = n + pow2(r);
		else
			n = n - pow2(r);
	}

	printf("%d <==> %d -> %d", l, r, n);
	return 0;
}