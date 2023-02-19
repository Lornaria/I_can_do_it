
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
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

//*********************| Start of changes for lesson 4 |**************************
void House::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Yellow);
	for (int i = 6; i >= 0; i--) {
		ScreenSingleton::getInstance().GotoXY(x, y - 6 + i);
		for (int j = 0; j < 14; j++) {
			cout << look[i][j];
		}
	}
}
//*********************| End of changes for lesson 4 |**************************