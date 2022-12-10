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
	jack = 10,
	queen = 10,
	king = 10,
	ace = 11
};

class Card {
private:
	Suit suit = spades;
	Value value = two;
	bool faceUp = false;
public:
	Card(Suit _suit, Value _value) : suit(_suit), value(_value) {}
	Card() {}
	void Flip() {
		faceUp = !faceUp;
	}
	Value GetValue() {
		return value;
	}
};

class Hand {
private:
	std::vector<Card*> hand;
public:
	Hand() {}
	~Hand() { Clear(); }
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
	int GetValue() {
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
