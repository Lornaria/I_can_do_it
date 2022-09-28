#include <stdio.h>

void fillIntRandom(int* array, int size, int border) {
    for (int i = 0; i < size; ++i)
        *(array + i) = rand() % border;
}

void printIntArray(int* array, int size, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

void swapInt(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sortInserts(int* arr, int len) {
    int temp, pos;
    for (int i = 1; i < len; ++i) {
        temp = arr[i];
        pos = i - 1;
        while (pos >= 0 && arr[pos] > temp) {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = temp;
    }
}

void qsImp(int* arr, int first, int last) {
    if ((last - first) > 10){
        int i = first;
        int j = last;
        int middle = (first + last) / 2;
        if ((arr[middle] - arr[first]) * (arr[last] - arr[middle]) >= 0){
        }
        else if ((arr[first] - arr[middle]) * (arr[last] - arr[first])>= 0){
            swapInt(&arr[first], &arr[middle]);
        }
        else{
            swapInt(&arr[last], &arr[middle]);
        }
        int x = arr[middle];
        do {
            while (arr[i] < x) i++;
            while (arr[j] > x) j--;

            if (i <= j) {
                swapInt(&arr[i], &arr[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (i < last) qsImp(arr, i, last);
        if (first < j) qsImp(arr, first, j);
    }
    else{
        sortInserts(arr, last + 1);
    }

}

int main(){
    const int SIZE = 20;
    int myArr[SIZE];
    fillIntRandom(myArr, SIZE, 100);
    printIntArray(myArr, SIZE, 3);
    qsImp(myArr, 0, SIZE - 1);
    printIntArray(myArr, SIZE, 3);
    return 0;
}
