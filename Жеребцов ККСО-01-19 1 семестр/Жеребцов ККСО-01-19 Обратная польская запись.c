#include <stdio.h>
#include <malloc.h>



int k_d = -1;                                                                              // Индекс последнего значимого элемента в стеке чисел


char str[40];                                                                              // Первоначальное выражение
char polska_str[40] = "";                                                                  // Обратная польская запись
char stack_operation[20] = "";                                                             // Стек операций
double stack_number[30];                                                                   // Стек чисел


// Является ли символ операцией?
int is_operation(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return 1;
	else
		return 0;
}

// Добавляет операцию в стек
char push_one_stack_operation()
{
	int i;
	char ch;
	for (i = 0; is_operation(stack_operation[i]); i++)
	{
		if (is_operation(stack_operation[i + 1]) == 0)
		{
			ch = stack_operation[i];
			if (ch != '(')
			{
				stack_operation[i] = '\0';
			}
			return ch;
		}
	}

}

// Добавляет число 'a' в стек
void add_stack_num(double a)
{
	stack_number[k_d + 1] = a;
	k_d++;
}

// Выкидывает весь стек операций в польскую запись
void push_all_stack_operation()
{
	while (is_operation(stack_operation[0]))
	{
		char t = push_one_stack_operation();
		if (t == '(')
		{

			break;
		}
		sprintf(polska_str, "%s %c ", polska_str, t);
	}
}

// Проверка приоритета операции
int priority(char prev_ch, char ch)
{
	int pr_prev_ch = 0;
	int pr_ch = 0;

	switch (prev_ch)
	{
	case '+':
		pr_prev_ch = 1;
		break;
	case '-':
		pr_prev_ch = 1;
		break;
	case '*':
		pr_prev_ch = 2;
		break;
	case '/':
		pr_prev_ch = 2;
		break;

	}

	switch (ch)
	{
	case '+':
		pr_ch = 1;
		break;
	case '-':
		pr_ch = 1;
		break;
	case '*':
		pr_ch = 2;
		break;
	case '/':
		pr_ch = 2;
		break;

	}

	if (pr_prev_ch == pr_ch)
	{
		sprintf(polska_str, "%s %c ", polska_str, push_one_stack_operation(stack_operation));
		return 1;
	}
	else
	{
		if (pr_prev_ch > pr_ch)
		{
			push_all_stack_operation();
			return 1;
		}
		return 0;
	}
}

// Проверка приоритета операции и добавление в стек
void add_stack_operation(char ch)
{
	char c = stack_operation[0];
	int i, j;



	for (i = 1; is_operation(c); i++)
	{
		c = stack_operation[i];
	}

	if (!is_operation(stack_operation[0]))
	{
		stack_operation[0] = ch;
	}
	else
	{
		// Закрывающая скобка выталкивает все из стека до открывающей скобки
		if (ch == ')')
		{
			while (1)
			{
				char t = push_one_stack_operation();

				if (t == '(')
				{
					for (i = 1; 1; i++)
					{
						if (!is_operation(stack_operation[i]))
						{
							break;
						}
					}
					stack_operation[i - 1] = '\0';
					break;
				}
				sprintf(polska_str, "%s %c ", polska_str, t);
			}
		}
		else
		{
			// Если операция не является скобкой и последняя операция не скобка --> Проверить приоритет
			if (ch != '(' && stack_operation[i - 2] != '(' && priority(stack_operation[i - 2], ch))
			{
				for (i = 0; 1; i++)
				{
					if (stack_operation[i] == '\0')
					{
						break;
					}

				}
				stack_operation[i] = ch;
			}
			// Если операция ниже приоритетом или является скобкой --> Поместить в стек
			else
			{
				stack_operation[i - 1] = ch;
			}
		}
	}


}

// Достает элемент из стека
double push_stack_num()
{
	double returned = stack_number[k_d];
	k_d--;
	stack_number[k_d + 1] = 0;
	return returned;
}

// Перевод символа в цифру
double char_to_double(char ch)
{
	switch (ch)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case '0':
		return 0;
	}
}

// Перевод строки в число
double str_to_double(double num, char ch) {
	return num * 10 + char_to_double(ch);
}

// "Красивый" вид польской записи. Каждый элемент через пробел.
void kracivo()
{
	int i, space = 0, k = 0;
	char ch;
	for (i = 0; 1; i++)
	{
		polska_str[i - k] = polska_str[i];
		ch = polska_str[i];
		if (ch == '\0')
			break;

		if (ch == ' ')
			space++;
		else
			space = 0;

		if (space >= 2)
			k++;
	}
}

int main()
{


	//stack_number = (double*)calloc(10, sizeof(double));
	//stack_operation = (char*)calloc(10, sizeof(char));


	char ch;
	int i, k;

	//Обратная Польская Запись//////////////////////////////////////////////////////////////////////////////////////////////
	gets(str);
	fflush(stdin);
	printf("\n");

	ch = str[0];
	for (int i = 1; ch != '\0'; i++)
	{
		if ((ch >= '0' && ch <= '9'))
		{
			sprintf(polska_str, "%s%c", polska_str, ch);                                             // Переносим числа в польскую запись
		}
		else
		{
			if (is_operation(ch))
			{
				sprintf(polska_str, "%s%c", polska_str, ' ');
				add_stack_operation(ch); // Кидаем операцию в стек
			}
		}

		ch = str[i];
	}


	push_all_stack_operation();                                                                      // Достаем из стека оставшиеся операции

	//printf("%s\n", polska_str);                                                                    // Некрасивая строка польской записи
	kracivo();                                                                                       // Красивая строка польской записи
	printf("%s\n", polska_str);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Результат арифметического выражения//////////////////////////////////////////////////////////////////////////////////////

	double right = 0, left = 0, temp = 0;
	int is_found = 0;
	ch = '1';
	for (i = 0; ch != '\0'; i++)
	{
		ch = polska_str[i];

		if ((ch >= '0' && ch <= '9') || ch == ' ')                                                 // Собираем число и кидаем в стек
		{
			if (ch == ' ' && is_found > 0)
			{
				add_stack_num(temp);                                                               // Число собрано -----> Стек
				temp = 0;
				is_found = 0;
			}
			else
			{
				if (ch >= '0' && ch <= '9')
				{
					temp = str_to_double(temp, ch);                                                 // Ищет конец числа
					is_found++;
				}
			}
		}
		if (is_operation(ch))                                                                       // Символ операции
		{
			right = push_stack_num();                                                               // Достает два числа из стека
			left = push_stack_num();

			switch (ch)                                                                             // Выполняет операцию и кидает в стек результат
			{
			case '+':
				right = right + left;
				add_stack_num(right);
				right = 0;
				left = 0;
				break;
			case '-':
				right = left - right;
				add_stack_num(right);
				right = 0;
				left = 0;
				break;
			case '*':
				right = right * left;
				add_stack_num(right);
				right = 0;
				left = 0;
				break;
			case '/':
				if (right == 0)
				{
					printf("ERROR --> Division by 0.\n");
					system("pause");
					return 0;
				}
				right = left / right;

				add_stack_num(right);
				right = 0;
				left = 0;
				break;
			}
		}

	}


	printf("result = %g\n", stack_number[0]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	system("pause");
	return 0;
}
