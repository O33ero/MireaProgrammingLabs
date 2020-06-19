// 21:25

#include <iostream>
#include <vector>


using namespace std;

struct clock
{
	int day;
	int minute;
	int full;
};

clock check(clock temp, clock main_clock, clock next_clock)
{
	if (next_clock.day == 0)
		next_clock = temp;
	else
	{
		if (temp.day == 0)
			return next_clock;

		if ((temp.full - main_clock.full) > 0) // temp находится правее
		{
			if ((next_clock.full - main_clock.full) < 0)
				next_clock = temp;
			else
			{
				if (temp.full - next_clock.full < 0)
					next_clock = temp;
			}
		}
		else // temp находится левее
		{
			if (temp.full - next_clock.full < 0)
				next_clock = temp;
		}
	}

	return next_clock;
}





int main()
{
	//INSERT
	clock main_clock;
	int n;
	int a,b,c;

	cin >> a >> b >> c;
	main_clock.day = a;
	main_clock.minute = b * 60 + c;
	main_clock.full = a * 24 * 60 + main_clock.minute;

	cin >> n;

	vector <clock> alarm_clock(n);

	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> c;

		alarm_clock[i].day = a;
		alarm_clock[i].minute = b * 60 + c;
		alarm_clock[i].full = a * 24 * 60 + alarm_clock[i].minute;

		if (alarm_clock[i].day == 0)
		{
			if (alarm_clock[i].minute >= main_clock.minute)
				alarm_clock[i].full = main_clock.day * 24 * 60 + alarm_clock[i].minute;
			else
			{
				if (main_clock.day + 1 == 8)
					alarm_clock[i].full = 1 * 24 * 60 + alarm_clock[i].minute;
				else
					alarm_clock[i].full = (main_clock.day + 1) * 24 * 60 + alarm_clock[i].minute;
			}
		}
	}

	//PROCCES
	clock next_clock;
	clock temp;

	

	next_clock.day = 0;
	next_clock.minute = 0;
	next_clock.full = 0;


	// Проверка на дебила, то что будильник стоит на время, которое сейчас на часах

	for (auto now_clock : alarm_clock)
	{
		if (now_clock.full == main_clock.full)
		{
			next_clock = main_clock;
			cout << next_clock.day << " " << next_clock.minute / 60 << " " << next_clock.minute % 60;
			return 0;
		}
	}



	temp.day = 0;
	temp.minute = 0;
	temp.full = 0;
	for (auto now_clock : alarm_clock) // Проверяем будильники по дням ближайшим к сегодняшенму справа
	{
		if (now_clock.day != 0)
		{
			if ( ((now_clock.full - main_clock.full) > 0) && (( (temp.full == 0) || (now_clock.full - temp.full) < 0) ) ) 
			{
				temp = now_clock;
			}
		}
	}

	next_clock = check(temp, main_clock, next_clock);
	







	if (next_clock.day == 0)
	{
		temp.day = 0;
		temp.minute = 0;
		temp.full = 0;
		for (auto now_clock : alarm_clock) // Проверяем будильники по дням ближайшим к сегодняшенму слева
		{


			if (now_clock.day != 0)
			{
				if (((now_clock.full - main_clock.full) < 0) && (((temp.full == 0) || (temp.full - now_clock.full) < 0)))
				{
					temp = now_clock;
				}
			}
		}

		next_clock = check(temp, main_clock, next_clock);
	}






	

	temp.day = 0;
	temp.minute = 0;
	temp.full = 0;
	for (auto now_clock : alarm_clock) // Проверяем ежедневные будильники
	{
		if (now_clock.day == 0)
		{
			if ( (abs(now_clock.full - main_clock.full) < abs(temp.full - main_clock.full) ) || (temp.full == 0))
			{
				temp.day = (now_clock.full - now_clock.minute) / (24 * 60);
				temp.minute = now_clock.minute;
				temp.full = now_clock.full;
			}
		}
	}

	next_clock = check(temp, main_clock, next_clock);



	




	//OUT

	cout << next_clock.day << " " << next_clock.minute / 60 << " " << next_clock.minute % 60;
	return 0;
}

// 0:00