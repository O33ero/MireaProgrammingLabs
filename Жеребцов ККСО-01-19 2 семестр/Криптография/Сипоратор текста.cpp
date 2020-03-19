#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <locale>
#include <fstream>
#include <algorithm>

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian"); // Кириллица
	setlocale(LC_CTYPE, "");

	ifstream ifile("5.txt");
	ofstream ofile("rusult.txt");

	set <char> alphabet = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' };
	/////////////////    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32

	char ch;
	while (!ifile.eof())
	{
		ifile >> ch;
		if (ch >= 'А' && ch <= 'Я')
			ch = ch - 'A' + 'a';
		if (alphabet.find(ch) != alphabet.end())
			ofile << ch;

	}
	ifile.close();
	ofile.close();
	return 0;
}
