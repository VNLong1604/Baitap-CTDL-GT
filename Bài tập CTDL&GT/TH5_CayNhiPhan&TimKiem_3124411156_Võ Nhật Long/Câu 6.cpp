#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node* pLeft;
    struct node* pRight;
} NODE;

typedef NODE* TREE;

// Hàm tạo nút mới
NODE* createNode(int data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode == NULL) {
        printf("Không thể cấp phát bộ nhớ!\n");
        exit(1);
    }
    newNode->info = data;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

// Hàm chèn nút (cho mục đích tạo cây test)
TREE insert(TREE root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->info) {
        root->pLeft = insert(root->pLeft, data);
    } else {
        root->pRight = insert(root->pRight, data);
    }
    return root;
}

// Hàm tính số nút trong cây
int countNodes(TREE root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->pLeft) + countNodes(root->pRight);
}

// Hàm tính tổng giá trị các nút trong cây
int sumNodes(TREE root) {
    if (root == NULL) {
        return 0;
    }
    return root->info + sumNodes(root->pLeft) + sumNodes(root->pRight);
}

// Hàm giải phóng bộ nhớ cây
void freeTree(TREE root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->pLeft);
    freeTree(root->pRight);
    free(root);
}

int main() {
    // Tạo một cây nhị phân tìm kiếm để test
    TREE root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 2);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 20);

    printf("So nut trong cay: %d\n", countNodes(root));
    printf("Tong gia tri cac nut trong cay: %d\n", sumNodes(root));

    freeTree(root);
    return 0;
}