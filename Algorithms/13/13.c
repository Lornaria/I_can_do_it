#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

boolean visit[14] = {0};

typedef struct OneLinkNode {
    int dat;
    struct OneLinkNode *next;
} OneLinkNode;

typedef struct {
    OneLinkNode *head;
    int size;
} OneLinkList;

typedef struct TwoLinkNode {
    int dat;
    struct TwoLinkNode *next;
    struct TwoLinkNode *prev;
} TwoLinkNode;

typedef struct {
    struct TwoLinkNode *head;
    struct TwoLinkNode *tail;
    int size;
} TwoLinkList;

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

void initTwoLinkList(TwoLinkList *lst) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
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

boolean TwoLinkEnqueue(TwoLinkList *queue, T value) {
    TwoLinkNode *tmp = (TwoLinkNode*) malloc(sizeof(TwoLinkNode));
    if (tmp == NULL) {
        printf("Out of memory! \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = NULL;
    tmp->prev = queue->tail;

    if (queue->tail != NULL) {
        queue->tail->next = tmp;
    }
    if (queue->head == NULL) {
        queue->head = tmp;
    }

    queue->tail = tmp;
    queue->size++;
    return true;
}

T TwoLinkDequeue(TwoLinkList *queue) {
    if (queue->size == 0) {
        printf("Queue is empty \n");
        return -1;
    }
    TwoLinkNode *tmp = queue->head;
    T data = queue->head->dat;

    queue->head = queue->head->next;

    if (queue->head != NULL) {
        queue->head->prev = NULL;
    }
    if (tmp == queue->tail) {
        queue->tail = NULL;
    }

    free(tmp);
    queue->size--;
    return data;
}

int get2dInt(int** array, const int row, const int col) {
    return *((*(array + row)) + col);

}

void set2dInt(int** array, const int row, const int col, int value) {
    *((*(array + row)) + col) = value;
}

void clearIntArray(int* arr, const int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = 0;
    }
}

int** init2dIntArray(int** array, const int row, const int col) {
    array = (int**) calloc(sizeof(int*), row);
    for (int i = 0; i < row; ++i) {
        *(array + i) = (int*) calloc(sizeof(int), col);
    }
    return array;
}

void setLineValues(int** matrix, int cols, int row, ...) {
    va_list args;
    va_start(args, row);
    for (int i = 0; i < cols; ++i) {
        set2dInt(matrix, row, i, va_arg(args, int));
    }
    va_end(args);
}

int getUnvisitedVertex (int** matrix, int ver, int size) {
    for (int i = 0; i < size; i++) {
        if (get2dInt(matrix, ver, i) == 1 && !visit[i])
            return i;
    }
    return -1;
}

void depthTraverseStack(int** matrix, int size) {
    OneLinkList* stack = (OneLinkList*) malloc(sizeof(OneLinkList));
    initOneLinkList(stack);

    visit[0] = true;
    printf("%c ", 0 + 65);
    pushOneLinkStack(stack, 0);

    while (stack->size) {
        int v = getUnvisitedVertex(matrix, stack->head->dat, size);
        if (v == -1) {
            popOneLinkStack(stack);
        } else {
            visit[v] = true;
            printf("%c ", v + 65);
            pushOneLinkStack(stack, v);
        }
    }
    clearIntArray(visit, size);
    printf("\n");
}

int traversalLinks[14] = {0};
int adjacencyLinks[14] = {0};

void adjacencyCount (int** matrix, const int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[j][i] == 1)
                if (i != j)
                    adjacencyLinks[i]++;
        }
    }
}

void traversalCount (int** matrix, int start, const int size) {
    TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    clearIntArray(visit, size);
    TwoLinkEnqueue(queue, start);
    while (queue->size > 0) {
        int indx = TwoLinkDequeue(queue);
        if (visit[indx]) continue;
        visit[indx] = true;
        for (int i = 0; i < size; ++i) {
            if (get2dInt(matrix, indx, i) == 1) {
                if (i != indx)
                    traversalLinks[i]++;
                if (!visit[i])
                    TwoLinkEnqueue (queue, i);
            }
        }
    }
    clearIntArray(visit, size);
}

