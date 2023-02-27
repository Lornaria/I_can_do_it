#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"
#include "Mediator.h"
#include <vector>
#include <random>

class Tank : public DestroyableGroundObject
{
public:
	Tank(Mediator* _Mediator);
	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	const uint16_t score = 30;
//*********************| Start of changes for lesson 6 |**************************
	Mediator* pMediator;
	std::vector<std::string> vPhrases;
	mutable std::mt19937 rnd;
	std::uniform_int_distribution<int> distribVec;
	std::uniform_int_distribution<int> distribChance = std::uniform_int_distribution<int>(0, 100);
//*********************| End of changes for lesson 6 |****************************
};

