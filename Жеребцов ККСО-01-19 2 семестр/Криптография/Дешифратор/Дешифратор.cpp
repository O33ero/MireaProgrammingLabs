#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


int main()
{


	setlocale(LC_ALL, "Russian"); // Кириллица
	setlocale(LC_CTYPE, "");

	ifstream data_file("data.csv");   // csv файл с разделителем ';'
	ifstream cry_file("3.txt");       // зашифрованный текст в кодировке ANSI
	ofstream decry_file("result.txt");// расшифрованный текст
	if (!cry_file)
	{
		cout << "Файл не открыт\n\n";
	    return -1;
	}
	if (!data_file)
	{
		cout << "Файл не открыт\n\n";
	    return -1;
	}



	char alphabet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' };
	/////////////////    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
	
	
	
	vector <pair <char,char>> letter;
	pair <char, char> temp;

	char ch;
	string str;


	for(int i = 0; i<33; i++)
	{


		/*
		Структура csv файла:
		
		Первым записывается символ, который надо заменить.
		Вторым записывается символ, на который надо заменить.
		
		*/

		if (!data_file.eof())
		{
							   //    из   -->    в
			data_file >> str;  // 'символ' ; 'символ' \n
							   //     0    1     2     3
		}

		temp.first = str[0];
		temp.second = str[2];

		letter.push_back(temp);

		cout << letter[i].first << " --> " << letter[i].second << endl;
	}

	


	while (cry_file.get(ch))
	{
		bool is_found = false;
		for (int i = 0; i < 33; i++)
		{
			if (ch == letter[i].first)
			{
				is_found = true;
				decry_file << letter[i].second;
				break;
			}
		}


		if (!is_found)
		{
			decry_file << ch;
		}
	}
	
	


   

	data_file.close();
	decry_file.close();
	cry_file.close();
	return 0;
}
