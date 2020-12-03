#include <iostream>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>
#include <string>

#define IMG "a.img"

using namespace std;


struct FileSystem
{
    // Файловые переменные
    string IMG_file;          // Имя файла
    ifstream file;            // Файловый указатель

    // FAT Данные
    uint16_t BytesPerSector;  // Байт в одном кластере
    uint8_t SectorPerCluster; // Секторов в одном кластере
    uint8_t CountFAT;         // Количество FAT-таблиц
    uint16_t SizeFATSectors;  // Размер одной FAT-таблицы
    uint16_t RootEntriesCount;// Число описателей в корневом каталоге
    uint32_t SectorDiskCount; // Число секторов на диске
    uint16_t RootDirSectors;  // Размер корневого каталога в секторах
    uint16_t DataSector;      // Размер области данных
    uint8_t SizeSystemSpace;  // Размер системной области
    

    // Тип системы
    string Type;


    // Адреса разделов диска. Нумерация от 0 до n;
    unsigned int AddressLoadingSecotor;
    unsigned int AddressRootDirectory;
    unsigned int AddressDataSpace;

};


uint8_t Scan_Byte (ifstream &file) // Достает байт из файла
{
    char byte;
    uint8_t value;

    file.get(byte);

    value = (uint8_t) byte;

    return (uint8_t) byte;
}

uint8_t Cyrcle_rotate(uint8_t value, int count) // Сдвиг байта вправо
{                                                    // 8-битовое число - value
    uint8_t temp;                                    // Кол-во сдигов   - count
    int rs;

    for (int i = 0; i < count; i++)
    {
        temp = value;
        rs = temp % 2;
        value = value / 2;                  // Сдвинули вправо;
        value = value + 128 * rs;   // Добавили 1 в начало, если остаток от деления на 2 был 1.
    }

    return value;
}

unsigned int intPow(unsigned int a, int b) // Возведение в степень
{                                          // Что возводим    - a
    unsigned int result = a;               // Во что возводим - b
    if (b == 0)
        return 1;
    else
        return a * intPow(a, (b-1));
}

uint32_t Table_With_Rotate (ifstream &file, int position, int count_byte) // Данные из hex-таблицы без переворота значений
{                                                                   // Поток файла                     - file
    uint8_t byte;                                                   // Сдвиг относительно начала файла - position
                                                                    // Число байт-значений             - count_byte
    file.seekg(position, ios::beg);

    uint32_t result = 0;

    for (int i = 0; i < count_byte; i++)
    {
        byte = Scan_Byte(file);
        result = result + byte * intPow(256, i);
    }

    return result;

}


void det_FileSystem(FileSystem &now)
{
    string file_path;
    // cout << "Insert the name of .img file:  ";
    // cin >> file_path;

    now.IMG_file = IMG; // Имя образа
    now.file.open(IMG); // Открытие образа

    ////////////////////////////////////

    now.SectorDiskCount = Table_With_Rotate(now.file, 19, 2);
    if (now.SectorDiskCount == 0)             // Если смещение 0х13 - пустое, то смотрим 0x20
    {
        now.SectorDiskCount = Table_With_Rotate(now.file, 32, 4);
    }

    now.SizeFATSectors = Table_With_Rotate(now.file, 22, 1);
    now.CountFAT = Table_With_Rotate(now.file, 16, 1);
    now.RootEntriesCount = Table_With_Rotate(now.file, 17, 2);
    now.BytesPerSector = Table_With_Rotate(now.file, 11, 2);
    now.SectorPerCluster = Table_With_Rotate(now.file, 13, 1);
    now.SizeSystemSpace = Table_With_Rotate(now.file, 14, 1);
    now.RootDirSectors = (now.RootEntriesCount * 32) / now.BytesPerSector;


    uint32_t c;
    c = now.SectorDiskCount - (now.SizeFATSectors * now.CountFAT + now.RootDirSectors + now.SizeSystemSpace);
    c = c / now.SectorPerCluster;
    if (c <= 4085)
        now.Type = "FAT12";
    else
        if (c <= 65525)
            now.Type = "FAT16";
        else
            now.Type = "FAT32";
     

    if (now.Type == "FAT12" || now.Type == "FAT16")
    {
        now.AddressLoadingSecotor = 0;                                             // Загрузочный = 0
        now.AddressRootDirectory = now.CountFAT * now.SizeFATSectors + now.SizeSystemSpace;          // Каталог = 5 * 2 + 1 = 11
        now.AddressDataSpace = now.AddressRootDirectory + now.RootDirSectors + now.SectorPerCluster;  // Данный = 11 + 14 + 2 = 27
    }

    
}

void print_Info(FileSystem &now) // Информация о системе
{
    cout << "Bytes per Secotr = "                     << now.BytesPerSector                   << "\n";
    cout << "Sectors per Cluster = "                  << (unsigned int) now.SectorPerCluster  << "\n";
    cout << "Count of FAT-table = "                   << (unsigned int) now.CountFAT          << "\n";
    cout << "Size of one FAT-table = "                << (unsigned int) now.SizeFATSectors    << " sectors\n";
    cout << "Count of Root Entries = "                << now.RootEntriesCount                 << "\n";
    cout << "Count of Sectors on Disk = "             << now.SectorDiskCount                  << "\n";
    cout << "Size of Root Directory = "               << now.RootDirSectors                   << " sectors\n";
    cout << "Type of File System = "                  << now.Type                             << "\n";
}

void print_Tree(ifstream &file) // Дерево системы
{
    char ch;

    while(!file.eof())
    {
        file.get(ch);
        cout << ch;
    }
}

int main()
{
    struct FileSystem now;
    det_FileSystem(now);

    print_Info(now);


    now.file.close();
    return 0;
}