// структура номер вершины - количество смежных с ней рёбер
typedef struct {
    int node;
    int edges;
} NodeEdges;

// сортирует массив вершин сортировкой вставками от наибольшего количества рёбер к наименьшему
void sortInsert(NodeEdges* array, int len) {
    NodeEdges temp;
    int pos;
    for (int i = 1; i < len; ++i) {
        temp.node = array[i].node;
        temp.edges = array[i].edges;
        pos = i - 1;
        while (pos >= 0 && array[pos].edges < temp.edges) {
            array[pos + 1].node = array[pos].node;
            array[pos + 1].edges = array[pos].edges;
            pos--;
        }
        array[pos + 1].node = temp.node;
        array[pos + 1].edges = temp.edges;
    }
}

// выводит на экран номер вершины и количество смежных с ней рёбер
void printNodeEdge(NodeEdges* a) {
    printf("vertex %02d:%2d edges\n", a->node, a->edges);
}

// выводит на экран список вершин и количество смежных с ними рёбер
void printResult(NodeEdges* array, int len) {
    for (int i = 0; i < len; ++i)
        printNodeEdge(array + i);
}

// рекурсивная функция обхода графа в ширину, количество подсчётов захода в каждую вершину считается в массиве edges
void widthTraverseRec(int** matrix, TwoLinkList* queue,
                      int* visited, int* edges, int start, const int size) {

    // ищем смежные вершины, считаем их и ставим в очередь для подсчёта их рёбер
    for (int next = 0; next < size; ++next)
        if ((get2dInt(matrix, start, next) == 1)) {
            ++edges[start];
            if (!visited[next]) {
                visited[next] = 1;
                TwoLinkEnqueue(queue, next);
            }
        }

    // переходим к следующей вершине в очереди
    if (queue->size > 0)
        widthTraverseRec(matrix, queue, visited,
                         edges, TwoLinkDequeue(queue), size);
}

// обрабатывает входящий массив полустепеней захода - сортирует и печатает
void composeTraverseResult(int* array, const int nodes) {
    NodeEdges* result = (NodeEdges*)calloc(nodes, sizeof(NodeEdges));
    for (int i = 0; i < nodes; ++i) {
        result[i].node = i;
        result[i].edges = array[i];
    }
    sortInsert(result, nodes);
    printResult(result, nodes);
    printf("\n\n");
    free(result);
}

void traversalCountFacade(int** graph, const int start, const int nodes) {

    // нам понадобится массив для отметки посещённых вершин
     int* visited = (int*)calloc(nodes, sizeof(int));    // изначально массив обнулён
     // и массив для подсчёта полустепеней захода
     int* recEdges = (int*)calloc(nodes, sizeof(int));  // изначально массив обнулён
     // очередь из вершин должна не зависить от экземпляра функции, поэтому создаём её здесь
     TwoLinkList* queue = (TwoLinkList*)malloc(sizeof(TwoLinkList));
     initTwoLinkList(queue);
     visited[start] = 1;

     widthTraverseRec(graph, queue, visited, recEdges, start, nodes);
     composeTraverseResult(recEdges, nodes);

}

int main() {
    int** adj = init2dIntArray(adj, 14, 14);
    setLineValues(adj, 14,  0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);
    setLineValues(adj, 14,  4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
    setLineValues(adj, 14,  7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    setLineValues(adj, 14,  8, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);
    setLineValues(adj, 14,  9, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
    setLineValues(adj, 14, 10, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0);
    setLineValues(adj, 14, 11, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0);
    setLineValues(adj, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1);
    setLineValues(adj, 14, 13, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
    depthTraverseStack (adj, 14);

    adjacencyCount(adj, 14);
    printIntArray(adjacencyLinks, 14, 3);

    traversalCount(adj, 0, 14);
    printIntArray(traversalLinks, 14, 3);

    traversalCountFacade(adj, 0, 14);

}


