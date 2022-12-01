//2.Создать классы Apple(яблоко) и Banana(банан), которые наследуют класс Fruit(фрукт).
//У Fruit есть две переменные - члена: name(имя) и color(цвет).
//Добавить новый класс GrannySmith, который наследует класс Apple.

//3. Должен быть класс, представляющий колоду, а так же базовый класс участника от которого будут производные классы дилер и игрок. Класс суммы денег игрока и производный от него класс ставки. 

#include <iostream>

class Fruit {
public:
    std::string getName() {
        return name;
    }
    std::string getColor() {
        return color;
    }
protected:
    std::string name = "fruit";
    std::string color = "fruity";
};

class Apple : public Fruit {
public:
    Apple() {
        name = "apple";
    }
    Apple(std::string _color) {
        name = "apple";
        color = _color;
    }
};

class Banana : public Fruit{
public:
    Banana() {
        name = "banana";
        color = "yellow";
    }
};

class GrannySmith : public Apple {
public:
    GrannySmith() { 
        name = "Granny Smith apple"; 
        color = "green";
    }
};

int main()
{
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}

