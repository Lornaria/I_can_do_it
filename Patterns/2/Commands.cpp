#include "Commands.h"
#include "Bomb.h"
#include "Ground.h"
#include "MyTools.h"

void CommandDeleteDynamicObj::SetParams(DynamicObject* pObj, vector<DynamicObject*>& vec) {
	_pObj = pObj;
	_pVec = &vec;
}

void CommandDeleteDynamicObj::Execute() {
    auto it = (*_pVec).begin();
    for (; it != (*_pVec).end(); it++)
    {
        if (*it == _pObj)
        {
            (*_pVec).erase(it);
            break;
        }
    }
}

void CommandDeleteStaticObj::SetParams(GameObject* pObj, vector<GameObject*>& vec) {
    _pObj = pObj;
    _pVec = &vec;
}

void CommandDeleteStaticObj::Execute() {
    auto it = (*_pVec).begin();
    for (; it != (*_pVec).end(); it++)
    {
        if (*it == _pObj)
        {
            (*_pVec).erase(it);
            break;
        }
    }
}

void CommandDropBomb::SetParams(vector<DynamicObject*>& vec, Plane* const pPlane, uint16_t& bombsNumber, int16_t& score) {
    _pVec = &vec;
    _pPlane = pPlane;
    _pBombsNumber = &bombsNumber;
    _pScore = &score;

}

void CommandDropBomb::Execute() {
    if (*_pBombsNumber > 0) {
        MyTools::FileLoggerSingletone::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");
        double x = _pPlane->GetX() + 4;
        double y = _pPlane->GetY() + 2;
        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);
        (*_pVec).push_back(pBomb);
        (*_pBombsNumber)--;
        (*_pScore) -= Bomb::BombCost;
    }
}
