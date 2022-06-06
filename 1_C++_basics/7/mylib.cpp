#include <iostream>

namespace myNamespace {
    void initArr(float* arr, const size_t size)
    {
        srand(time(0));
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = rand() % 101 - 50;
        }
    }

    void printArr(const float* arr, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            std::cout << "[" << i << "]= " << arr[i] << std::endl;
        }
    }
    void countPosNegInArr(const float* arr, size_t size)
    {
        int pos = 0, neg = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] < 0)
            {
                neg++;
            }
            else
            {
                pos++;
            }
        }
        std::cout << "Amount of positive numbers: " << pos << std::endl;
        std::cout << "Amount of negative numbers: " << neg << std::endl;
    }
}