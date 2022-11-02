#include <stdio.h>
#include <stdlib.h>

#define T char
#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} BinTreeIntNode;

int countDepth(BinTreeIntNode *node) {
    if (node == NULL) {
        return 0;
    }
    int left = 0;
    int right = 0;
    if (node->left != NULL) {
        left = countDepth(node->left);
    }
    if (node->right != NULL) {
        right = countDepth(node->right);
    }
    return 1 + ((left > right) ? left : right);
}

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
    BinTreeIntNode *newNode;
    newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode *current = t;
    BinTreeIntNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}


boolean isBalanced(BinTreeIntNode *root) {
    return abs(countDepth(root->left) - countDepth(root->right)) <= 1;
}

void fillTree(int size, BinTreeIntNode *root) {
    for (int i = 0; i < size; ++i) {
        treeInsert(root, rand() % 1000);
    }
}

BinTreeIntNode* searchNode(BinTreeIntNode *root, int data) {
    if (root == NULL || root->key == data)
        return root;

    if (data < root->key)
        return searchNode(root->left, data);
    else
        return searchNode(root->right, data);
}

int main() {
    const int TREES = 50;
    const int size = 10000;
    int balanced = 0;

    for (int i = 0; i < TREES; ++i) {
        BinTreeIntNode *node = NULL;
        BinTreeIntNode *root = treeInsert(node, rand() % 1000);
        fillTree(size, root);
        balanced += isBalanced(root) ? 1 : 0;
    }

    printf("%d%% \n", balanced * 100 / TREES);
    return 0;
}
