#include <iostream>
#include<memory>
#include "blackjack.h"
#include<algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <strstream>

//1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.
//Перегрузите оператор вывода для данного класса.
//Создайте два "умных" указателя today и date.
//Первому присвойте значение сегодняшней даты.
//Для него вызовите по отдельности методы доступа к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.
//Затем переместите ресурс, которым владеет указатель today в указатель date.
//Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.

class Date {
private:
    int day = 1;
    int month = 1;
    int year = 1;
public:
    Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {}
    Date(){}
    ~Date(){}
    void set(int _day, int _month, int _year) {
        day = _day;
        month = _month;
        year = _year;
    }
    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }
    int getYear() const {
        return year;
    }
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.getDay() << "." << date.getMonth() << "." << date.getYear() << std::endl;
    return os;
}


//2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
//• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой(сравнение происходит по датам).Функция должна вернуть более позднюю дату.
//• Создайте функцию, которая обменивает ресурсами(датами) два умных указателя, переданных в функцию в качестве параметров.
//Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.

Date& compareDates(const std::unique_ptr<Date>& date1, const std::unique_ptr<Date>& date2) {
    if (date1->getYear() > date2->getYear()) {
        return *date1;
    }
    else if (date1->getYear() < date2->getYear()) {
        return *date2;
    }
    else {
        if (date1->getMonth() > date2->getMonth()) {
            return *date1;
        }
        else if (date1->getMonth() < date2->getMonth()) {
            return *date2;
        }
        else {
            if (date1->getDay() > date2->getDay()) {
                return *date1;
            }
            else if (date1->getDay() < date2->getDay()) {
                return *date2;
            }
            else {
                return *date1;
            }
        }
    }
}

void swapDates(std::unique_ptr<Date>& date1, std::unique_ptr<Date>& date2) {
    date1.swap(date2);
}


//3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт.Класс Deck имеет 4 метода:
//• vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
//• void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
//• vold Deal(Hand& aHand) - метод, который раздает в руку одну карту
//• void AddltionalCards(GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать


class Deck : public Hand
{
public:
    Deck(){
        hand.reserve(52);
        Populate();
    };
    virtual ~Deck(){};
    
    void Populate() {
        Clear();
        for (int s = Suit::spades; s <= Suit::clubs; ++s)
        {
            for (int v = Value::two; v <= Value::king; ++v)
            {
                Add(new Card(static_cast<Suit>(s),
                    static_cast<Value>(v)));
            }
        }
    }
    
    void Shuffle() {
        std::random_shuffle(hand.begin(), hand.end());
    }
    
    void Deal(Hand& aHand) {
        if (!hand.empty())
        {
            aHand.Add(hand.back());
            hand.pop_back();
        }
        else
        {
            std::cout << "Out of cards. Unable to deal.";
        }
    }
    
    void AdditionalCards(GenericPlayer& aGenericPlayer) {
        std::cout << std::endl;
        // продолжает раздавать карты до тех пор, пока у игрока не случается
        // перебор или пока он хочет взять еще одну карту
        while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            std::cout << aGenericPlayer << std::endl;
            if (aGenericPlayer.IsBusted())
            {
                aGenericPlayer.Bust();
            }
        }
    }
};

//4. Реализовать класс Game, который представляет собой основной процесс игры.У этого класса будет 3 поля:
//• колода карт
//• рука дилера
//• вектор игроков.
//Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков.
//В конструкторе создается колода карт и затем перемешивается.
//Также класс имеет один метод play().
//В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется.
//Далее выводится на экран информация о картах каждого игра, в т.ч.и для дилера.
//Затем раздаются игрокам дополнительные карты.
//Потом показывается первая карта дилера и дилер набирает карты, если ему надо.
//После этого выводится сообщение, кто победил, а кто проиграл.В конце руки всех игроков очищаются.


class Game
{
private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
public:
    Game(const std::vector<std::string>& names) {
        // создает вектор игроков из вектора с именами
        std::vector<std::string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }
        // запускает генератор случайных чисел
        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }
    ~Game(){};
    // проводит игру в Blackjack
    void Play() {
        // раздает каждому по две стартовые карты
        std::vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i){
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }
        // прячет первую карту дилера
        m_House.FlipFirstCard();
        // открывает руки всех игроков
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            std::cout << *pPlayer << std::endl;
        }
        std::cout << m_House << std::endl;
        // раздает игрокам дополнительные карты
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            m_Deck.AdditionalCards(*pPlayer);
        }
        // показывает первую карту дилера
        m_House.FlipFirstCard();
        std::cout << std::endl << m_House;
        // раздает дилеру дополнительные карты
        m_Deck.AdditionalCards(m_House);
        if (m_House.IsBusted()){
            // все, кто остался в игре, побеждают
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
                if (!(pPlayer->IsBusted())){
                    pPlayer->Win();
                }
            }
        }
        else{
            // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
                if (!(pPlayer->IsBusted())){
                    if (pPlayer->GetValue() > m_House.GetValue()){
                        pPlayer->Win();
                    }
                    else if (pPlayer->GetValue() < m_House.GetValue()){
                        pPlayer->Lose();
                    }
                    else{
                        pPlayer->Push();
                    }
                }
            }
        }
        // очищает руки всех игроков
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            pPlayer->Clear();
        }
        m_House.Clear();
    }
};




int main()
{
    //1.
    /*std::shared_ptr<Date> today(new Date(19, 12, 2022));
    std::shared_ptr<Date> date(new Date());

    std::cout << "day: " << today->getDay() << " year: " << today->getYear() << std::endl;
    std::cout << *today;

    date = move(today);

    std::cout << date << std::endl;
    std::cout << today << std::endl;*/

    //2

    //std::unique_ptr<Date> date1(new Date(18, 12, 2022));
    //std::unique_ptr<Date> date2(new Date(19, 12, 2022));
    //std::cout << compareDates(date1, date2);

    //5. Написать функцию main() к игре Блекджек.
    //   В этой функции вводятся имена игроков.
    //   Создается объект класса Game и запускается игровой процесс.
    //   Предусмотреть возможность повторной игры.


    static char sResponse = 'n';
    do {
        std::cin.ignore(32767, '\n');
        std::cout << "Enter names of the players: " << std::endl;
        std::string names;
        
        std::getline(std::cin, names);
        std::stringstream sNames(names);

        std::vector<std::string> vNames;

        while (sNames >> names) {
            vNames.push_back(names);
        }

        Game myGame(vNames);
        myGame.Play();
        std::cout << "Do you want to play again?(Y/N): ";
        std::cin >> sResponse;

    } while (sResponse == 'y' || sResponse == 'Y');

    return 0;
}

