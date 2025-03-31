#include <iostream>

using namespace std;

// Định nghĩa cấu trúc node của cây nhị phân tìm kiếm
struct BST_NODE {
    int Key;        // Khóa của nút
    int So_lan;     // Số lần xuất hiện
    BST_NODE* Left;
    BST_NODE* Right;
};

// Định nghĩa cấu trúc cây nhị phân tìm kiếm
struct BST_TREE {
    BST_NODE* pRoot; // Nút gốc của cây
};

// Khởi tạo cây rỗng
void Init(BST_TREE& tree) {
    tree.pRoot = nullptr;
}

// Hàm tạo một node mới
BST_NODE* createNode(int key) {
    BST_NODE* newNode = new BST_NODE;
    if (newNode == nullptr) {
        return nullptr;
    }
    newNode->Key = key;
    newNode->So_lan = 1;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}

// Hàm chèn một node vào cây nhị phân tìm kiếm
void insertNode(BST_TREE& tree, int key) {
    if (tree.pRoot == nullptr) {
        tree.pRoot = createNode(key);
        return;
    }

    BST_NODE* current = tree.pRoot;
    while (true) {
        if (key == current->Key) {
            current->So_lan++;
            return;
        } else if (key < current->Key) {
            if (current->Left == nullptr) {
                current->Left = createNode(key);
                return;
            }
            current = current->Left;
        } else {
            if (current->Right == nullptr) {
                current->Right = createNode(key);
                return;
            }
            current = current->Right;
        }
    }
}

// Hàm tìm kiếm một node theo khóa
BST_NODE* searchNode(BST_NODE* root, int key) {
    if (root == nullptr || root->Key == key) {
        return root;
    }
    if (key < root->Key) {
        return searchNode(root->Left, key);
    }
    return searchNode(root->Right, key);
}

// Hàm xóa phần tử có khóa X
void deleteElement(BST_TREE& tree, int x) {
    BST_NODE* nodeToDelete = searchNode(tree.pRoot, x);
    if (nodeToDelete != nullptr) {
        if (nodeToDelete->So_lan > 1) {
            nodeToDelete->So_lan--;
            cout << "Da giam so lan xuat hien cua phan tu co khoa " << x << ".\n";
        } else {
            nodeToDelete->So_lan--;
            cout << "Da giam so lan xuat hien cua phan tu co khoa " << x << ". So lan xuat hien hien tai la 0.\n";
            // Lưu ý: Trong thực tế, bạn có thể muốn loại bỏ các node có So_lan = 0.
        }
    } else {
        cout << "Phan tu co khoa " << x << " khong ton tai trong cay.\n";
    }
}

// Hàm in cây theo thứ tự NLR (Node-Left-Right)
void printNLR(BST_NODE* root) {
    if (root != nullptr) {
        if (root->So_lan > 0) {
            cout << root->Key << "(" << root->So_lan << ") ";
        }
        printNLR(root->Left);
        printNLR(root->Right);
    }
}

// Hàm in các phần tử đang tồn tại trong cây theo thứ tự NLR
void printExistingElementsNLR(BST_TREE tree) {
    cout << "Cac phan tu dang ton tai trong cay (NLR): ";
    printNLR(tree.pRoot);
    cout << endl;
}

// Hàm giải phóng bộ nhớ cây (để tránh rò rỉ bộ nhớ)
void freeTree(BST_NODE* root) {
    if (root == nullptr) {
        return;
    }
    freeTree(root->Left);
    freeTree(root->Right);
    delete root;
}

int main() {
    BST_TREE t;
    Init(t);

    // Chèn các phần tử vào cây
    insertNode(t, 10);
    insertNode(t, 5);
    insertNode(t, 15);
    insertNode(t, 5);
    insertNode(t, 12);
    insertNode(t, 10);

    cout << "Cay ban dau:\n";
    printExistingElementsNLR(t);

    // Xóa phần tử
    deleteElement(t, 5);
    cout << "\nSau khi xoa phan tu co khoa 5:\n";
    printExistingElementsNLR(t);

    deleteElement(t, 10);
    cout << "\nSau khi xoa phan tu co khoa 10:\n";
    printExistingElementsNLR(t);

    deleteElement(t, 20); // Xóa phần tử không tồn tại
    cout << "\nSau khi xoa phan tu co khoa 20:\n";
    printExistingElementsNLR(t);

    deleteElement(t, 5); // Xóa tiếp phần tử có khóa 5
    cout << "\nSau khi xoa phan tu co khoa 5 lan nua:\n";
    printExistingElementsNLR(t);

    // Giải phóng bộ nhớ
    freeTree(t.pRoot);

    return 0;
}