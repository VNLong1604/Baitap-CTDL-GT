#include <iostream>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc của một nút trong cây AVL
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Hàm để lấy chiều cao của một nút
int getHeight(Node *n) {
    if (n == nullptr)
        return 0;
    return n->height;
}

// Hàm để lấy hệ số cân bằng của một nút
int getBalance(Node *n) {
    if (n == nullptr)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Hàm để cập nhật chiều cao của một nút
void updateHeight(Node *n) {
    if (n != nullptr) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }
}

// Hàm xoay trái
Node* rotateLeft(Node *z) {
    Node *y = z->right;
    Node *T2 = y->left;

    // Thực hiện xoay
    y->left = z;
    z->right = T2;

    // Cập nhật chiều cao
    updateHeight(z);
    updateHeight(y);

    return y;
}

// Hàm xoay phải
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Hàm THÊM một khóa vào cây AVL
Node* insertNode(Node* node, int key) {
    
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else // Các khóa trùng lặp không được phép trong BST
        return node;

    
    updateHeight(node);
      int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Hàm tìm nút có giá trị nhỏ nhất trong cây con
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Hàm XÓA một khóa khỏi cây AVL
Node* deleteNode(Node* root, int key) {
    // 1. Thực hiện xóa như cây BST thông thường
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Nút có một hoặc không có con
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            // Trường hợp không có con
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // Trường hợp có một con
                *root = *temp; // Sao chép nội dung của con

            delete temp;
        } else {
            // Nút có hai con: Tìm nút kế cận nhỏ nhất (trong cây con bên phải)
            Node* temp = minValueNode(root->right);

            // Sao chép giá trị kế cận nhỏ nhất vào nút này
            root->key = temp->key;

            // Xóa nút kế cận nhỏ nhất
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Nếu cây chỉ có một nút thì trả về
    if (root == nullptr)
        return root;

        updateHeight(root);

        int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Các hàm thao tác cây BST (không thay đổi)
Node* search(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

void preorderTraversal(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->key << " ";
    }
}

void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    Node* root = nullptr;

    // Sử dụng hàm insertNode để thêm các phần tử
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    root = insertNode(root, 25);

    cout << "Cây AVL sau khi thêm các phần tử:" << endl;
    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << endl;

    // Tìm kiếm một phần tử
    int searchKey = 15;
    if (search(root, searchKey) != nullptr) {
        cout << endl << "Đã tìm thấy phần tử " << searchKey << " trong cây." << endl;
    } else {
        cout << endl << "Không tìm thấy phần tử " << searchKey << " trong cây." << endl;
    }

    // Sử dụng hàm deleteNode để xóa một phần tử
    int deleteKey = 20;
    root = deleteNode(root, deleteKey);
    cout << endl << "Cây AVL sau khi xóa phần tử " << deleteKey << ":" << endl;
    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << endl;

    // Tìm kiếm lại phần tử đã xóa
    if (search(root, deleteKey) != nullptr) {
        cout << endl << "Đã tìm thấy phần tử " << deleteKey << " trong cây." << endl;
    } else {
        cout << endl << "Không tìm thấy phần tử " << deleteKey << " trong cây." << endl;
    }

    // Giải phóng bộ nhớ
    deleteTree(root);
    root = nullptr;

    return 0;
}