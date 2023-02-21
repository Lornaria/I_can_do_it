#pragma once

#include "DynamicObject.h"

class DynamicObject;

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

//*********************| Start of changes for lesson 5 |**************************

    void accept(const Visitor& v) override
    {
        v.log(*this);
    }

//*********************| End of changes for lesson 5 |****************************
private:

};

