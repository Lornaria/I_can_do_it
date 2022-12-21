#include<iostream>
#include<exception>
#include<string>

//1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero, если второй параметр равен 0. 
//В функции main выводить результат вызова функции div в консоль, а также ловить исключения.

template<typename T>
T Div(T a, T b) {
    if (b == 0) {
        throw "Division by zero";
    }
    return a / b;
    }

//2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра.
//Написать класс Bar, хранящий вещественное число y(конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a.
//Если y + a > 100, возбуждается исключение типа Ex с данными a* y, иначе в y заносится значение a.
//В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n.
//Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0.
//В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.

class Ex {
public:
    Ex(float _x) : x(_x) {}
    Ex(){}
    float x = 0;
};

class Bar {
private:
    float y;
public:
    Bar() { y = 0; }
    void set(float a) {
        if ((y + a) > 100) {
            throw Ex(a * y);
        }
        y = a;
    }
};

//3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, означающий задание переместиться на соседнюю позицию.
//Эти методы должны запускать классы - исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда(направление не находится в нужном диапазоне).
//Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.
//Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех возникающих ошибках.

enum direction {
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};

std::ostream& operator<<(std::ostream& os, direction& dir) {
    switch (dir) {
    case 0:
        os << "N";
        break;
    case 1:
        os << "NE";
        break;
    case 2:
        os << "E";
        break;
    case 3:
        os << "SE";
    case 4:
        os << "S";
        break;
    case 5:
        os << "SW";
        break;
    case 6:
        os << "W";
        break;
    case 7:
        os << "NW";
        break;
    }
    return os;
}


class BaseRobot {
public:
    virtual int getX() = 0;
    virtual int getY() = 0;
};

class IllegalCommand {
private:
    std::string error;
public:
    IllegalCommand(std::string _error) : error(_error) {}
    const char* getError() {
        return error.c_str();
    }
};

class OffTheField {
private:
    direction dir;
    int x = 0;
    int y = 0;
public:
    OffTheField(int& _x, int& _y, direction& _dir) : x(_x), y(_y), dir(_dir) {}
    void getError() {
        std::cerr << "Error: Off the field!" << std::endl;
        std::cerr << "You were on position x: " << x << " y: " << y << " and tried to go " << dir << "! Please try again!" << std::endl;
    }
};

class Robot : public BaseRobot{
private:
    int x = 0;
    int y = 0;
public:
    Robot() {}
    void move(direction _dir) {
        int tempX = x;
        int tempY = y;
        switch (_dir) {
        case N:
            y++;
            break;
        case NE:
            x++;
            y++;
            break;
        case E:
            x++;
            break;
        case SE:
            x++;
            y--;
            break;
        case S:
            y--;
            break;
        case SW:
            x--;
            y--;
            break;
        case W:
            x--;
            break;
        case NW:
            x--;
            y++;
            break;
        }
        if (x < 0 || y < 0 || x > 9 || y > 9) {
            x = tempX;
            y = tempY;
            throw OffTheField(x, y, _dir);
        }
    }
    void print() {
        std::cout << "x: " << x << " y: " << y << std::endl;
    }
    int getX() { return x; }
    int getY() { return y; }
};

std::istream& operator>>(std::istream& is, direction& dir) {
    std::string text;
    if (is >> text) {
        if (text == "N") {
            dir = N;
        }
        else if (text == "NE") {
            dir = NE;
        }
        else if (text == "E") {
            dir = E;
        }
        else if (text == "SE") {
            dir = SE;
        }
        else if (text == "S") {
            dir = S;
        }
        else if (text == "SW") {
            dir = SW;
        }
        else if (text == "W") {
            dir = W;
        }
        else if (text == "NW") {
            dir = NW;
        }
        else {
            throw IllegalCommand("Illegal Command! Use one of the following notations: N, NE, E, SE, S, SW, W, NW");
        }
    }
    return is;
}


void clearScr()
{
    system("cls");
}

int main()
{
    //1.
    /*try {
        std::cout << Div(10, 0) << std::endl;
    }
    catch (const char* ex) {
        std::cerr << "Error: " << ex << std::endl;
    }*/

    //2.
    /*Bar bar;
    int n = 0;
    while(true) {
        try {
            std::cout << "n= ";
            std::cin >> n;
            if (n == 0) {
                break;
            }
            bar.set(n);
        }
        catch (Ex& ex) {
            std::cout << "Error: ex= " << ex.x << std::endl;
        }
    }*/


    //3.

    Robot myRobot;
    direction newdir;

    while (true) {
        try {
            std::cout << "Your current coordinates: ";
            myRobot.print();
            std::cout << "Your next direction: ";
            std::cin >> newdir;
            myRobot.move(newdir);
            clearScr();
        }
        catch (IllegalCommand& ex) {
            std::cerr << ex.getError() << std::endl;
        }
        catch (OffTheField& ex) {
            ex.getError();
        }
    }
    
    return 0;
}
