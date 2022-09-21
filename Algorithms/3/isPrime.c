#include <stdio.h>

int isPrime(float num)
{
    if(num <= 1 || (int)num != num)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i <= num; i++)
        {
            if (i == (int)num)
            {
                return 1;
            }
            else if ((int)num % i == 0)
            {
                return 0;
            }
        }
    }
}

int main()
{
    float num;
    printf("%s", "Your number:");
    scanf("%f", &num);
    if(isPrime(num))
    {
        printf("%s", "It is a prime!");
    }
    else
    {
        printf("%s", "It is not a prime.");
    }
    return 0;
}
