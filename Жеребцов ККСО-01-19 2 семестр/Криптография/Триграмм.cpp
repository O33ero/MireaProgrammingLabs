#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    

    setlocale(LC_ALL, "Russian"); // Кириллица
    setlocale(LC_CTYPE, "");


    ifstream file("1.txt");
    ofstream ofile("resultTrigrammSanya.csv");
    ofile << "Пара" << ';' << "Количество" << ';' << "Процент" << endl;
    if (!file)
    {
        cout << "Файл не открыт\n\n";
        return -1;
    }




  
    char alphabet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я'};
                   //    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33
    
    long int sum = 0;
    string buffstr = "aaа";
    char buff[3];


    file.get(buff[0]);
    file.get(buff[1]);
    set <string> letters_set;
    map <string, int> letters_count;
    while (file.get(buff[2]))
    {
        buffstr[0] = buff[0];
        buffstr[1] = buff[1];
        buffstr[2] = buff[2];

        if (letters_set.find(buffstr) == letters_set.end()) 
        { // Не найден
            letters_count[buffstr] = 1;
            letters_set.insert(buffstr);
        }
        else 
        { // Найден
            letters_count[buffstr] += 1;
        }

        sum += 1;

        buff[0] = buff[1];
        buff[1] = buff[2];
    }

    for (auto now : letters_count)
    {
        if (now.second > 15)
            ofile << now.first << ";" << now.second << ";" << (double)now.second / (double)sum * 100 << endl;
    }

    ofile << "Всего" << ";" << sum << endl;
    ofile.close();
    file.close();
    return 0;
}
