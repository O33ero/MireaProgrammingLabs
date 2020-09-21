#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int main()
{
	FILE* f;
	f = fopen("/dev/input/event2", "r");

	struct input_event k;

	unsigned long int first_time;
	int first_code = 0;

	unsigned long int last_time;
	int last_code = 0;

	unsigned long int count = 0;

	while(1)
	{	
		fread(&k, sizeof(k), 1, f);
		fread(&k, sizeof(k), 1, f);

		if (k.value == 0 || k.value == 1)
			continue;
		
//		printf("%d \n", k.value);

		if (first_code == 0)
		{
			first_code = k.value;
			first_time = k.time.tv_sec;
		}

		last_code = k.value;
		last_time = k.time.tv_sec;

		count += 1;
		
//		printf("%ld \n\n", last_time);
		printf("\n***\n c = %ld, t = %ld \n***\n", count,last_time-first_time ); 
		

		float t = (float)(last_time - first_time);
		float c = (float)count;

		printf("\n***\n Action per second = %f \n***\n", c/t );

	}

	fclose(f);
	return 0;
}
