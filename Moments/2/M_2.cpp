#include <iostream>
#include<memory>
#include <vector>
#include<algorithm>
#include<string_view>
#include<fstream>
#include"Timer.h"
#include<string>

using std::cout;
using std::endl;

//1. Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, на которые указывают эти указатели
//(нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).

template<typename T>
void Swap(T& left, T& right) {
	T tempT = std::move(left);
	left = std::move(right);
	right = std::move(tempT);
}

//2. Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.
template<typename T>
void SortPointers(std::vector<T>& vec) {
	std::sort(vec.begin(), vec.end(), [](T& ptr1, T& ptr2) { return *ptr1 < *ptr2; });
}

//3. Подсчитайте количество гласных букв в книге “Война и мир”.Для подсчета используйте 4 способа:
//○ count_if и find
//○ count_if и цикл for
//○ цикл for и find
//○ 2 цикла for
//Замерьте время каждого способа подсчета и сделайте выводы.
//Справка:
//count_if - это алгоритмическая функция из STL, которая принимает 3 параметра : итератор на начало, итератор на конец и унарный предикат(функцию, принимающую один параметр и возвращающую тип bool).
//find - это метод класса string, который возвращает позицию символа(строки), переданного в качестве параметра, в исходной строке.Если символ не найден, то метод возвращает string::npos.

void count_if_find(const std::string& s) {
	Timer timer("count_if_find");
	std::string_view sv = s;
	std::string vowels = "EAOUIeaoui";
	size_t counter = std::count_if(sv.begin(), sv.end(), [&vowels](const char& c) { return vowels.find(c) != std::string::npos; });
	cout << "Vowels: " << counter << endl;
	timer.print();

}

void count_if_for(const std::string& s) {
	Timer timer("count_if_for");
	std::string_view sv = s;
	std::string vowels = "EAOUIeaoui";
	size_t counter = std::count_if(sv.begin(), sv.end(), [&vowels](const char& c)
																		{	for (const auto& symbol : vowels) {
																				if (c == symbol) { return true; }
																			}
																			return false; 
																		});
	cout << "Vowels: " << counter << endl;
	timer.print();
}

void for_find(const std::string& s) {
	Timer timer("for_find");
	std::string_view sv = s;
	std::string vowels = "EAOUIeaoui";
	size_t counter = 0;
	for (const auto& c : s) {
		if (vowels.find(c) != std::string::npos) {
			counter++;
		}
	}
	cout << "Vowels: " << counter << endl;
	timer.print();
}

void for_for(const std::string& s) {
	Timer timer("for_for");
	std::string_view sv = s;
	std::string vowels = "EAOUIeaoui";
	size_t counter = 0;
	for (const auto& c : s) {
		for (const auto& vowel : vowels) {
			if (c == vowel) {
				counter++;
				break;
			}
		}
	}
	cout << "Vowels: " << counter << endl;
	timer.print();
}
//самым медленным  методом подсчета оказался count_if_for, а самым быстрым for_find.

int main()
{
	std::srand(std::time(0));

	std::ifstream fin("War-and-Peace.txt");
	if (fin.is_open()){
		fin.seekg(0, std::ios::end);
		size_t size = fin.tellg();
		fin.seekg(0);
		std::string s(size, ' ');
		fin.read(&s[0], size);
		fin.close();
		std::string vowels = "EAOUIeaoui";

		count_if_find(s);
		cout << endl;

		count_if_for(s);
		cout << endl;

		for_find(s);
		cout << endl;

		for_for(s);
	}
	else
	{ 
		cout << "Error. Can not open file.";
	}

	
	return 0;
}

