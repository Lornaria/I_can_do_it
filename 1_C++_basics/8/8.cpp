#include <iostream>
#include<random>
#include<stdlib.h>
#include<chrono>
#include <Windows.h>

enum TCell : char 
{
    CROSS = 'X',
    ZERO = '0',
    EMPTY = ' '
};

enum TProgress 
{
    IN_PROGRESS,
    WON_HUMAN,
    WON_AI,
    DRAW
};

struct TCoord 
{
    size_t y{ 0 };
    size_t x{ 0 };
};

#pragma pack(push, 1)
struct TGame
{
    TCell** ppField = nullptr;
    const size_t SIZE{ 3 };
    TProgress progress{ IN_PROGRESS };
    TCell human = EMPTY, ai = EMPTY;
    size_t turn{0U};
};
#pragma pack(pop)


void clearScr()
{
    system("cls");
    //std::cout << "\x1B[2J\x1B[H";
}

int32_t getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}
//********************************************************************

void __fastcall initGame(TGame& g) 
{
    g.ppField = new TCell * [g.SIZE];
    for (size_t i = 0; i < g.SIZE; i++)
    {
        g.ppField[i] = new TCell[g.SIZE];
    }

    for (size_t y = 0; y < g.SIZE; y++)
    {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            g.ppField[y][x] = EMPTY;
        }

    }

    if (getRandomNum(0, 1000) > 500)
    {
        g.human = CROSS;
        g.ai = ZERO;
        g.turn = 0;
    }
    else
    {
        g.human = ZERO;
        g.ai = CROSS;
        g.turn = 1;
    }
}

void changingColor(TCell sign)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (sign)
    {
    case EMPTY:
        SetConsoleTextAttribute(hConsole, 15);
        break;
    case CROSS:
        SetConsoleTextAttribute(hConsole, 9);
        break;
    case ZERO:
        SetConsoleTextAttribute(hConsole, 12);
        break;
    }
}

void __fastcall drawGame(const TGame& g)
{
    std::cout << "     ";
    for (size_t x = 0; x < g.SIZE; x++)
    {
        std::cout << x + 1 << "   ";
    }
    std::cout << std::endl;

    for (size_t y = 0; y < g.SIZE; y++)
    {
        std::cout << " " << y + 1 << " | ";
        for (size_t x = 0; x < g.SIZE; x++)
        {         
            if (g.ppField[y][x] == CROSS)
            {
                changingColor(CROSS);
                std::cout << g.ppField[y][x];
                changingColor(EMPTY);
                std::cout << " | ";
            }
            else if (g.ppField[y][x] == ZERO)
            {
                changingColor(ZERO);
                std::cout << g.ppField[y][x];
                changingColor(EMPTY);
                std::cout << " | ";
            }
            
            else
            {
                std::cout << g.ppField[y][x] << " | ";
            }
            
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "Human: " << g.human << std::endl << "Computer: " << g.ai << std::endl;
}

void __fastcall deinitGame(TGame& g)
{
    for (size_t i = 0; i < g.SIZE; i++)
    {
        delete [] g.ppField[i];
    }
    delete[] g.ppField;
}

TProgress __fastcall getWon(const TGame& g)
{
    for (size_t y = 0; y < g.SIZE; y++)
    {
        if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2])
        {
            if (g.ppField[y][0] == g.human)
            {
                return WON_HUMAN;
            }

            if (g.ppField[y][0] == g.ai)
            {
                return WON_AI;
            }
        }
    }

    for (size_t x = 0; x < g.SIZE; x++)
    {
        if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[0][x] == g.ppField[2][x])
        {
            if (g.ppField[0][x] == g.human)
            {
                return WON_HUMAN;
            }

            if (g.ppField[0][x] == g.ai)
            {
                return WON_AI;
            }
        }
    }

    if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2])
    {
        if (g.ppField[1][1] == g.human)
        {
            return WON_HUMAN;
        }

        if (g.ppField[1][1] == g.ai)
        {
            return WON_AI;
        }
    }

    if (g.ppField[0][2] == g.ppField[1][1] && g.ppField[0][2] == g.ppField[2][0])
    {
        if (g.ppField[1][1] == g.human)
        {
            return WON_HUMAN;
        }

        if (g.ppField[1][1] == g.ai)
        {
            return WON_AI;
        }
    }

    bool draw{ true };
    for (size_t y = 0; y < g.SIZE; y++)
    {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                draw = false;
                break;
            }
        }
        if (!draw)
            break;
    }
    if (draw)
        return DRAW;

    return IN_PROGRESS;
}

