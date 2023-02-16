#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    class BombIterator {
    private:
        const std::vector<DynamicObject*>& _vec;
        int _curIndex;
        DynamicObject** _ptr;
    public:
        BombIterator(std::vector<DynamicObject*>& vec) : _vec(vec), _curIndex(-1), _ptr(nullptr) { ++(*this); }
        void reset() { _curIndex = -1; _ptr = nullptr; }
        BombIterator& operator++ ();
        BombIterator& operator-- ();
        DynamicObject*& operator*();
        bool operator==(BombIterator it);
        bool operator!=(BombIterator it);

    };

    BombIterator _begin() { BombIterator it(vecDynamicObj); return it; }
    BombIterator _end() { BombIterator it(vecDynamicObj); it.reset(); return it; }
private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};