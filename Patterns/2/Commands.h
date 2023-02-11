#pragma once
#include <vector>
#include "DynamicObject.h"
#include "Plane.h"
using std::vector;

class AbstractCommand {
public:
	virtual void Execute() = 0;
};

class CommandDeleteDynamicObj : public AbstractCommand {
public:
	void SetParams(DynamicObject* pObj, vector<DynamicObject*>& vec);
	void Execute() override;	
private:
	DynamicObject* _pObj;
	vector<DynamicObject*>* _pVec;
};

class CommandDeleteStaticObj : public AbstractCommand {
public:
	void SetParams(GameObject* pObj, vector<GameObject*>& vec);
	void Execute() override;
private:
	GameObject* _pObj;
	vector<GameObject*>* _pVec;
};

class CommandDropBomb : public AbstractCommand {
public:
	void SetParams(vector<DynamicObject*>& vec, Plane* const pPlane, uint16_t& bombsNumber, int16_t& score);
	void Execute() override;
private:
	vector<DynamicObject*>* _pVec;
	Plane* _pPlane;
	uint16_t* _pBombsNumber;
	int16_t* _pScore;
};