
#include <stdio.h>
#include <time.h>

int main() {

	srand(time(NULL));                 // �����������
	int n, x, i, j, temp, error = 0;   /* n     - ������ �������
										* x     - ������� �����
										* i,j   - ���������� ��� ����� for
										* temp  - ��������� ����������
										* error - ������ � ������ ����� x � ������� */
	scanf("%d %d", &n, &x);
	int arr[2 * n];                    // ������ ������� - 2 * n

	printf("Original array:\n");
	for (i = 0; i < 2 * n; i++)        // ���������� �������
	{
		arr[i] = rand() % (2 * n);     // ��������� ������ ���������� ������� � ��������� [0;2n)     

		temp = arr[i];
		printf("%d ", temp);
	}
	printf("\n\n");



	
	for (i = 0; i < 2 * n; i++)			///////////////////////////////////
	{
		for (j = 0; j < 2 * n - 1; j++)
		{
			if (arr[j + 1] < arr[j])
			{							// ���������� �������� ////////////
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}									///////////////////////////////////

	
	
	
	printf("Sorted array:\n");
	for (i = 0; i < 2 * n; i++)         // ����� �������������� ������� 
	{
		temp = arr[i];
		printf("%d ", temp);
	}
	printf("\n\n");
	
	
	//////////////// �������� ����� ////////////////
	int left_l = 0, right_l = 2 * n, pos_x, middle = n;
										/* left_l  - ����� ������ ��������������� ����� �������
										 * right_l - ������ ������ ��������������� ����� �������
										 * pos_x   - ������� x � ������������� �������
										 * middle  - �������� � �������� ��������������� ����� ������� */
	while (1)  
	{
		if (right_l - left_l <= 1)      // �� ����� ����� x � ������� 
		{	
			error++;
			printf("Error. Cannot find %d.\n", x);
			break;
		}
		if (arr[middle] == x)			// ����� x � �������
		{
			pos_x = middle;
			break;
		}

		if (arr[middle] > x)            // x ��������� ����� ������ �������
		{
			right_l = middle;
			middle = (left_l + right_l) / 2;
		}
		else                            // x ��������� ������ ������ �������
		{
			left_l = middle;
			middle = (left_l + right_l) / 2;
		}
	}
	/////////////////////////////////////////////////
	
	
	left_l = pos_x;                     // ����� ������ ��������� x � �������
	right_l = pos_x;					// ������ ������ ��������� x � �������
	while (!error)
	{
		if (left_l > 0)
		{
			if (arr[left_l - 1] == x)   // ����� ������� ����� x
			{
				left_l = left_l - 1;
			}
			else                        // ����� ������ ��� �������� ������ x
			{
				break;
			}
		}
		else                            // ������ ������� ������� ����� x
		{
			break;
		}
	}

	while (!error)
	{
		if (right_l < 2* n - 1)       
		{
			if (arr[right_l + 1] == x)  // ������ ������� ����� x
			{
				right_l = right_l + 1;
			}
			else                        // ����� ������ ��� �������� ������ x
			{
				break;
			}
		}
		else                            // ��������� ������� ����� x
		{
			break;
		}
	}
	
	
	
	
	if (!error)
	{
		if (left_l == right_l)          // ������ ���� ������� x � �������
		{
			printf("Position: %d\n\n", left_l);
		}
		else                            // �������� x � ������� [left_l; right_l] 
		{
			printf("Range: %d to %d\n\n", left_l + 1, right_l + 1);
		}
	}





	return 0;
}
