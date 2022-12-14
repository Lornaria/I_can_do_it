#include <iostream>
#include "blackjack.h"

//1. Создать программу, которая считывает целое число типа int.
//И поставить «защиту от дурака» : если пользователь вводит что - то кроме одного целочисленного значения, 
//нужно вывести сообщение об ошибке и предложить ввести число еще раз.

int getIntNumber()
{
	while (true)
	{
		std::cout << "Enter an integer value: ";
		int num;
		std::cin >> num;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "Error. Please enter an integer number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			return num;
		}
	}
}

//2. Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& __CLRCALL_OR_CDECL endll(
	std::basic_ostream<_Elem, _Traits>& _Ostr) { // insert 2 newlines and flush stream
	_Ostr.put(_Ostr.widen('\n'));
	_Ostr.put(_Ostr.widen('\n'));
	_Ostr.flush();
	return _Ostr;
}

//3. Реализовать класс Player, который наследует от класса GenericPlayer.У этого класса будет 4 метода:
//• virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
// Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
//• void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
//• void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
//• void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.

class Player : public GenericPlayer {
public:
	Player(std::string _name) : GenericPlayer(_name) {}
	Player(){}
	~Player(){}
	bool IsHitting() const override {
		std::cout << name << ", do you want a hit? (Y/N): ";
		char response;
		std::cin >> response;
		return (response == 'y' || response == 'Y');
	}
	void Win() const {
		std::cout << name << " wins." << std::endl;
	}
	void Lose() const {
		std::cout << name << " loses." << std::endl;
	}
	void Push() const {
		std::cout << name << " pushes." << std::endl;
	}
};

//4. Реализовать класс House, который представляет дилера.Этот класс наследует от класса GenericPlayer.У него есть 2 метода:
//• virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта.Если у дилера не больше 16 очков, то он берет еще одну карту.
//• void FlipFirstCard() - метод переворачивает первую карту дилера.

class House : public GenericPlayer {
public:
	House() { name = "House"; }
	~House(){}
	bool IsHitting() const override {
		return (GetValue() <= 16);
	}
	void FlipFirstCard() {
		if (!(hand.empty())) {
			hand[0]->Flip();
		}
		else
		{
			std::cout << "No card to flip!" << std::endl;
		}
		
	}
};

//5. Написать перегрузку оператора вывода для класса Card.
//Если карта перевернута рубашкой вверх(мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты.
//Также для класса GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты, а также общую сумму очков его карт.

std::ostream& operator<<(std::ostream& os, const Card& aCard) {
	const std::string RANKS[] = { "0", "0", "2", "3", "4", "5", "6", "7", "8", "9","10", "A", "J", "Q", "K" };
	const char SUITS[] = { 's', 'h', 'd', 'c'};
	if (aCard.faceUp)
	{
		
		os <<RANKS[aCard.value] << SUITS[aCard.suit];
	}
	else
	{
		os << "XX";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer) {
	os << aGenericPlayer.name << ":\t";
	std::vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.hand.empty())
	{
		for (pCard = aGenericPlayer.hand.begin();
			pCard != aGenericPlayer.hand.end();
			++pCard)
		{
			os << *(*pCard) << "\t";
		}
		if (aGenericPlayer.GetValue() != 0)
		{
			std::cout << "(" << aGenericPlayer.GetValue() << ")";
		}
	}
	else
	{
		os << "<empty>";
	}
	return os;
}


int main()
{
	//std::cout << "Your int number: " << getIntNumber() << std::endl;

	//std::cout << "some text" << endll;
	//std::cout << "some text" << std::endl;

	return 0;
}
