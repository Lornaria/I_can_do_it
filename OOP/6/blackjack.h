#pragma once
#pragma once
#include <iostream>
#include <vector>

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
	jack = 12,
	queen = 13,
	king = 14,
	ace = 11
};

class Card {
private:
	Suit suit = spades;
	Value value = two;
	bool faceUp = false;
public:
	Card(Suit _suit, Value _value) : suit(_suit), value(_value) {}
	Card(Suit _suit, Value _value, bool _faceUp) : suit(_suit), value(_value), faceUp(_faceUp) {}
	Card() {}
	~Card() { std::cout << __FUNCTION__ << std::endl; }
	void Flip() {
		faceUp = !faceUp;
	}
	int GetValue() const {
		if (faceUp) {
			if (value > 11) {
				return 10;
			}
			return value;
		}
		return 0;
	}
	friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
};

class Hand {
protected:
	std::vector<Card*> hand;
public:
	Hand() { hand.reserve(7); }
	virtual ~Hand() { Clear(); }
	void Add(Card* newCard) {
		hand.push_back(newCard);
	}
	void Clear() {
		std::vector<Card*>::iterator iter = hand.begin();
		for (iter = hand.begin(); iter != hand.end(); ++iter)
		{
			delete* iter;
			*iter = 0;
		}
		hand.clear();
	}
	int GetValue() const {
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

class GenericPlayer : public Hand {
protected:
	std::string name = "None";
public:
	GenericPlayer(std::string _name) : name(_name) {}
	GenericPlayer() {}
	virtual bool IsHitting() const = 0;
	bool IsBoosted() const {
		if (GetValue() > 21) {
			return true;
		}
		return false;
	}
	void Bust() const {
		std::cout << name << " busts!\n";
	}
	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);
};
