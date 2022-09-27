#include <stdio.h>
#include <math.h>

int** init2dArray(int rows, int cols) {  //инициализация двумерного массива и заполнение рандомными числами до 10
    int **arr = malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; ++i) {
        *(arr + i) = malloc(sizeof(int) * cols);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % 10;
        }
    }
    return arr;
}

void print2dArray(int** arr, const int row, const int col){
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            printf("  %d", *((*(arr + i)) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void swapInt(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubble2dSort(int** arr, int rows, int cols){
    int length = rows * cols;
    for (int i = 0; i < length; ++i){
        for (int j = 0; j < rows; ++j){
            for (int k = 0;  k < cols - 1; ++k){
                if ((k == 0 && j > 0) && (arr[j - 1][cols - 1] > arr[j][k])){
                    swapInt(&arr[j - 1][cols - 1], &arr[j][k]);
                }
                if (arr[j][k] > arr[j][k + 1]){
                    swapInt(&arr[j][k], &arr[j][k + 1]);
                }
            }
        }
    }
}

void algTPK(){
    float a[11] = {};
    float y;
    for (int i = 0; i < 11; ++i){
        printf("Number %d: ", i + 1);
        scanf("%f", &a[i]);
    }
    printf("\n");
    for (int i = 10; i >= 0; --i) {
        y = sqrt(fabs(a[i])) + 5 * pow(a[i], 3);
        if (y > 400)
            printf("%d greater than 400\n", i + 1);
        else
            printf("%d %f\n", i + 1, y);
    }
}

int main(){

    const int ROWS = 6;
    const int COLS = 4;

    int** arr = init2dArray(ROWS, COLS);
    print2dArray(arr, ROWS, COLS);
    bubble2dSort(arr, ROWS, COLS);
    print2dArray(arr, ROWS, COLS);

    algTPK();

    return 0;
}
