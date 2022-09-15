#Задание 1.1 Напишите программу, которая принимает на вход два числа и проверяет, является ли одно число квадратом другого.
print('Enter first number:')
a = int(input())
print('Enter second number:')
b = int(input())

if a == b ** 2 or b == a ** 2:
    print('Yes')
else:
    print('No')