//*********************| Start of changes for lesson 5 |**************************
#pragma once

class Bomb;
class Plane;

class Visitor {
public:
    virtual void log(Plane& e) const = 0;
    virtual void log(Bomb& e) const = 0;
};

class LogVisitor : public Visitor {
public:
    void log(Plane& e) const override;

    void log(Bomb& e) const override;
};
//*********************| End of changes for lesson 5 |****************************