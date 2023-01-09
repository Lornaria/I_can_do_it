#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

//1. Имеется отсортированный массив целых чисел.
//Необходимо разработать функцию insert_sorted, которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
//Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.

void insert_sorted(vector<int>& vec, int num) {
    vector<int>::iterator it = std::lower_bound(vec.begin(), vec.end(), num);
    vec.insert(it, num);
}

template<typename T1, typename T2>
void insert_sorted(T1& cont, T2 num) {
    std::fill_n(std::inserter(cont, std::lower_bound(cont.begin(), cont.end(), num)), 1, num);
    //std::inserter(cont, std::lower_bound(cont.begin(), cont.end(), num));
}

//2. Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения аналогового сигнала.
//На основе этого массива чисел создайте другой вектор целых чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
//Выведите получившиеся массивы чисел.Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле

void Task2() {
    srand(static_cast <unsigned> (time(0)));

    vector<float> v1(100);
    vector<int> v2;
    v2.reserve(100);

    std::generate(v1.begin(), v1.end(), []() {return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0));});
    cout << "analogue: ";
    copy(v1.begin(), v1.end(), std::ostream_iterator<float>{cout, ", "});

    std::transform(v1.begin(), v1.end(), std::back_inserter(v2), [](float num) { return static_cast<int>(num); });
    cout << endl << "digital: ";
    copy(v2.begin(), v2.end(), std::ostream_iterator<int>{cout, ", "});

    cout << endl << "Error: " << std::accumulate(begin(v1), end(v1), static_cast<float>(0.0), [](float x, float y) {return x + std::pow((y - static_cast<int>(y)), 2); }) << endl;
}


int main()
{

}

