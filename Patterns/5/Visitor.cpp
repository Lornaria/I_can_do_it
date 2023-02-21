//*********************| Start of changes for lesson 5 |**************************
#include "Visitor.h"
#include "MyTools.h"
#include "Plane.h"
#include "Bomb.h"
using namespace MyTools;

void LogVisitor::log(Plane& e) const {
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Plane x= "), e.GetX());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Plane y= "), e.GetY());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Plane speed= "), e.GetSpeed());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Plane x direction= "), e.GetDirection().first);
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Plane y direction= "), e.GetDirection().second);
}

void LogVisitor::log(Bomb& e) const {
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Bomb x= "), e.GetX());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Bomb y= "), e.GetY());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Bomb speed= "), e.GetSpeed());
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Bomb x direction= "), e.GetDirection().first);
    FileLoggerSingletone::getInstance().WriteToLog(std::string("Bomb y direction= "), e.GetDirection().second);
}
//*********************| End of changes for lesson 5 |****************************