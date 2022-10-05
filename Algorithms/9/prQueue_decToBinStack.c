#include <stdio.h>
#include <stdlib.h>

#define SZ 10
#define T char
#define SIZE 1000
#define true 1 == 1
#define false 1 != 1

// Priority queue

typedef struct {
    int pr;
    int dat;
} Node;

Node* arr[SZ];
int items;

void initQueue() {
    for (int i = 0; i < SZ; ++i) {
        arr[i] = NULL;
    }
    items = 0;
}

void ins(int pr, int dat) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->pr = pr;

    if (items == SZ) {
        printf("%s \n", "Queue is full");
        return;
    } else {
        arr[items] = node;
        items++;
    }
}

Node* rem() {
    if (items == 0) {
        return NULL;
    } else {
        Node* tmp = arr[0];
        int idx = 0;
        for(int i = 1; i < items; ++i){
            if(tmp->pr > arr[i]->pr){
                tmp = arr[i];
                idx = i;
            }
        }

        while(idx < items - 1){
            arr[idx] = arr[idx + 1];
            idx++;
        }
        arr[items - 1] = NULL;
        items--;
        return tmp;
    }
}

void printQueue() {
    printf("[ ");
    for (int i = 0; i < SZ; ++i) {
        if (arr[i] == NULL)
            printf("[*, *] ");
        else
            printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
    }
    printf(" ]\n");
}

void prQueueTest() {
    initQueue();
    ins(1, 11);
    ins(3, 22);
    ins(4, 33);
    ins(2, 44);
    ins(3, 55);
    ins(4, 66);
    ins(5, 77);
    ins(1, 88);
    ins(2, 99);
    ins(6, 100);
    printQueue();
    for (int i = 0; i < 7; ++i) {
        Node* n = rem();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);
    }
    printQueue();

    ins(1, 110);
    ins(3, 120);
    ins(6, 130);
    printQueue();

    for (int i = 0; i < 5; ++i) {
        Node* n = rem();
        printf("pr=%d, dat=%d \n", n->pr, n->dat);
    }
    printQueue();

}

// Conversion from decimal to binary number system

typedef int boolean;
int cursor = -1;
T Stack[SIZE];

boolean pushStack(T data) {
    if (cursor < SIZE) {
        Stack[++cursor] = data;
        return true;
    } else {
        printf("%s \n", "Stack overflow");
        return false;
    }
}

T popStack() {
    if (cursor != -1) {
        return Stack[cursor--];
    } else {
        printf("%s \n", "Stack is empty");
        return -1;
    }
}

void decToBinStack(int num){
    while(num >0){
        pushStack(num % 2 + '0');
        num /= 2;
    }
    while (cursor != -1) {
        printf("%c", popStack());
    }
}

int main () {
    prQueueTest();
    decToBinStack(23);
    return 0;
}
