#include <iostream>
using std::cout;

void PrintArr(double *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

void PrintArr(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

void SwapArr(int arr[], size_t size)
{
    cout << "\nYour array before: ";

    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nYour array after: ";

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == 0)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = 0;
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << std::endl;
}

void InitMyArr3(int arr[], size_t size) 
{
    arr[0] = 1;

    for (size_t i = 1; i < size; i++)
    {
        arr[i] = arr[i - 1] + 3;
    }

    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}


void CircleArr(int* arr, const int size, int n)
{
    int *tempArr = new int[size];

    n = n % size; //убираем полные циклы

    if (n >= 0) //если сдвиг вправо или сдвига нет
    {
        for (size_t i = 0; i < size; i++)
        {
            if (i < n)
            {
                tempArr[i] = arr[size - n + i];
            }
            else
            {
                tempArr[i] = arr[i - n];
            }

        }
    }

    if (n < 0) //если сдвиг влево
    {
        for (size_t i = 0; i < size; i++)
        {
            if (i < (size + n))
            {
                tempArr[i] = arr[i - n];
            }
            else
            {
                tempArr[i] = arr[-(size + n) + i ];
            }

        }
    }

    for (int i = 0; i < size; i++) //записываем изменения в оригинальный массив
    {
        arr[i] = tempArr[i];
    }

}

bool CheckBalance(int *arr, size_t size) 
{
    int leftSum = 0, rightSum = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j <= i; j++) //проходим по левой части и суммируем
        {
            leftSum += arr[j];
        }

        for (size_t j = i + 1; j < size; j++) //проходим по правой части и суммируем
        {
            rightSum += arr[j];
        }
        
        if(leftSum == rightSum)
        {
            return true;
        }
        leftSum = 0;
        rightSum = 0;
    }
    return false;
}

int main()
{
    const size_t SIZE = 8;

    //Задание 5.1
    //Написать функцию которая выводит массив double чисел на экран.Параметры функции это сам массив и его размер. Вызвать эту функцию из main

    double myArr[SIZE] = { 10.00, 2.00 };
    PrintArr(myArr, SIZE);

    //Задание 5.2
    //Задать целочисленный массив, состоящий из элементов 0 и 1. Например: [1, 1, 0, 0, 1, 0, 1, 1, 0, 0] .Написать функцию, заменяющую в принятом массиве 0 на 1, 1 на 0. 
    //Выводить на экран массив до изменений и после

    int myArr2[SIZE] = { 1, 1, 1, 0, 0 };
    SwapArr(myArr2, SIZE);

    //Задание 5.3
    //Задать пустой целочисленный массив размером 8. Написать функцию, которая с помощью цикла заполнит его значениями 1 4 7 10 13 16 19 22. Вывести массив на экран.

    int myArr3[SIZE];
    InitMyArr3(myArr3, SIZE);

    //Задание 5.4
    //Написать функцию, которой на вход подаётся одномерный массив и число n(может быть положительным 
    //или отрицательным), при этом метод должен циклически сместить все элементы массива на n позиций.

    int myArr4[SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7};
    cout << "\n\nTask 5.4 \n";
    CircleArr(myArr4, SIZE, 10);
    PrintArr(myArr4, SIZE);

    //Задание 5.5
    //Написать функцию, которой передается не пустой одномерный целочисленный массив, она должна вернуть
    //истину если в массиве есть место, в котором сумма левой и правой части массива равны.

    cout << "\n\nTask 5.5 \n";
    int myArr5[SIZE] = { 1, 1, 0, 0, 0, 1, 0, 3};
    cout << CheckBalance(myArr5, SIZE);

    return 0;
}