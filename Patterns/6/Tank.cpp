
#include <iostream>

#include "Tank.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

//*********************| Start of changes for lesson 6 |**************************
void initVecOfPhrases(std::vector<string>& _v) {
	_v.push_back("Phrase 1!");
	_v.push_back("Phrase 2!");
	_v.push_back("Phrase 3!");
	_v.push_back("Phrase 4!");
	_v.push_back("Phrase 5!");
}

Tank::Tank(Mediator* _Mediator) : pMediator(_Mediator) {
	initVecOfPhrases(vPhrases);
	rnd.seed(23);
	distribVec = std::uniform_int_distribution<int>(0, static_cast<int>(vPhrases.size() - 1));
}

void Tank::Draw() const
{
	int dice = distribChance(rnd);
	if (dice < 20) {
		dice = distribVec(rnd);
		pMediator->passMessage(vPhrases[dice]);
	}

	MyTools::ScreenSingleton::getInstance().SetColor(CC_Brown);
	ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x - 2, y - 2);
	cout << "#######   #";
	ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "    #####";
	ScreenSingleton::getInstance().GotoXY(x, y);
	cout << " ###########";
}

//*********************| End of changes for lesson 6 |****************************


bool Tank::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

