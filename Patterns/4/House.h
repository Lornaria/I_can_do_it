#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;
	friend class HouseBuilderA;
private:
	char look[7][14];
	const uint16_t score = 40;
};

//*********************| Start of changes for lesson 4 |**************************
class HouseBuilder {
public:
	HouseBuilder() : _pHouse(nullptr) {}
	virtual ~HouseBuilder(){}
	virtual void createHouse(){}

	virtual void buildWalls(){}
	virtual void buildFloor(){}
	virtual void buildRoof(){}
	virtual void buildWindow(){}
	virtual void buildPipe() {}
	virtual House* getHouse() { return _pHouse; }
protected:
	House* _pHouse;
};

class HouseBuilderA : public HouseBuilder {
public:
	void createHouse() override {
		_pHouse = new House;
	}

	void buildWalls() override {
		for (int i = 4; i < 6; i++) {
			for (size_t j = 0; j < 14; j++)
			{
				if (j == 0 || j == 13) {
					_pHouse->look[i][j] = '#';
				}
				else {
					_pHouse->look[i][j] = ' ';
				}
			}
		}
	}

	void buildFloor() override {
		for (size_t j = 0; j < 14; j++)
		{
			_pHouse->look[6][j] = '#';
		}
	}

	void buildRoof() override {
		for (size_t i = 0; i < 4; i++)
		{
			switch (i) {
			case 0:
				for (size_t j = 0; j < 14; j++)
				{
					if (j >= 4 && j < 10) {
						_pHouse->look[i][j] = '#';
					}
					else {
						_pHouse->look[i][j] = ' ';
					}
				}
				break;
			case 1:
				for (size_t j = 0; j < 14; j++)
				{
					if (j == 2 || j == 3 || j == 10 || j == 11) {
						_pHouse->look[i][j] = '#';
					}
					else {
						_pHouse->look[i][j] = ' ';
					}
				}
				break;
			case 2:
				for (size_t j = 0; j < 14; j++)
				{
					if (j == 0 || j == 1 || j == 12 || j == 13) {
						_pHouse->look[i][j] = '#';
					}
					else {
						_pHouse->look[i][j] = ' ';
					}
				}
				break;
			case 3:
				for (size_t j = 0; j < 14; j++)
				{
					_pHouse->look[i][j] = '#';
				}
				break;
			}
		}
	}

	void buildWindow() override{
		for (int i = 4; i < 6; i++) {
			for (int j = 4; j < 7; j++) {
				_pHouse->look[i][j] = '#';
			}
		}
	}

	void buildPipe() override{
		_pHouse->look[0][12] = 'T';
		_pHouse->look[0][13] = 'T';
		_pHouse->look[1][12] = '|';
		_pHouse->look[1][13] = '|';
	}
};

class HouseDirector {
public:
	House* constructWithPipe (HouseBuilder& builder) {
		builder.createHouse();
		builder.buildWalls();
		builder.buildFloor();
		builder.buildRoof();
		builder.buildWindow();
		builder.buildPipe();
		return(builder.getHouse());
	}
	House* constructWithoutPipe(HouseBuilder& builder) {
		builder.createHouse();
		builder.buildWalls();
		builder.buildFloor();
		builder.buildRoof();
		builder.buildWindow();
		return(builder.getHouse());
	}
};
//*********************| End of changes for lesson 4 |**************************