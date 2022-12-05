//1. Создать абстрактный класс Figure(фигура).
//Его наследниками являются классы Parallelogram(параллелограмм) и Circle(круг).
//Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).
//Для всех классов создать конструкторы.
//Для класса Figure добавить чисто виртуальную функцию area() (площадь).
//Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.

#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>
#include <string>


class Figure {
public:
    Figure(){}
    virtual float area() = 0;
};

class Parallelogram : public Figure {
public:
    Parallelogram(float _b, float _h) : b(_b), h(_h) {}
    Parallelogram() = default;
    float area() override {
        return b * h;
    }
protected:
    float b = 0;
    float h = 0;
};

class Circle : public Figure {
public:
    Circle(float _radius) : radius(_radius){}
    Circle() = default;
    float area() override {
        return std::numbers::pi_v<float> * powf(radius, 2);
    }
private:
    float radius = 1;
};

class Rectangle : public Parallelogram {
public:
    Rectangle(float _a, float _b) : Parallelogram(_a, _b){}
    Rectangle() = default;
    float area() override  {
        return Parallelogram::area();
    }
};

class Square : public Parallelogram {
public:
    Square(float _a) : Parallelogram(_a, _a){}
    Square() = default;
    float area() override {
        return Parallelogram::area();
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(float _b, float _h) : Parallelogram(_b, _h) {}
    Rhombus() = default;
    float area() override {
        return Parallelogram::area();
    }
};
    
//2. Создать класс Car(автомобиль) с полями company(компания) и model(модель).
//Классы - наследники: PassengerCar(легковой автомобиль) и Bus(автобус).
//От этих классов наследует класс Minivan(минивэн).
//Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
//Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы.
//Обратить внимание на проблему «алмаз смерти».

class Car {
protected:
    std::string company = "None";
    std::string model = "None";
public:
    Car(std::string _company, std::string _model) : company(_company), model(_model) { std::cout << __FUNCTION__ << std::endl; }
    Car(){ std::cout << __FUNCTION__ << std::endl; }
    virtual ~Car(){ std::cout << __FUNCTION__ << std::endl; }
};

class PassangerCar : virtual public Car {
public:
    PassangerCar(std::string _company, std::string _model) : Car(_company, _model) { std::cout << __FUNCTION__ << std::endl; }
    PassangerCar(){ std::cout << __FUNCTION__ << std::endl; }
    ~PassangerCar(){ std::cout << __FUNCTION__ << std::endl; }
};

class Bus : virtual public Car {
public:
    Bus(std::string _company, std::string _model) : Car(_company, _model) {}
    Bus(){ std::cout << __FUNCTION__ << std::endl; }
    ~Bus(){ std::cout << __FUNCTION__ << std::endl; }
};

class Minivan : public PassangerCar, public Bus {
public:
    Minivan(std::string _company, std::string _model) : Car(_company, _model) {}
    Minivan(){ std::cout << __FUNCTION__ << std::endl; }
    ~Minivan(){ std::cout << __FUNCTION__ << std::endl; }
};

//3. Создать класс : Fraction(дробь).Дробь имеет числитель и знаменатель(например, 3 / 7 или 9 / 2).Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить :
//    математические бинарные операторы(+, -, *, / ) для выполнения действий с дробями
//    унарный оператор(-)
//    логические операторы сравнения двух дробей(== , != , <, >, <= , >= ).
//    Примечание : Поскольку операторы < и >= , > и <= — это логические противоположности, попробуйте перегрузить один через другой.
//    Продемонстрировать использование перегруженных операторов.


//Знак учитывается при числителе. Считаем, что подается на ввод только положительный знаменатель.
class Fraction {
private:
    int numerator = 1;
    int denominator = 1;
public:
    Fraction(int _numerator, int _denominator){
        numerator = _numerator;
        if (_denominator == 0) {
            std::cout << "Denominator can't be zero! You can change it with methode set." << std::endl;
            denominator = 1;
        }
        else {
            denominator = _denominator;
        }
    }
    Fraction() = default;
    void set(int _numerator, int _denominator) {
        numerator = _numerator;
        if (_denominator == 0) {
            std::cout << "Denominator can't be zero! Set up default value 1" << std::endl;
            denominator = 1;
        }
        else {
            denominator = _denominator;
        }
    }
    int getNumerator() { return numerator; }
    int getDenominator() { return denominator; }
    void print() {
        std::cout << numerator << "/" << denominator;
    }
    std::string getPrint() {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
    Fraction operator- () const {
        return Fraction(numerator * -1, denominator);
    }
    friend Fraction operator+ (const Fraction& first, const Fraction& second);
    friend Fraction operator- (const Fraction& first, const Fraction& second);
    friend Fraction operator* (const Fraction& first, const Fraction& second);
    friend Fraction operator/ (const Fraction& first, const Fraction& second);
    friend bool operator== (const Fraction& first, const Fraction& second);
    friend bool operator!= (const Fraction& first, const Fraction& second);
    friend bool operator< (const Fraction& first, const Fraction& second);
    friend bool operator> (const Fraction& first, const Fraction& second);
    friend bool operator>= (const Fraction& first, const Fraction& second);
    friend bool operator<= (const Fraction& first, const Fraction& second);
};

Fraction operator+ (const Fraction &first, const Fraction &second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    int result = (first.numerator * (lcm / first.denominator)) + (second.numerator * (lcm / second.denominator));
    return Fraction(result, lcm);
}
Fraction operator- (const Fraction& first, const Fraction& second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    int result = (first.numerator * (lcm / first.denominator)) - (second.numerator * (lcm / second.denominator));
    return Fraction(result, lcm);
}
Fraction operator* (const Fraction& first, const Fraction& second) {
    int newNum = first.numerator * second.numerator;
    int newDen = first.denominator * second.denominator;
    return Fraction(newNum, newDen);
}
Fraction operator/ (const Fraction& first, const Fraction& second) {
    if (second.numerator == 0) {
        std::cout << "Division by zero!" << std::endl;
        return Fraction(1, 1);
    }
    int newNum = first.numerator * second.denominator;
    int newDen = first.denominator * second.numerator;
    if (second.numerator < 0) {
        newNum *= -1;
        newDen *= -1;
    }
    return Fraction(newNum, newDen);
}
bool operator== (const Fraction& first, const Fraction& second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    if ((first.numerator * (lcm / first.denominator)) == (second.numerator * (lcm / second.denominator))) {
        return true;
    }
    else {
        return false;
    }
}
bool operator!= (const Fraction& first, const Fraction& second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    if ((first.numerator * (lcm / first.denominator)) != (second.numerator * (lcm / second.denominator))) {
        return true;
    }
    else {
        return false;
    }
}
bool operator< (const Fraction& first, const Fraction& second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    if ((first.numerator * (lcm / first.denominator)) < (second.numerator * (lcm / second.denominator))) {
        return true;
    }
    else {
        return false;
    }
}
bool operator> (const Fraction& first, const Fraction& second) {
    int lcm = std::lcm(first.denominator, second.denominator);
    if ((first.numerator * (lcm / first.denominator)) > (second.numerator * (lcm / second.denominator))) {
        return true;
    }
    else {
        return false;
    }
}
bool operator>= (const Fraction& first, const Fraction& second) {
    if (first < second) {
        return false;
    }
    else {
        return true;
    }
}
bool operator<= (const Fraction& first, const Fraction& second) {
    if (first > second) {
        return false;
    }
    else {
        return true;
    }
}


//4. Создать класс Card, описывающий карту в игре БлэкДжек.
//У этого класса должно быть три поля : масть, значение карты и положение карты(вверх лицом или рубашкой).
//Сделать поля масть и значение карты типом перечисления(enum).
//Положение карты - тип bool.Также в этом классе должно быть два метода :
//метод Flip(), который переворачивает карту, т.е.если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
//метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.

enum Suit {
    spades,
    hearts,
    diamonds,
    clubs
};

enum Value {
    ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack = 10,
    queen = 10,
    king = 10
};

class Card {
private:
    Suit suit = spades;
    Value value = two;
    bool faceUp = false;
public:
    Card(){}
    void Flip() {
        faceUp = !faceUp;
    }
    Value GetValue() {
        return value;
    }
};

int main()
{   
    //Car car;
    //PassangerCar passangerCar;
    //Bus bus;
    //Minivan minivan;

    Fraction firstNum(-3, 5);
    Fraction secNum(2, 15);
    Fraction thNum(-2, 5);
    std::cout << firstNum.getPrint() + " + " + secNum.getPrint() + " = " + (firstNum + secNum).getPrint() << std::endl;
    std::cout << firstNum.getPrint() + " - " + secNum.getPrint() + " = " + (firstNum - secNum).getPrint() << std::endl;
    std::cout << firstNum.getPrint() + " * " + secNum.getPrint() + " = " + (firstNum * secNum).getPrint() << std::endl;
    std::cout << firstNum.getPrint() + " / " + thNum.getPrint() + " = " + (firstNum / thNum).getPrint() << std::endl;
    std::cout << "-(" + firstNum.getPrint() + ") = " << (-firstNum).getPrint() << std::endl;
    std::cout << std::boolalpha << firstNum.getPrint() + " == " + secNum.getPrint() + " " << (firstNum == secNum) << std::noboolalpha << std::endl;
    std::cout << std::boolalpha << firstNum.getPrint() + " != " + secNum.getPrint() + " " << (firstNum != secNum) << std::noboolalpha << std::endl;
    std::cout << std::boolalpha << firstNum.getPrint() + " <= " + secNum.getPrint() + " " << (firstNum <= secNum) << std::noboolalpha << std::endl;
    std::cout << std::boolalpha << firstNum.getPrint() + " > " + secNum.getPrint() + " " << (firstNum > secNum) << std::noboolalpha << std::endl;

    return 0;
}

