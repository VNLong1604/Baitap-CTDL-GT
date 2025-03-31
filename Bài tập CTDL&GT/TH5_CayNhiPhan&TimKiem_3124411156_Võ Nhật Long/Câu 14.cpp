#include <iostream>

// Định nghĩa cấu trúc node của danh sách liên kết
struct nodelist {
    int info;
    struct nodelist* pNext;
};
typedef struct nodelist NODELIST;

// Định nghĩa cấu trúc danh sách liên kết
struct list {
    NODELIST* pHead;
    NODELIST* pTail;
};
typedef struct list LIST;

// Định nghĩa cấu trúc node của cây nhị phân (giả định đã có)
struct node {
    int info;
    struct node* pLeft;
    struct node* pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

// Hàm khởi tạo danh sách liên kết
void Init(LIST& l) {
    l.pHead = l.pTail = nullptr;
}

// Hàm tạo một node mới cho danh sách liên kết
NODELIST* GetNode(int x) {
    NODELIST* p = new NODELIST;
    if (p == nullptr) {
        return nullptr;
    }
    p->info = x;
    p->pNext = nullptr;
    return p;
}

// Hàm thêm một node vào cuối danh sách liên kết
void AddTail(LIST& l, NODELIST* p) {
    if (l.pHead == nullptr) {
        l.pHead = l.pTail = p;
    } else {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Hàm duyệt cây theo thứ tự Right-Node-Left (RNL) và thêm các node vào danh sách
void RNL(TREE Root, LIST& l) {
    if (Root == nullptr) {
        return;
    }
    RNL(Root->pRight, l);
    NODELIST* p = GetNode(Root->info);
    if (p != nullptr) {
        AddTail(l, p);
    }
    RNL(Root->pLeft, l);
}

// Hàm xây dựng danh sách liên kết từ cây nhị phân (duyệt RNL)
void BuildList(TREE Root, LIST& l) {
    Init(l);
    RNL(Root, l);
}

// Hàm tạo một node mới cho cây nhị phân (cho mục đích test)
NODE* createTreeNode(int data) {
    NODE* newNode = new NODE;
    if (newNode == nullptr) {
        return nullptr;
    }
    newNode->info = data;
    newNode->pLeft = nullptr;
    newNode->pRight = nullptr;
    return newNode;
}

// Hàm chèn một node vào cây nhị phân tìm kiếm (cho mục đích test)
TREE insertTreeNode(TREE root, int data) {
    if (root == nullptr) {
        return createTreeNode(data);
    }
    if (data < root->info) {
        root->pLeft = insertTreeNode(root->pLeft, data);
    } else {
        root->pRight = insertTreeNode(root->pRight, data);
    }
    return root;
}

// Hàm in danh sách liên kết
void PrintList(LIST l) {
    NODELIST* current = l.pHead;
    while (current != nullptr) {
        std::cout << current->info << " ";
        current = current->pNext;
    }
    std::cout << std::endl;
}

// Hàm giải phóng bộ nhớ của danh sách liên kết
void FreeList(LIST& l) {
    NODELIST* current = l.pHead;
    while (current != nullptr) {
        NODELIST* next = current->pNext;
        delete current;
        current = next;
    }
    l.pHead = l.pTail = nullptr;
}

// Hàm giải phóng bộ nhớ của cây nhị phân
void FreeTree(TREE root) {
    if (root == nullptr) {
        return;
    }
    FreeTree(root->pLeft);
    FreeTree(root->pRight);
    delete root;
}

int main() {
    // Tạo một cây nhị phân tìm kiếm để test
    TREE root = nullptr;
    root = insertTreeNode(root, 10);
    root = insertTreeNode(root, 5);
    root = insertTreeNode(root, 15);
    root = insertTreeNode(root, 2);
    root = insertTreeNode(root, 7);
    root = insertTreeNode(root, 12);
    root = insertTreeNode(root, 20);

    // Khai báo và xây dựng danh sách liên kết từ cây
    LIST linkedList;
    BuildList(root, linkedList);

    std::cout << "Danh sach lien ket duoc xay dung tu cay (duyet RNL): ";
    PrintList(linkedList);

    // Giải phóng bộ nhớ
    FreeTree(root);
    FreeList(linkedList);

    return 0;
}