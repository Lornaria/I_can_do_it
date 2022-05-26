#include <iostream>
#include <clocale>
using std::cout;
using std::cin;

int main()
{
    setlocale(LC_ALL, "Russian");
    //Задание 4.1
    //Написать программу, проверяющую что сумма двух (введенных с клавиатуры) чисел лежит в пределах от 10 до 20 
    //(включительно), если да – вывести строку "true", в противном случае – "false";

    cout << "Задание 4.1\n";

    int a1, b1;
    cout << "Enter first number:";
    cin >> a1;
    cout << "Enter second number:";
    cin >> b1;

    if (10 <= a1 + b1 && a1 + b1 <= 20)
    {
        cout << "true\n";

    }
    else 
    {
        cout << "false\n";
    }

    //Задание 4.2
    //Написать программу, выводящую на экран строку “true”, если две целочисленные константы, объявленные в её начале либо
    //обе равны десяти сами по себе, либо их сумма равна десяти. Иначе "false".

    cout << "\nЗадание 4.2\n";


    const int a2 = 5;
    const int b2 = 5;

    if ((a2 == 10 && b2 == 10) || (a2 + b2 == 10)) 
    {
        cout << "true\n";
    }
    else
    {
        cout << "false\n";
    }

    //Задание 4.3 
    //Написать программу которая выводит на экран список всех нечетных чисел он 1 до 50. Например: "Your numbers: 1 3 5 7 9 
    //11 13 ...". Для решения используйте любой С++ цикл.

    cout << "\nЗадание 4.3\n";

    cout << "Your uneven numbers from 1 to 50:\n";
    for (size_t i = 0; i <= 50; i++)
    {
        if (i % 2 != 0) 
        {
            cout << i << " ";
        }
    }

    //Задание 4.4
    //Написать программу, проверяющую,является ли некоторое число - простым.Простое число — это
    //целое положительное число, которое делится без остатка только на единицу и себя само.
    cout << "\n\nЗадание 4.4\n";

    float num;
    cout << "Let's check if your number is a prime: ";
    cin >> num;


    if(num <= 1 || static_cast<int>(num) != num)
    {
        cout << "Not a prime\n";
    }
    else 
    {
        for (size_t i = 2; i <= num; i++)
        {
            if (i == static_cast<int>(num))
            {
                cout << "It's a prime!!!\n";
                break;
            }
            else if (static_cast<int>(num) % i == 0)
            {
                cout << "Not a prime\n";
                break;
            }
        }
    }
    
    //Задание 4.5
    //Пользователь вводит с клавиатуры число (год) : от 1 до 3000. Написать программу, которая определяет является ли этот год високосным.
    cout << "\nЗадание 4.5\n";

    
    cout << "Now let's check if the year is a leap year: ";
    uint16_t year;
    cin >> year;

    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
    {
        cout << "It's a leap year!";
    }
    else
    {
        cout << "Nah, just some ordinary year...";
    }
    
    return 0;
}
