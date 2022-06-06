#include <iostream>
#include "mylib.h"
#include <fstream>
#define CHECKINRANGE(numToCheck, border) \
        if(numToCheck >= 0 && numToCheck <= border) {std::cout << "true\n";} \
        else {std::cout << "false\n";}
#define DEFINESIZE 5
#define SwapINT(a, b) \
        if (a > b) { \
        int c = a;\
        a = b;\
        b = c;\
        }
#pragma pack(push, 1)
struct Employee
{
    int id;
    char section;
    double salary;
    bool hasChildren;
};
#pragma pack(pop)

void sortBubble(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            SwapINT(arr[j], arr[j+1])
        }
    }
}

int main()
{
    //Задание 7.1 7.5
    //Создайте проект из 2х cpp файлов и заголовочного (main.cpp, mylib.cpp, mylib.h) во втором модуле mylib объявить 3 функции:
    //для инициализации массива(типа float), печати его на экран и подсчета количества отрицательных и положительных
    //элементов.Вызывайте эти 3 - и функции из main для работы с массивом.
    const size_t SIZE = 5;
    float* pMyarr1 = new float[SIZE];
    myNamespace::initArr(pMyarr1, SIZE);
    myNamespace::printArr(pMyarr1, SIZE);
    myNamespace::countPosNegInArr(pMyarr1, SIZE);
    delete[] pMyarr1;
    pMyarr1 = nullptr;

    //Задание 7.2
    //Описать макрокоманду(через директиву define), проверяющую, входит ли переданное ей число(введенное с
    //клавиатуры) в диапазон от нуля(включительно) до переданного ей второго аргумента(исключительно) и возвращает true или
    //false, вывести на экран «true» или «false»

    int num2, border;
    std::cout << "Enter your number to check: ";
    std::cin >> num2;
    std::cout << "Enter border: ";
    std::cin >> border;
    CHECKINRANGE(num2, border);

    //Задание 7.3
    //Задайте массив типа int.Пусть его размер задается через директиву препроцессора #define.Инициализируйте его через
    //ввод с клавиатуры.Напишите для него свою функцию сортировки(например Пузырьком).Реализуйте перестановку
    //элементов как макрокоманду SwapINT(a, b).Вызывайте ее из цикла сортировки.

    int myArr[DEFINESIZE];
    int numArr;
    for (size_t i = 0; i < DEFINESIZE; i++)
    {
        std::cout << "[" << i << "]= ";
        std::cin >> numArr;
        myArr[i] = numArr;
    }
    sortBubble(myArr, DEFINESIZE);
    //for (int i = 0; i < DEFINESIZE; i++)
    //{
    //    std::cout << myArr[i] << std::endl;
    //}

    //Задание 7.4
    //Объявить структуру Сотрудник с различными полями. Сделайте для нее побайтовое выравнивание с помощью
    //директивы pragma pack.Выделите динамически переменную этого типа.Инициализируйте ее.Выведите ее на экран и ее
    //размер с помощью sizeof.Сохраните эту структуру в текстовый файл.

    Employee* pJohn = new Employee;
    pJohn->hasChildren = false;
    pJohn->id = 12345;
    pJohn->salary = 2000.00;
    pJohn->section = 'S';

    std::cout << "John has children: " << std::boolalpha << pJohn->hasChildren << std::noboolalpha << std::endl;
    printf("John's id: %d\nJohn's salary: %.2lf\nJohn's section: %c\n", pJohn->id, pJohn->salary, pJohn->section);

    std::cout << "size of *pJohn: " << sizeof(*pJohn) << std::endl;

    std::ofstream fout("John.txt");
    if (fout.is_open())
    {
        fout << "John has children : " << std::boolalpha << pJohn->hasChildren << std::noboolalpha << std::endl;
        fout << "John's id: " << pJohn->id << std::endl;
        fout << "John's salary: " << pJohn->salary << std::endl;
        fout << "John's section: " << pJohn->section << std::endl;
       
        fout.close();
    }
    delete pJohn;

}

