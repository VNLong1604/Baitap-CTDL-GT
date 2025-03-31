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

// Hàm tính tổng số nút có một nhánh con (NLR)
int demNutMotConNLR(TREE root) {
    static int count = 0;
    if (root != NULL) {
        if ((root->pLeft != NULL && root->pRight == NULL) || (root->pLeft == NULL && root->pRight != NULL)) {
            count++;
        }
        demNutMotConNLR(root->pLeft);
        demNutMotConDeQuy(root->pRight); // Lỗi ở đây, nên gọi NLR
    }
    return count;
}

// Hàm tính tổng số nút có một nhánh con (Đệ quy)
int demNutMotConDeQuy(TREE root) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;
    if ((root->pLeft != NULL && root->pRight == NULL) || (root->pLeft == NULL && root->pRight != NULL)) {
        count = 1;
    }
    return count + demNutMotConDeQuy(root->pLeft) + demNutMotConDeQuy(root->pRight);
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
    // Tạo một cây nhị phân để test
    TREE root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 2);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 20);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 13);
    root = insert(root, 18);
    root = insert(root, 22);
    root = insert(root, 9); // Thêm nút có một con

    printf("So nut co mot nhanh con (duyet NLR): %d\n", demNutMotConNLR(root));

    // Reset biến static count nếu muốn gọi lại NLR cho cây khác
    // (Trong trường hợp này, không cần thiết vì chỉ gọi một lần)

    printf("So nut co mot nhanh con (de quy): %d\n", demNutMotConDeQuy(root));

    freeTree(root);
    return 0;
}