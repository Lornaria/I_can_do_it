#include <iostream>
#include <fstream>
#include <string>

using std::cout; 
using std::cin;

void initArrExp2(int *arr, const size_t size) 
{
    arr[0] = 1;

    for (size_t i = 1; i < size; i++)
    {
        arr[i] = arr[i - 1] * 2;
    }
}

void printArrAndDelete(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << "[" << i << "]= " << arr[i] << std::endl;
    }
    delete[]arr;
    arr = nullptr;
}

void printArrAndDelete(int** arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            cout << "[" << i << "][" << j << "]= " << arr[i][j] << std::endl;
        }
        
    }
    for (size_t i = 0; i < size; i++)
    {
        delete[] arr[i];
    }
    delete[]arr;
    arr = nullptr;
}

void initArrRand(int** arr, const size_t size)
{
    srand(time(0));
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            arr[i][j] = rand() % 100;
        }
    }

}

void combineTwoFiles(const std::string fileName1, const std::string fileName2, const std::string foutName)
{
    std::ofstream fout(foutName);
    if (fout.is_open())
    {
        std::ifstream fin1(fileName1);
        if (fin1.is_open())
        {
            std::string buf;
            while (!fin1.eof())
            {
                getline(fin1, buf);
                fout << buf << std::endl;
            }
            fin1.close();
        }

        std::ifstream fin2(fileName2);
        if (fin2.is_open())
        {
            std::string buf;
            while (!fin2.eof())
            {
                getline(fin2, buf);
                fout << buf << std::endl;
            }
            fin2.close();
        }

        fout.close();
    }

}
std::string searchWord(const std::string fileName, const std::string word)
{
    std::ifstream fin(fileName);
    if (fin.is_open())
    {
        std::string buf;
        while (true) //по-хорошему стоило бы сделать проверку на достижение последней строки
        {
            while (!fin.eof())
            {
                getline(fin, buf);
                if (buf.find(word) != std::string::npos)
                {
                    fin.close();
                    return "Yes, your word is in this file";
                }
            }
            fin.close();
            return "No, there is no that word in this file";
        }
    }
}

int main()
{
    //Задание 6.1
    //Выделить в памяти динамический одномерный массив типа int.Размер массива запросить у пользователя.
    //Инициализировать его числами степенями двойки. Вывести массив на экран.Не забыть освободить память. Разбить программу на функции

    int* pMyArr1;
    int size;

    do //проверка ради тренировки на ввод положительного и не нулевого значения int
    {
        cout << "Enter the size of your array: ";
        cin >> size;
        if (cin.fail())
        {
            std::cerr << "Please enter a positive integer number!" << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } 
    while (size <= 0);

    pMyArr1 = new(std::nothrow) int[size];

    if (pMyArr1 == nullptr)
    {
        std::cerr << "Error: not enough memory";
    }
    else
    {
        initArrExp2(pMyArr1, size);
        printArrAndDelete(pMyArr1, size);
    }

    //Задание 6.2
    //Динамически выделить матрицу 4х4 типа int. Инициализировать ее псевдослучайными числами через
    //функцию rand.Вывести на экран.Разбейте вашу программу на функции которые вызываются из main

    cout << "\nTask 6.2\n";

    size_t const SIZE = 4;
    int** pMyArr2 = new int*[SIZE];
    for (size_t i = 0; i < SIZE; i++) 
    {
        pMyArr2[i] = new int[SIZE];
    }
    initArrRand(pMyArr2, SIZE);
    printArrAndDelete(pMyArr2, SIZE);

    //Задание 6.3
    //Написать программу, которая создаст два текстовых файла(*.txt), примерно по 50 - 100 символов в каждом
    //(особого значения не имеет с каким именно содержимым). Имена файлов запросить у пользователя.
    
    std::string fileName;
    cout << "Name of the first file to create: ";
    cin >> fileName;

    std::ofstream fout1(fileName + ".txt");
    if (fout1.is_open())
    {
        fout1 << "C makes it easy to shoot yourself in the foot;";
        fout1.close();
    }

    cout << "Name of the second file to create: ";
    cin >> fileName;
    std::ofstream fout2(fileName + ".txt");
    if (fout2.is_open())
    {
        fout2 << "C++ makes it harder, but when you do it blows your whole leg off.";
        fout2.close();
    }

    //Задание 6.4
    //Написать функцию, «склеивающую» эти файлы в третий текстовый файл(имя файлов спросить у пользователя).

    std::string fileName1, fileName2, foutName;
    cout << "Name of the first file to combine: ";
    cin >> fileName1;
    cout << "Name of the second file to combine: ";
    cin >> fileName2;
    cout << "Name of the output file: ";
    cin >> foutName;
    fileName1 += ".txt";
    fileName2 += ".txt";
    foutName += ".txt";

    combineTwoFiles(fileName1, fileName2, foutName);

    //Задание 6.5
    //Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в указанном пользователем файле(для простоты
    //работаем только с латиницей).Используем функцию find которая есть в строках std::string.

    std::string fileName5, word;
    cout << "Name of the file where we will search the word: ";
    cin >> fileName5;
    fileName5 += ".txt";
    cout << "The word to find: ";
    cin >> word;

    cout << searchWord(fileName5, word);

    return 0;
}