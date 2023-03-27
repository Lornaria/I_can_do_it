#pragma once
#include <string>
#include "LevelGUI.h"
class Mediator
{
private:
	LevelGUI* pLvlGUI;
public:
	Mediator(LevelGUI* _pLvlGUI) : pLvlGUI(_pLvlGUI) {}
	void passMessage(const std::string& message);
};

