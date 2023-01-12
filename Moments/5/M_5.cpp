#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <list>
#include <sstream>

using std::cout;
using std::endl;

//1. Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов(если слово повторяется больше 1 раза, то вывести его надо один раз).
//Продемонстрировать работу функции, передав итераторы различных типов.

template <typename T>
void unicWords(T _begin, T _end) {
    std::unordered_set<std::string> mySet;
    copy(_begin, _end, inserter(mySet, mySet.end()));
    copy(mySet.begin(), mySet.end(), std::ostream_iterator<std::string>(cout, " "));
}

//2. Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем из стандартного потока ввода и разбивать их на предложения.
//Далее программа должна вывести пользователю все предложения, а также количество слов в них, отсортировав предложения по количеству слов.
 
int main()
{
    //1.
    std::vector<std::string> v{ "wo", "wo", "rd", "word", "rd", "word", "hehe" };
    copy(v.begin(), v.end(), std::ostream_iterator<std::string>(cout, " "));
    cout << endl;
    unicWords(v.begin(), v.end());
    std::list<std::string> l{ "wo", "wo", "rd", "word", "rd", "word", "hehe" };
    cout << endl;
    unicWords(l.begin(), l.end());

}
