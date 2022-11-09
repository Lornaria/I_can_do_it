#include <stdio.h>

int simpleHashSum(char* in) {
    int sum = 0;
    while (*in != '\0') {
        sum += *in;
        in++;
    }
    return sum;
}

int* exchange(int* money, int size, int sum) {
    if (size == 0 || sum == 0)
        return NULL;

    int* rslt = (int*) calloc(100, sizeof(int)); // (*(money+size-1) * sum, sizeof(int)) //O
    rslt[0] = 0;
    int current;
    int k = 1;
    for (int i = 0; i < size; ++i) {
        current = 0;
        while (sum - current >= money[i]) {
            current += money[i];
            rslt[k] = money[i];
            rslt[0]++;
            k++;
            if (sum == current)
                return rslt;
        }
        sum -= current;
    }
    printf("%s \n", "Exchange failed");
    return NULL;
}

void printArr(int* arr) {
    int i = 1;
    while(i <= arr[0]) {
        printf("%d, ", arr[i++]);
    }
    printf("\n");
}

int main() {
    printf("%d \n", simpleHashSum("HelloWorld!"));
    printf("%d \n", simpleHashSum("IelloWorld!"));

    int money[] = {50, 10, 5, 2, 1};
    printArr(exchange(money, 5, 98));

}

