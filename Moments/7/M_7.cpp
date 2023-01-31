#include <iostream>
#include <fstream>
#include "students.pb.h"
#include <algorithm>
#include <tuple>
#include <sstream>
#pragma comment(linker, "/alternatename:__imp___std_init_once_complete=__imp_InitOnceComplete")
#pragma comment(linker, "/alternatename:__imp___std_init_once_begin_initialize=__imp_InitOnceBeginInitialize")

using namespace std;

//1. Установить библиотеку protobuf.
//2. С помощью компилятора protobuf в отдельном пространстве имен сгенерировать классы
//a.FullName с полями имя, фамилия, отчество(отчество опционально).
//b.Student с полями полное имя, массив оценок, средний балл.
//c.StudentsGroup с полем массив студентов.
//3. Создать класс StudentsGroup, который реализует интерфейсы :

class IRepository {
	virtual void Open() = 0; // бинарная десериализация в файл
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
	virtual float GetAverageScore(const Task2::Student::FullName& name) = 0;
	virtual string GetAllInfo(const Task2::Student::FullName& name) = 0;
	virtual string GetAllInfo() = 0;
};

class StudentsGroup : public IRepository, public IMethods {
public:
	void Open() {
		ifstream in("students.bin", ios_base::binary);
		group.ParseFromIstream(&in);
	}
	void Save() {
		ofstream out("students.bin", ios_base::binary);
		group.SerializeToOstream(&out);
	}
	float GetAverageScore(const Task2::Student::FullName& name) {
		auto prd = [&name](const Task2::Student stud)
		{	if (stud.fullname().name() == name.name()) {
				if (stud.fullname().surname() == name.surname()) {
					if (name.has_patronymic() && (stud.fullname().patronymic() == name.patronymic())) {
						return true;
					}
					else if (!name.has_patronymic()) {
						return true;
					}
				}
			}
			return false;
		};
		auto it = find_if(group.students().begin(), group.students().end(), prd);
		return it->averagegrade();
	}
	string GetAllInfo(const Task2::Student::FullName& name) {
		stringstream ss;
		auto prd = [&name](const Task2::Student stud)
		{	if (stud.fullname().name() == name.name()) {
			if (stud.fullname().surname() == name.surname()) {
				if (name.has_patronymic() && (stud.fullname().patronymic() == name.patronymic())) {
					return true;
				}
				else if (!name.has_patronymic()) {
					return true;
				}
			}
		}
		return false;
		};
		auto it = find_if(group.students().begin(), group.students().end(), prd);
		ss << "Name: " << it->fullname().name() << " " << it->fullname().surname();
		if (it->fullname().has_patronymic()) {
			ss << " " << it->fullname().patronymic();
		}
		ss << endl;
		ss << "Grades: ";
		for (auto grade : it->grades()) {
			ss << grade << " ";
		}
		ss << endl;
		ss << "Average of grades: " << it->averagegrade();
		return ss.str();
	}
	string GetAllInfo() {
		stringstream ss;
		for (auto student : group.students()) {
			ss << GetAllInfo(student.fullname());
		}
		return ss.str();
	}
private:
	Task2::StudentsGroup group;
};

int main()
{
	return 0;
}
