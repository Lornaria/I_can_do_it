
#include <conio.h>

#include "SBomber.h"
#include "MyTools.h"
#include "FileLogger.h"

using namespace std;

FileLogger g_logger("log.txt"); //******************* added for lesson 7 **********************************************************


int main(void)
{
    //MyTools::OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    //MyTools::CloseLogFile();

    return 0;
}
