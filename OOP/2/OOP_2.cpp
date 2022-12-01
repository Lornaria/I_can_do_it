#include <iostream>
//Создать класс Person (человек) с полями: имя, возраст, пол и вес. 
//Определить методы переназначения имени, изменения возраста и веса. 
//Создать производный класс Student (студент), имеющий поле года обучения. 
//Определить методы переназначения и увеличения этого значения. 
//Создать счетчик количества созданных студентов. 
//В функции main() создать несколько (не больше трёх) студентов. 
//Вывести информацию о них.

class Person {
public:
	Person(std::string _name, int _age, char _sex, float _weight) {
		name = _name;
		age = _age;
		sex = _sex;
		weight = _weight;
	}
	Person() = default;

	void print() {
		std::cout << "name: " << name << "\n" << "age: " << age << "\n" << "sex: " << sex << "\n" << "weight: " << weight << std::endl;
	}
	void setName(std::string _name) {
		name = _name;
	}
	void setAge(int _age) {
		age = _age;
	}
	void setWeight(float _weight) {
		weight = _weight;
	}

private:
	std::string name = "None";
	int age = NULL;
	char sex = ' ';
	float weight = NULL;
};

class Student : public Person {
public:
	Student(std::string _name, int _age, char _sex, float _weight, int _year) : Person(_name, _age, _sex, _weight) {
		year = _year;
		amountOfStudents++;
	}
	Student() { amountOfStudents++; };
	
	void setYear(int _year) {
		year = _year;
	}
	void increaseYear() {
		year++;
	}
	void print() {
		Person::print();
		std::cout << "year: " << year << std::endl << std::endl;
	}
	friend void showAmountOfStudents();
private:
	int year = 0;
	static int amountOfStudents;
};

int Student::amountOfStudents = 0;
void showAmountOfStudents() {
	std::cout << "Amount of students created: " << Student::amountOfStudents << std::endl;
}

int main()
{

	Student Tommy("Tommy", 33, 'M', 81.3, 1);
	Student Masha("Masha", 28, 'F', 65, 2);

	Tommy.print();
	Masha.print();

	showAmountOfStudents();

	return 0;
}

