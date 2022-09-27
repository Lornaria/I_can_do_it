#include<stdio.h>

int decToBinRec(int dec, float constATenth) // constATenth должно всегда быть равным 0.1 как значение по умолчанию
{
    int result = 0;
    if(dec == 0)
    {
        return dec % 2 * constATenth;
    }
    else
    {
        constATenth *= 10; // имитирует разрядность
        result = (dec % 2) * constATenth + decToBinRec(dec / 2, constATenth);
    }
    return result;
}

int expRecOne (int base, int exponent)
{
    int result = 0;
    if(exponent == 0)
    {
        return 1;
    }
    result = base * expRecOne(base, exponent - 1);
    return result;
}

int expRecTwo (int base, int exponent)
{
    int result = 0;
    if(exponent == 0)
    {
        return 1;
    }
    if(exponent % 2 == 0)
    {
        result = base * base * expRecTwo(base, exponent / 2);
    }
    else
    {
        result = base * expRecTwo(base, exponent - 1);
    }
    return result;
}

int main()
{
    printf("%d\n", decToBinRec(19, 0.1));
    printf("%d\n", expRecOne(2, 6));
    printf("%d\n", expRecTwo(2, 8));

    return 0;
}
