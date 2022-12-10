#include <iostream>
#include <string>
#include "blackjack.h"

//1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
template<typename T> class Pair1 {
private:
	T m_first;
	T m_second;
public:
	Pair1(T _first, T _second){
		m_first = _first;
		m_second = _second;
	}
	Pair1(){}
	T first() const {
		return m_first;
	}
	T second() const {
		return m_second;
	}

};

//2. Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.

template<typename T1, typename T2> class Pair {
private:
	T1 m_first;
	T2 m_second;
public:
	Pair(T1 _first, T2 _second) {
		m_first = _first;
		m_second = _second;
	}
	Pair() {}
	T1 first() const {
		return m_first;
	}
	T2 second() const {
		return m_second;
	}
};

//3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа.
//Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, а второй — любого типа данных.

template<typename T2> class Pair <std::string, T2> {
private:
	std::string m_first;
	T2 m_second;
public:
	Pair(std::string _first, T2 _second) {
		m_first = _first;
		m_second = _second;
	}
	Pair() {}
	virtual ~Pair(){}
	std::string first() const {
		return m_first;
	}
	T2 second() const {
		return m_second;
	}
};

template<typename T2> class StringValuePair : public Pair<std::string, T2> {
public:
	StringValuePair(std::string _first, T2 _second) : Pair<std::string, T2>(_first, _second) {}
};

//4. Создать класс GenericPlayer, в который добавить поле name - имя игрока.
//Также добавить 3 метода:
//• IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
//• IsBoosted() - возвращает bool значение, есть ли у игрока перебор
//• Bust() - выводит на экран имя игрока и объявляет, что у него перебор.

class GenericPlayer : public Hand {
private:
	std::string name = "None";
public:
	GenericPlayer(std::string _name) : name(_name) {}
	GenericPlayer(){}
	virtual bool IsHitting() = 0;
	bool IsBoosted() {
		if (GetValue() > 21) {
			return true;
		}
		return false;
	}
	void Bust() {
		std::cout << name << " busted!\n";
	}
};

int main()
{
	/*Pair1<int> p1(6, 9);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';*/

	/*Pair<int, double> p1(6, 7.8);
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2(3.4, 5);
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';*/

	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

	return 0;
}