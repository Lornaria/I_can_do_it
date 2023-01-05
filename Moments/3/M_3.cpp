#include <iostream>
#include <list>
#include<vector>

using std::cout;
using std::endl;

//1. Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого равно среднему арифметическому всех его элементов.
void addAverage(std::list<double>& list) {
    double average = 0;
    for (auto it : list) {
        average += it;
    }
    average = average / list.size();
    list.push_back(average);
}

//2. Создать класс, представляющий матрицу.Реализовать в нем метод, вычисляющий определитель матрицы.Для реализации используйте контейнеры из STL.

class Matrix {
private:
    std::vector<std::vector<int>> matrix;
    int size;
    Matrix(int newSize, Matrix& bigM, int curColumn) {
        size = newSize;
        matrix.reserve(size);
        for (int i = 1; i <= size; i++) {
            matrix.push_back({});
            for (int j = 0; j <= size; j++) {
                if (j == curColumn) {
                    continue;
                }
                else {
                    matrix[i - 1].push_back(bigM.matrix[i][j]);
                }
            }
        }
    }
public:
    Matrix() : size(4) {
        matrix = std::vector<std::vector<int>>{ {1, 0, 2, -1}, {2, 0, -2, 1}, {3, 1, 3, 1}, {4, -1, 1, 2} };
    }
    Matrix(std::vector<std::vector<int>> _matrix) {
        matrix = _matrix;
        size = _matrix.size();
    }
    
    void printMatrix(){
        for (auto const& it : matrix) {
            for (auto const& it2 : it) {
                cout << it2 << " ";
            }
            cout << endl;
        } 
    }
    int determinant() {
        int result = 0;
        if (size == 1) {
            result = matrix[0][0];
            return result;
        }
        for (int i = 0; i < size; i++) {
            Matrix smal(size - 1, *this, i);
            int sign;
            if (i % 2 == 0) {
                sign = 1;
            }
            else {
                sign = -1;
            }
            result += matrix[0][i] * smal.determinant() * sign;
        }
        return result;
    }
};



int main()
{
    

}


