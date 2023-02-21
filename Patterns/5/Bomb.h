#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10;

	void Draw() const override;

//*********************| Start of changes for lesson 5 |**************************
	
	void accept(const Visitor& v) override
	{
		v.log(*this);
	}

//*********************| End of changes for lesson 5 |****************************
private:

};

