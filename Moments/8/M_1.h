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

//������� ���� ����������� � ������� �� ���������.
//��������� �������� ��������������� ��������� ��� �������� ������, � ��������� ��������� �������� �� ����.
//����� ���������� ����������� ������ ��������� ������, � ����� ������� �� ����� ��� ����������� ����������.

//1. �������� ��������� Person � 3 ������: �������, ���, ��������.
//���� �������� ������ ���� ������������� ����, �.�.�� � ���� ����� ���� ��������.
//����������� �������� ������ ������ ��� ���� ���������.
//����� ����������� ��������� < � == (����������� tie).

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

//2. �������� ��������� PhoneNumber � 4 ������:
//� ��� ������(����� �����)
//� ��� ������(����� �����)
//� �����(������)
//� ���������� �����(����� �����, ������������ ���)
//��� ���� ��������� ����������� �������� ������.
//����������, ����� ����� �������� ��������� � ������� : +7(911)1234567 12, ��� 7 � ��� ����� ������, 911 � ����� ������, 1234567 � �����, 12 � ���������� �����.
//���� ����������� ������ ���, �� ��� �������� �� ����.
//����� ����������� ��������� < � == (����������� tie)

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

//3. �������� ����� PhoneBook, ������� ����� � ���������� ������� ���� : ������� � ����� ��������.
//����������� ����� ������ ������ ��������� �������� ���� ifstream � ����� ������, ���������� �� �����.
//� ���� ������������ ���������� ���������� ������ �� ����� � ���������� ����������.
//����� PhoneBook ������ ��������� ������������� �������� ������, ��� ������ ���� ������ �� ���������� � �������.

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

//� ������ PhoneBook ���������� ����� SortByName, ������� ������ ����������� �������� ���������� �� ������� ����� � ���������� �������.
//���� ������� ����� �����������, �� ���������� ������ ����������� �� ������, ���� ����� ����� ���������, �� ���������� ������������ �� ���������.
//����������� ��������������� ������� sort.
void PhoneBook::SortByName() {
	sort(book.begin(), book.end(), [](pair<Person, PhoneNumber> person1, pair<Person, PhoneNumber> person2) { return person1.first < person2.first; });
}
//���������� ����� SortByPhone, ������� ������ ����������� �������� ���������� �� ������� ���������.����������� ��������������� ������� sort.
void PhoneBook::SortByPhone() {
	sort(book.begin(), book.end(), [](pair<Person, PhoneNumber> person1, pair<Person, PhoneNumber> person2) { return person1.second < person2.second; });
}
//���������� ����� GetPhoneNumber, ������� ��������� ������� ��������, � ���������� ������ �� ������ � PhoneNumber.
//������ ������ ���� ������, ���� ������ ����� ���� ������� � �������� �������� � ������.
//���� �� ������ �� ���� ������� � �������� ��������, �� � ������ ������ ���� ������ �not found�, ���� ���� ������� ������ ������ ��������, �� � ������ ������ ���� �found more than 1�.
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

//���������� ����� ChangePhoneNumber, ������� ��������� �������� � ����� ����� �������� �, ���� ������� ��������� �������� � ����������, �� ������ ��� ����� �������� �� �����, ����� ������ �� ������.
void PhoneBook::ChangePhoneNumber(const Person& person, const PhoneNumber& newNum) {
	for (auto& [_person, _phone] : book) {
		if (person == _person) {
			_phone = newNum;
		}
	}
}

