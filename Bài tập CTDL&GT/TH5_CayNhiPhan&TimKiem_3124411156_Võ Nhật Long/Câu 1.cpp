#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node của cây
typedef struct node
{
    int info;
    struct node *pLeft;
    struct node *pRight;
} NODE;

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

// Hàm chèn một node vào cây (ví dụ: chèn theo thứ tự tăng dần)
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

// Hàm đếm số lượng node trong cây
int DemNode(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = DemNode(Root->pLeft);
    int b = DemNode(Root->pRight);
    return (a + b + 1);
}

// Hàm tính tổng giá trị các node trong cây
int TongNode(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = TongNode(Root->pLeft);
    int b = TongNode(Root->pRight);
    return (a + b + Root->info);
}

// Hàm tính trung bình cộng các nút trong cây
float TinhTrungBinhCong(TREE Root) {
    int tong = TongNode(Root);
    int dem = DemNode(Root);
    if (dem == 0) {
        return 0;
    }
    return (float)tong / dem;
}

// Hàm đếm số lượng nút dương trong cây
int DemDuong(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = DemDuong(Root->pLeft);
    int b = DemDuong(Root->pRight);
    if (Root->info > 0) {
        return (a + b + 1);
    }
    return (a + b);
}

// Hàm tính tổng giá trị các nút dương trong cây
int TongDuong(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = TongDuong(Root->pLeft);
    int b = TongDuong(Root->pRight);
    if (Root->info > 0) {
        return (a + b + Root->info);
    }
    return (a + b);
}

// Hàm tính trung bình cộng các nút dương trong cây
float TinhTrungBinhCongDuong(TREE Root) {
    int tongDuong = TongDuong(Root);
    int demDuong = DemDuong(Root);
    if (demDuong == 0) {
        return 0;
    }
    return (float)tongDuong / demDuong;
}

// Hàm đếm số lượng nút âm trong cây
int DemAm(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = DemAm(Root->pLeft);
    int b = DemAm(Root->pRight);
    if (Root->info < 0) {
        return (a + b + 1);
    }
    return (a + b);
}

// Hàm tính tổng giá trị các nút âm trong cây
int TongAm(TREE Root) {
    if (Root == NULL) {
        return 0;
    }
    int a = TongAm(Root->pLeft);
    int b = TongAm(Root->pRight);
    if (Root->info < 0) {
        return (a + b + Root->info);
    }
    return (a + b);
}

// Hàm tính trung bình cộng các nút âm trong cây
float TinhTrungBinhCongAm(TREE Root) {
    int tongAm = TongAm(Root);
    int demAm = DemAm(Root);
    if (demAm == 0) {
        return 0;
    }
    return (float)tongAm / demAm;
}

// Hàm tính tỉ số R = a / b, với a là tổng các nút có giá trị dương, b là tổng các nút có giá trị âm
float TinhTySo(TREE Root) {
    int a = TongDuong(Root);
    int b = TongAm(Root);
    if (b == 0) {
        return 0;
    }
    return (float)a / b;
}

// Hàm giải phóng bộ nhớ cây (tránh rò rỉ bộ nhớ)
void freeTree(TREE root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->pLeft);
    freeTree(root->pRight);
    free(root);
}

int main() {
    // Tạo một cây nhị phân cho mục đích kiểm thử
    TREE root = NULL;
    root = insertNode(root, 5);
    root = insertNode(root, 2);
    root = insertNode(root, 8);
    root = insertNode(root, -1);
    root = insertNode(root, 4);
    root = insertNode(root, -3);
    root = insertNode(root, 7);

    printf("Trung binh cong cac nut trong cay: %.2f\n", TinhTrungBinhCong(root));
    printf("Trung binh cong cac nut duong trong cay: %.2f\n", TinhTrungBinhCongDuong(root));
    printf("Trung binh cong cac nut am trong cay: %.2f\n", TinhTrungBinhCongAm(root));
    printf("Ty so R (tong duong / tong am): %.2f\n", TinhTySo(root));

    // Giải phóng bộ nhớ cây
    freeTree(root);

    return 0;
}