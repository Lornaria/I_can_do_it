#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstdio>

class Power {
private:

    double base = 1.0;
    double exponent = 1.0;

public:
    void set(double _base, double _exp){

        base = _base;
        exponent = _exp;
    }
    double calculate() {
        return std::pow(base, exponent);
    }
};

class RGBA {
private:
    std::uint8_t m_blue = 0;
    std::uint8_t m_red = 0;
    std::uint8_t m_green = 0;
    std::uint8_t m_alpha = 255;
public:
    RGBA() = default;
    RGBA(uint8_t blue, uint8_t red, uint8_t green, uint8_t alpha) {
        m_blue = blue;
        m_red = red;
        m_green = green;
        m_alpha = alpha;
    }
    
    void print() {
        printf("%u %u %u %u\n", m_blue, m_red, m_green, m_alpha);
    }
};

class Stack {
private:
    int array[10] = { 0 };
    int length = -1;
public:
    void reset() {
        for (int i = 0; i < 10; ++i) {
            array[i] = 0;
        }
        length = -1;
    }
    bool push(int num) {
        if (length < 9) {
            array[++length] = num;
            return true;
        }
        else {
            std::cout << "Stack is full!" << std::endl;
            return false;
        }
        
    }
    int pop() {
        if (length >= 0) {
            return array[length--];

        }
        else {
            std::cout << "Stack is empty!" << std::endl;
            return NULL;
        }
    }
    void print() {
        if (length == -1) {
            std::cout << "()" << std::endl;
        }
        else {
            std::cout << "(";
            for (int i = 0; i <= length; ++i) {
                std::cout << array[i] << " ";
            }
            std::cout << "\b)" << std::endl;
        }   
    }
};

int main()
{
    Power myNum;
    myNum.set(2, 10);
    std::cout << myNum.calculate() << std::endl;

    RGBA color(2, 3, 4, 50);
    color.print();
     
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

}