TCoord __fastcall getHumanCoord(const TGame& g)
{
    TCoord c;
    do
    {
        std::cout << "Enter X (1..3): ";
        std::cin >> c.x;
        std::cout << "Enter Y (1..3): ";
        std::cin >> c.y;
        c.x--;
        c.y--;
    } while (c.x > 2 || c.y > 2 || g.ppField[c.y][c.x] != EMPTY);

    return c;
}

TCoord __fastcall getAICoord(TGame& g)
{
    //предвыиграшная ситуация
    for (size_t y = 0; y < g.SIZE; y++)
    {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                g.ppField[y][x] = g.ai;
                if (getWon(g) == WON_AI)
                {
                    g.ppField[y][x] = EMPTY;
                    return { y, x };
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }
    //предпроигрышная ситуация
    for (size_t y = 0; y < g.SIZE; y++)
    {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY)
            {
                g.ppField[y][x] = g.human;
                if (getWon(g) == WON_HUMAN)
                {
                    g.ppField[y][x] = EMPTY;
                    return { y, x };
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }
    //по приоритетам + рандом
    if (g.ppField[1][1] == EMPTY)
    {
        return { 1, 1 };
    }

    //проверка свободных углов
    TCoord buf[4];
    size_t num{ 0 };
    if (g.ppField[0][0] == EMPTY)
    {
        buf[num] = { 0, 0 };
        num++;
    }

    if (g.ppField[2][2] == EMPTY)
    {
        buf[num] = { 2, 2 };
        num++;
    }

    if (g.ppField[2][0] == EMPTY)
    {
        buf[num] = { 2, 0 };
        num++;
    }

    if (g.ppField[0][2] == EMPTY)
    {
        buf[num] = { 0, 2 };
        num++;
    }

    if (num > 0)
    {
        const size_t index = getRandomNum(0, 1000) % num;
        return buf[index];
    }
    //проверка свободных не углов
    if (g.ppField[1][0] == EMPTY)
    {
        buf[num] = { 1, 0 };
        num++;
    }

    if (g.ppField[1][2] == EMPTY)
    {
        buf[num] = { 1, 2 };
        num++;
    }

    if (g.ppField[0][1] == EMPTY)
    {
        buf[num] = { 0, 1 };
        num++;
    }

    if (g.ppField[2][1] == EMPTY)
    {
        buf[num] = { 2, 1 };
        num++;
    }

    if (num > 0)
    {
        const size_t index = getRandomNum(0, 1000) % num;
        return buf[index];
    }


}

void congrats(const TGame& g)
{
    if (g.progress == WON_HUMAN)
    {
        std::cout << "Won human! :)" << std::endl;
    }
    else if (g.progress == WON_AI)
    {
        std::cout << "Won computer! :(" << std::endl;
    }
    else
    {
        std::cout << "Draw! :|" << std::endl;
    }
}


//********************************************************************
int main()
{
    

    TGame g;
    initGame(g);
    changingColor(EMPTY);
    drawGame(g);

    do
    {
        if (g.turn % 2 == 0) //ходит человек
        {
            TCoord c = getHumanCoord(g);
            g.ppField[c.y][c.x] = g.human;
        }
        else // ходит ПК
        {
            TCoord c = getAICoord(g);
            g.ppField[c.y][c.x] = g.ai;
        }

        clearScr();
        drawGame(g);
        g.turn++;
        g.progress = getWon(g);

    } while (g.progress == IN_PROGRESS);

    congrats(g);

    deinitGame(g);
    return 0;
}
