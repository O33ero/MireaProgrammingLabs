#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

bool cmp(pair <char, int> a, pair <char, int> b)
{
    return a.second > b.second;
}

int main()
{
    

    setlocale(LC_ALL, "Russian"); // Кириллица
    setlocale(LC_CTYPE, "");


    ifstream file("3.txt");
    ofstream ofile("result.csv");
    ofile << "Символ" << ';' << "Количество" << ';' << "Процент" << ';' << ';' << "Символ" << ';' << "Количество" << ';' << "Процент" << endl;
    if (!file)
    {
        cout << "Файл не открыт\n\n";
        return -1;
    }




  
    char alphabet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я'};
                   //    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33
    


    vector <pair <char, int>> letter;
    
    for (int i = 0; i < 33; i++)
    {
        pair <char, int> temp = { alphabet[i], 0 };
        letter.push_back(temp);
    }
   


    long int sum = 0;
    bool is_found = false;
    char ch;
    

    while (file.get(ch))
    {
        sum += 1;

        for (int i = 0; i < 33; i++)
        {
            bool is_found = false;
            if (letter[i].first == ch)
            {
                is_found = true;
                letter[i].second += 1;
                break;
            }
        }
        

        
    }
    
    for (int i = 0; i < 33; i++)
    {
        cout << letter[i].first << " " << letter[i].second << " " << (double)letter[i].second / (double)sum * 100 << endl;
        ofile << letter[i].first << ";" << letter[i].second << ";" << (double)letter[i].second / (double)sum * 100 << endl;
    }

    ofile << endl;

    sort(letter.begin(), letter.end(), cmp);

    for (int i = 0; i < 33; i++)
    {
        ofile << letter[i].first << ";" << letter[i].second << ";" << (double)letter[i].second / (double)sum * 100 << endl;
    }

    ofile.close();
    file.close();
    return 0;
}
