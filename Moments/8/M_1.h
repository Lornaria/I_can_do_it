#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <tuple>
#include<functional>
#include<optional>
#include<fstream>
#include<vector>
#include<sstream>
#include<cctype>
#include<algorithm>

using namespace std;

//Имеется база сотрудников и номеров их телефонов.
//Требуется написать соответствующие структуры для хранения данных, и заполнить контейнер записями из базы.
//Затем необходимо реализовать методы обработки данных, а также вывести на экран всю необходимую информацию.

//1. Создайте структуру Person с 3 полями: фамилия, имя, отчество.
//Поле отчество должно быть опционального типа, т.к.не у всех людей есть отчество.
//Перегрузите оператор вывода данных для этой структуры.
//Также перегрузите операторы < и == (используйте tie).

struct Person {
	string surname;
	string name;
	optional<string> patronymic;
};

ostream& operator<<(ostream& os, Person person) {
	os << person.surname << " " << person.name << " " << person.patronymic.value_or("") << " ";
	return os; 
}

bool operator<(Person person1, Person person2) {
	return tie(person1.surname, person1.name, person1.patronymic) < tie(person2.surname, person2.name, person2.patronymic);
}

bool operator==(Person person1, Person person2) {
	return tie(person1.surname, person1.name, person1.patronymic) == tie(person2.surname, person2.name, person2.patronymic);
}

//2. Создайте структуру PhoneNumber с 4 полями:
//· код страны(целое число)
//· код города(целое число)
//· номер(строка)
//· добавочный номер(целое число, опциональный тип)
//Для этой структуры перегрузите оператор вывода.
//Необходимо, чтобы номер телефона выводился в формате : +7(911)1234567 12, где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер.
//Если добавочного номера нет, то его выводить не надо.
//Также перегрузите операторы < и == (используйте tie)

struct PhoneNumber {
	int prefix = 0;
	int code = 0;
	string number;
	optional<int> addNum;
};

ostream& operator<<(ostream& os, PhoneNumber phoneNumber) {
	os << "+" << phoneNumber.prefix << "(" << phoneNumber.code << ")" << phoneNumber.number;
	if (phoneNumber.addNum.has_value()) {
		os << " " << phoneNumber.addNum.value();
	}
	return os;
}

bool operator<(PhoneNumber number1, PhoneNumber number2) {
	return tie(number1.prefix, number1.code, number1.number, number1.addNum) < tie(number2.prefix, number2.code, number2.number, number2.addNum);
}

bool operator==(PhoneNumber number1, PhoneNumber number2) {
	return tie(number1.prefix, number1.code, number1.number, number1.addNum) == tie(number2.prefix, number2.code, number2.number, number2.addNum);
}

//3. Создайте класс PhoneBook, который будет в контейнере хранить пары : Человек – Номер телефона.
//Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
//В теле конструктора происходит считывание данных из файла и заполнение контейнера.
//Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.

class PhoneBook
{
public:
	PhoneBook(ifstream& fin) {
		if (fin.is_open())
		{
			string str;
			int i = 0;
			while (!fin.eof())
			{
				book.push_back(pair<Person, PhoneNumber>());
				getline(fin, str);
				stringstream sStr(str);
				sStr >> book[i].first.surname >> book[i].first.name;
				sStr.ignore(1, ' ');
				unsigned char pk = static_cast<unsigned char>(sStr.peek());
				if (isalpha(pk)) {
					string help;
					sStr >> help;
					book[i].first.patronymic = help;
				}
				sStr >> book[i].second.prefix >> book[i].second.code >> book[i].second.number;
				int help = 0;
				if (sStr >> help) {
					book[i].second.addNum = help;
				}
				i++;
			}
			fin.close();
		}
		else
		{
			cout << "Error. Can not open file.";
		}
	};
	~PhoneBook() {};
	friend ostream& operator<<(ostream& os, PhoneBook& _book);
	void SortByName();
	void SortByPhone();
	tuple<string, PhoneNumber> GetPhoneNumber(const string& _surname);
	void ChangePhoneNumber(const Person& person, const PhoneNumber& newNum);
private:
	vector<pair<Person, PhoneNumber>> book;
};

ostream& operator<<(ostream& os, PhoneBook& _book) {
	for (auto const& [name, phone] : _book.book) {
		os << name << phone << endl;
	}
	return os;
}

//В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке.
//Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка производится по отчествам.
//Используйте алгоритмическую функцию sort.
void PhoneBook::SortByName() {
	sort(book.begin(), book.end(), [](pair<Person, PhoneNumber> person1, pair<Person, PhoneNumber> person2) { return person1.first < person2.first; });
}
//Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов.Используйте алгоритмическую функцию sort.
void PhoneBook::SortByPhone() {
	sort(book.begin(), book.end(), [](pair<Person, PhoneNumber> person1, pair<Person, PhoneNumber> person2) { return person1.second < person2.second; });
}
//Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber.
//Строка должна быть пустой, если найден ровно один человек с заданной фамилией в списке.
//Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», если было найдено больше одного человека, то в строке должно быть «found more than 1».
tuple<string, PhoneNumber> PhoneBook::GetPhoneNumber(const string& _surname) {
	int i = 0;
	PhoneNumber tempNum;
	for (auto const& [name, phone] : book) {
		if (name.surname == _surname) {
			tempNum = phone;
			i++;
		}
	}
	switch (i) {
	case 0:
		return tie("not found", tempNum);
	case 1:
		return tie("", tempNum);
	default:
		return tie("found more than 1", tempNum);
	}

}

//Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает.
void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& newNum) {
	for (auto& [_person, _phone] : book) {
		if (person == _person) {
			_phone = newNum;
		}
	}
}

