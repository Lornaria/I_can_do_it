#include <stdio.h>

#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct OneLinkNode {
    int dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct {
    OneLinkNode *head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList *lst) {
    lst->head = NULL;
    lst->size = 0;
}

boolean pushOneLinkStack(OneLinkList *stack, T value) {
    OneLinkNode *tmp = (OneLinkNode*) malloc(sizeof(OneLinkNode));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

T popOneLinkStack(OneLinkList *stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    OneLinkNode *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

void printOneLinkIntNode(OneLinkNode *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}

void printOneLinkIntList(OneLinkList *lst) {
    OneLinkNode *current = lst->head;
    if (current == NULL) {
        printOneLinkIntNode(current);
    } else {
        do {
            printOneLinkIntNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}

int bracesCheck(char* expression) {
    const int TYPES = 3;
    char braces[][2] = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    OneLinkList *st = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(st);
    int countIndex = 0;
    while (*expression != '\0') {
        for (int i = 0; i < TYPES; ++i) {
            if (*expression == braces[i][0])
              pushOneLinkStack(st, i);
        }
        for (int i = 0; i < TYPES; ++i) {
            if (*expression == braces[i][1]) {
                if (st->size == 0)
                  return countIndex;
                if (i == st->head->dat)
                    popOneLinkStack(st);
                else
                    return countIndex;
            }
        }
        expression++;
        countIndex++;
    }
    if (st->size != 0)
        return st->head->dat;
    return -1;
}

void copyList(OneLinkList* from, OneLinkList* to) {
 	OneLinkNode* current = from->head;
 	if (current == NULL) return;

    pushOneLinkStack(to, current->dat);
    OneLinkNode* nodeInNew = to->head;
    while (current->next != NULL) {
        OneLinkNode *tmp = (OneLinkNode*) malloc(sizeof(OneLinkNode));
        if (tmp == NULL) {
            printf("Stack overflow \n");
            return;
        }
        tmp->dat = current->next->dat;
        nodeInNew->next = tmp;
        tmp->next = NULL;

        current = current->next;
        nodeInNew = tmp;
        to->size++;
    }
}

boolean isSorted(OneLinkList *lst) {
    boolean asc = true;
    boolean desc = true;
    OneLinkNode *current = lst->head;
    while (current->next != NULL) {
        if (current->dat > current->next->dat)
            asc = false;
        if (current->dat < current->next->dat)
            desc = false;
        current = current->next;
    }
    return asc || desc;
}

int main() {
    printf("%d \n", bracesCheck("([{}])"));
    printf("%d \n", bracesCheck("())({)"));
    printf("%d \n", bracesCheck("(2+(2*2)))"));

    OneLinkList* first = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(first);
    OneLinkList* second = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(second);
    for (int i = 9; i > 1; --i) {
        pushOneLinkStack(first, i);
    }
    copyList(first, second);
    printOneLinkIntList(first);
    printOneLinkIntList(second);
    printf("%s \n", isSorted(first) ? "true" : "false");
    return 0;
}


