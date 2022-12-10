#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>

//1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
//• для удаления последнего элемента массива(аналог функции pop_back() в векторах)
//• для удаления первого элемента массива(аналог pop_front() в векторах)
//• для сортировки массива
//• для вывода на экран элементов.

class ArrayInt {
private:
	int m_length;
	int* m_data;
public:
	ArrayInt() : m_length(0), m_data(nullptr) {}
	ArrayInt(int length) : m_length(length) {
		assert(length >= 0);
		if (length > 0) {
			m_data = new int[length];
		}
		else {
			m_data = nullptr;
		}
	}
	~ArrayInt() {
		delete[] m_data;
		m_data = nullptr;
	}
	void erase() {
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	};
	int& operator[] (int index) {
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}
	void resize(int newLength) {

		if (newLength == m_length) {
			return;
		}
		if (newLength <= 0) {
			erase();
			return;
		}
		int* newData = new int[newLength];
		if (newLength > m_length) {
			for (size_t i = 0; i < m_length; i++)
			{
				newData[i] = m_data[i];
			}
		}
		else {
			for (size_t i = 0; i < newLength; i++)
			{
				newData[i] = m_data[i];
			}
		}
		delete[] m_data;
		m_data = newData;
		m_length = newLength;
	}
	void insertBefore(int value, int index)
	{
		assert(index >= 0 && index <= m_length);
		int* data = new int[m_length + 1];
		for (size_t before = 0; before < index; ++before) {
			data[before] = m_data[before];
		}
		data[index] = value;
		for (int after = index; after < m_length; ++after) {
			data[after + 1] = m_data[after];
		}
		delete[] m_data;
		m_data = data;
		++m_length;
	}
	void push_back(int value) { insertBefore(value, m_length); }
	int deleteIndex(int index) {
		assert(index >= 0 && index < m_length);
		int* data = new int[m_length - 1];
		for (int before = 0; before < index; ++before) {
			data[before] = m_data[before];
		}
		for (int after = index; after < m_length - 1; ++after) {
			data[after] = m_data[after + 1];
		}
		int dIndex = m_data[index];
		delete[] m_data;
		m_data = data;
		--m_length;
		return dIndex;
	}
	int pop_back() {
		return deleteIndex(m_length -1);
	}
	int pop_front() {
		return deleteIndex(0);
	}
	void print() {
		for (size_t i = 0; i < m_length; i++)
		{
			std::cout << m_data[i] << " ";
		}
		std::cout << std::endl;
	}
	void sort() {
		std::sort(m_data, m_data + m_length );
	}
};


//2. Дан вектор чисел, требуется выяснить, сколько среди них различных.
//Постараться использовать максимально быстрый алгоритм.

size_t countingV(std::vector<int> &vector) {
	std::set<int> s;
	for (int i : vector) {
		s.insert(i);
	}
	return s.size();
}


//3. Реализовать класс Hand, который представляет собой коллекцию карт.
//В классе будет одно поле : вектор указателей карт(удобно использовать вектор, т.к.это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).
//Также в классе Hand должно быть 3 метода :
//	• метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
//	• метод Clear, который очищает руку от карт
//	• метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).

enum Suit {
	spades,
	hearts,
	diamonds,
	clubs
};

enum Value {
	two = 2,
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
	king = 10,
	ace = 11
};

class Card {
private:
	Suit suit = spades;
	Value value = two;
	bool faceUp = false;
public:
	Card(Suit _suit, Value _value) : suit(_suit), value(_value) {}
	Card() {}
	void Flip() {
		faceUp = !faceUp;
	}
	Value GetValue() {
		return value;
	}
};

class Hand {
private:
	std::vector<Card*> hand;
public:
	Hand(){}
	~Hand(){}
	void Add(Card * newCard) {
		hand.push_back(newCard);
	}
	void Clear() {
		hand.clear();
	}
	int GetValue() {
		int sum = 0;
		std::vector<Card*>::const_iterator it = hand.begin();
		while (it != hand.end()) {
			sum += (*it)->GetValue();
			++it;
		}
		if (sum > 21) {
			it = hand.begin();
			int countAce = 0;
			while (it != hand.end()) { //подсчет всех тузов, после чего, если сумма больше 21, пересчет их значений на 1 вместо 11
				if ((*it)->GetValue() == ace) {
					countAce++;
				}
				++it;
			}
			while (sum > 21 || countAce > 0) {
				sum -= 10;
				countAce--;
			}
			return sum;
		}
		return sum;
	}
	
};

int main()
{
	/*std::vector<int> v = { 5, 5, 2, 3, 1, 2, 5 };
	std::cout << countingV(v);*/

	
	Card c1(spades, queen);
	Card c2(diamonds, two);
	Card c3(clubs, ace);
	Card c4(spades, ace);
	Hand ohMy;
	ohMy.Add(&c1);
	ohMy.Add(&c2);
	ohMy.Add(&c3);
	ohMy.Add(&c4);
	std::cout << ohMy.GetValue();
	return 0;
}
 