#pragma once

#include <stdint.h>

#include "GameObject.h"
#include "Visitor.h"

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    
//*********************| Start of changes for lesson 5 |**************************

    double GetSpeed() { return speed; }
    std::pair<double, double> GetDirection() { return std::make_pair(xDirction, yDirection); }
    virtual void accept(const Visitor& v) = 0;

//*********************| End of changes for lesson 5 |****************************

    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };

protected:

    double speed;
    double xDirction, yDirection;

};
