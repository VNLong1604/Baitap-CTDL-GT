#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node của cây
struct node {
    float info;
    struct node* pLeft;
    struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

// Hàm tạo một node mới
NODE* createNode(float data) {
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
TREE insertNode(TREE root, float data) {
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

// Hàm duyệt NLR và lưu cây xuống file nhị phân
void NLR(TREE t, FILE* fp) {
    if (t == NULL)
        return;
    fwrite(&t->info, sizeof(float), 1, fp);
    NLR(t->pLeft, fp);
    NLR(t->pRight, fp);
}

// Hàm lưu cây nhị phân tìm kiếm xuống file
int Xuat(char *filename, TREE t) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
        return 0;
    NLR(t, fp);
    fclose(fp);
    return 1;
}

// Hàm đọc cây từ file nhị phân (tái tạo cây)
TREE Nhap(char *filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;
    TREE root = NULL;
    float data;
    while (fread(&data, sizeof(float), 1, fp) == 1) {
        
        fclose(fp);
        fp = fopen(filename, "rb");
        if (fp == NULL) return NULL;
        TREE restoredRoot = readTreeNLR(fp);
        fclose(fp);
        return restoredRoot;
    }
    fclose(fp);
    return NULL;
}

// Hàm đệ quy để đọc cây từ file theo thứ tự NLR
TREE readTreeNLR(FILE* fp) {
    float data;
    if (fread(&data, sizeof(float), 1, fp) == 1) {
        TREE newNode = createNode(data);
        newNode->pLeft = readTreeNLR(fp);
        newNode->pRight = readTreeNLR(fp);
        return newNode;
    }
    return NULL;
}

// Hàm giải phóng bộ nhớ cây
void freeTree(TREE root) {
    if (root == NULL)
        return;
    freeTree(root->pLeft);
    freeTree(root->pRight);
    free(root);
}

// Hàm in cây (In-order để kiểm tra thứ tự)
void inOrderTraversal(TREE root) {
    if (root != NULL) {
        inOrderTraversal(root->pLeft);
        printf("%.2f ", root->info);
        inOrderTraversal(root->pRight);
    }
}

int main() {
    // Tạo một cây nhị phân tìm kiếm các số thực
    TREE root = NULL;
    root = insertNode(root, 8.5);
    root = insertNode(root, 3.2);
    root = insertNode(root, 10.7);
    root = insertNode(root, 1.1);
    root = insertNode(root, 6.9);
    root = insertNode(root, 14.3);

    // Tên file để lưu cây
    const char* filename = "binary_tree.dat";

    // Lưu cây xuống file
    if (Xuat((char*)filename, root)) {
        printf("Cay da duoc luu xuong file '%s' (duyet NLR).\n", filename);
    } else {
        perror("Loi khi luu cay xuong file");
        freeTree(root);
        return 1;
    }

    // Giải phóng cây ban đầu
    freeTree(root);
    root = NULL;

    // Đọc cây từ file
    TREE restoredRoot = Nhap((char*)filename);

    if (restoredRoot != NULL) {
        printf("Cay da duoc doc tu file '%s'.\n", filename);
        printf("Cay da doc (duyet In-order): ");
        inOrderTraversal(restoredRoot);
        printf("\n");
        freeTree(restoredRoot);
    } else {
        perror("Loi khi doc cay tu file");
    }

    return 0;
}