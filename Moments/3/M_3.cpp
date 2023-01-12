﻿#include <iostream>
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
        size = static_cast<int>(_matrix.size());
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

//3. Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for - range - based.

template<typename T>
class range_iterator : std::iterator<std::random_access_iterator_tag, typename T::value_type>
{
public:
    typedef T range_type;
    typedef range_iterator<range_type> self_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename range_type::value_type value_type;
    typedef typename range_type::size_type size_type;
    typedef typename range_type::difference_type difference_type;
    typedef typename range_type::pointer pointer;
    typedef typename range_type::const_pointer const_pointer;
    typedef typename range_type::reference reference;
    typedef typename range_type::const_reference const_reference;

    range_iterator(const range_type* const range, value_type start_value)
        : m_range(range), m_value(start_value)
    { }

    range_iterator(const self_type&) = default;
    range_iterator(self_type&&) = default;
    range_iterator& operator=(const range_iterator&) = default;
    ~range_iterator() = default;

    operator value_type() const {
        return m_value;
    }

    value_type& operator*() {
        return m_value;
    }

    self_type& operator++() {
        m_value += m_range->step();
        return *this;
    }

    self_type operator++(int) {
        self_type tmp(*this);
        ++(*this);
        return tmp;
    }

    self_type& operator--() {
        m_value -= m_range->step();
        return *this;
    }

    self_type operator--(int) {
        self_type tmp(*this);
        --(*this);
        return tmp;
    }

    self_type operator+(difference_type n) {
        self_type tmp(*this);
        tmp.m_value += m_range->step() * n;
        return tmp;
    }

    self_type& operator+=(difference_type n) {
        m_value += n * m_range->step();
        return (*this);
    }

    self_type operator-(difference_type n) {
        self_type tmp(*this);
        tmp.m_value -= n * m_range->step();
        return tmp;
    }

    self_type& operator-=(difference_type n) {
        m_value -= n * m_range->step();
        return (*this);
    }

    bool operator==(const self_type& other) const {
        return ((m_range == other.m_range) &&
            (equals<value_type>(m_value, other.m_value, m_range->step())));
    }

    bool operator!=(const self_type& other) const {
        return !((*this) == other);
    }

private:
    template<typename T> static bool equals(T a, T b, T e) {
        return a == b;
    }

    template<> static bool equals(double a, double b, double e) {
        return std::abs(a - b) < std::abs(e);
    }

    template<> static bool equals(float a, float b, float e) {
        return std::abs(a - b) < std::abs(e);
    }

    const range_type* const m_range;
    value_type m_value;
};

template<typename T>
class range sealed
{
    static_assert(std::is_arithmetic<T>::value, "Template type should be a integral-type");

public:
    typedef T          value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef range<value_type>               self_type;
    typedef class range_iterator<self_type> iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;

    range(value_type _min, value_type _max, value_type _step = value_type(1))
        : m_min(_min), m_max(_max), m_step(_step) {
        if (m_step == 0) {
            throw std::invalid_argument("Step equals zero");
        }
    }

    range(const self_type&) = default;
    range(self_type&&) = default;
    range& operator=(const self_type&) = default;
    ~range() = default;

    bool operator==(const self_type& _obj) const {
        return (m_max == _obj.max()) &&
            (m_min == _obj.min()) &&
            (m_step == _obj.step());
    }

    bool operator!=(const self_type& _obj) const {
        return !(this == _obj);
    }

    value_type operator[](size_type _index) const {
#ifdef _DEBUG
        if (_index > size()) {
            throw std::out_of_range("Index out-of-range");
        }
#endif
        return (m_min + (_index * m_step));
    }

    bool empty() const {
        bool is_empty = ((m_max < m_min) && (m_step > 0));
        is_empty |= ((m_max > m_min) && (m_step < 0));
        return is_empty;
    }

    size_type size() const {
        if (empty()) {
            return 0;
        }
        return static_cast<size_type>((m_max - m_min) / m_step);
    }

    value_type min() const {
        return m_min;
    }

    value_type max() const {
        return m_max;
    }

    value_type step() const {
        return m_step;
    }

    iterator begin() const {
        iterator start_iterator(this, m_min);
        return start_iterator;
    }

    iterator end() const {
        iterator end_iterator(this, m_min + size() * m_step);
        return end_iterator;
    }

    reverse_iterator rbegin() const {
        reverse_iterator start_iterator(end());
        return start_iterator;
    }

    reverse_iterator rend() const {
        reverse_iterator end_iterator(begin());
        return end_iterator;
    }

private:

    value_type m_min;
    value_type m_max;
    value_type m_step;
};

int main()
{
    /*Matrix m1;
    m1.printMatrix();
    cout << m1.determinant() << endl;
    Matrix m2({ {1, 0, 5, -1, 6}, {2, 6, -6, 1, 0}, {3, 6, 3, 1, 8}, {4, 6, 1, 2, -7}, {5, 3, 7, 8, -2} });
    m2.printMatrix();
    cout << m2.determinant() << endl;*/

    std::cout << '[';
    for (int i : range<int>(0, 10))
        std::cout << i << ' ';
    std::cout << ']' << std::endl;

    std::cout << '[';
    for (int i : range<int>(0, 10, 2))
        std::cout << i << ' ';
    std::cout << ']' << std::endl;

    std::cout << '[';
    for (int i : range<int>(10, 2))
        std::cout << i << ' ';
    std::cout << ']' << std::endl;

    std::cout << '[';
    for (int i : range<int>(10, 2, -1))
        std::cout << i << ' ';
    std::cout << ']' << std::endl;

}

