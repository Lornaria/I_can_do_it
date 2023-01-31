#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using std::cout;
using std::endl;

//1.Создайте потокобезопасную оболочку для объекта cout.
//Назовите ее pcout.
//Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль.
//Продемонстрируйте работу pcout.

std::mutex m1;

class pcout : public std::stringstream {
public:
    pcout() {
        std::lock_guard<std::mutex> lck(m1);
    }
    ~pcout() {
        cout << this->str();
    }
};

void fPcout1() {
    for (size_t i = 0; i < 5; i++)
    {
        pcout{} << __FUNCTION__ << " " << "uses" << " pcout" << " class" << endl;
    }
}

void fPcout2() {
    for (size_t i = 0; i < 5; i++)
    {
        pcout{} << __FUNCTION__ << " " << "uses" << " pcout" << " class" << endl;
    }
}

//2.Реализовать функцию, возвращающую i - ое простое число (например, миллионное простое число равно 15485863).
//Вычисления реализовать во вторичном потоке.
//В консоли отображать прогресс вычисления(в основном потоке).

std::condition_variable condVar;
std::mutex m2;
uint16_t progress = 0;

size_t primeI(size_t i) {
    std::vector<size_t> v;
    v.reserve(i);
    v.push_back(2);
    size_t temp;
    size_t lim;
    float k = 100.0 / i; // coefficient
    bool primeNotFound = true;
    while (v.size() != i) {
        temp = v.back();
        primeNotFound = true;
        while (primeNotFound) {
            ++temp;
            lim = std::sqrt(temp) + 1;
            for (size_t i = 2; i <= lim; i++)
            {
                if (i == lim) {
                    primeNotFound = false;
                    break;
                }
                else if (temp % i == 0) {
                    break;
                }
            }
        }
        std::lock_guard<std::mutex> lk(m2);
        v.push_back(temp); 
        progress = std::ceil(v.size() * k);
        condVar.notify_all();
    }
    return v.back();
}

//3. Промоделировать следующую ситуацию.
//Есть два человека(2 потока) : хозяин и вор.
//Хозяин приносит домой вещи(функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду).
//При этом у каждой вещи есть своя ценность.
//Вор забирает вещи(функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), каждый раз забирает вещь с наибольшей ценностью.
std::vector<int> store;
std::mutex m3;
std::mt19937 rnd(23);
//mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> distrib(1, 100);

void man() {
    int treasure = 0;
    while (true) {
        treasure = distrib(rnd);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lk3(m3);
        store.push_back(treasure);
    }

}

void thief() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::lock_guard<std::mutex> lk3(m3);
        if (!store.empty()) {
            store.erase(std::max_element(store.begin(), store.end()));
        }
    }
    
    
}

int main()
{
    //Task 1.
    //std::thread t1(fPcout1);
    //std::thread t2(fPcout2);
    //t1.join();
    //t2.join();

    //Task 2.
    //size_t result=0;
    //size_t num;
    //cout << "Enter number for task 2: ";
    //std::cin >> num;
    //std::thread t([&result, num]() {result = primeI(num); });
    //while (true) {
    //    std::unique_lock lk(m2);
    //    condVar.wait(lk);
    //    cout << "\r" << progress;
    //    lk.unlock();
    //    if (progress >= 100) {
    //        break;
    //    }
    //} 
    //t.join();
    //cout << endl << result;
    
    //Task 3.
    //std::thread tMan(man);
    //std::thread tThief(thief);

    //tMan.join();
    //tThief.join();

}
