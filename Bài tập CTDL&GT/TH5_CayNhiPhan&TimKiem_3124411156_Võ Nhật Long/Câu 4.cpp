#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node của cây
struct node {
    int info;
    struct node *pLeft;
    struct node *pRight;
};
typedef struct node NODE;
typedef NODE *TREE;

// Hàm tạo một node mới
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

// Hàm chèn một node vào cây nhị phân tìm kiếm
TREE insertNode(TREE root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->info) {
        root->pLeft = insertNode(root->pLeft, data);
    } else {
        root->pRight = insertNode(root->pRight, data);
    }
    return root;
}

// Hàm tìm node nhỏ nhất trong cây (hoặc cây con)
NODE* NhoNhat(TREE Root) {
    if (Root == NULL) {
        return NULL;
    }
    NODE* lc = Root;
    while (lc->pLeft) {
        lc = lc->pLeft;
    }
    return lc;
}

// Hàm tìm node lớn nhất trong cây (hoặc cây con)
NODE* LonNhat(TREE Root) {
    if (Root == NULL) {
        return NULL;
    }
    NODE* lc = Root;
    while (lc->pRight) {
        lc = lc->pRight;
    }
    return lc;
}

// Hàm in giá trị của một node (hỗ trợ cho việc kiểm tra)
void printNode(NODE* node) {
    if (node != NULL) {
        printf("%d", node->info);
    } else {
        printf("NULL");
    }
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
    // Tạo một cây nhị phân tìm kiếm với các giá trị 3, 5, 7, 9, 10, 12, 15, 18, 20
    TREE root = NULL;
    int values[] = {3, 5, 7, 9, 10, 12, 15, 18, 20};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insertNode(root, values[i]);
    }

    printf("Cay da tao (thu tu in tuyen tinh khong dam bao thu tu BST):\n");
    // Để minh họa, chúng ta không in theo thứ tự cụ thể,
    // mà chỉ tạo cây và tìm min/max.

    printf("\nTim node nho nhat:\n");
    NODE* minNode = NhoNhat(root);
    printf("Node nho nhat co gia tri: ");
    printNode(minNode);
    printf("\n");

    printf("\nTim node lon nhat:\n");
    NODE* maxNode = LonNhat(root);
    printf("Node lon nhat co gia tri: ");
    printNode(maxNode);
    printf("\n");

    // Giải phóng bộ nhớ cây
    freeTree(root);

    return 0;
}