#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút trong cây nhị phân
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Hàm xoay phải một nút
Node* rotateRight(Node* root) {
    if (!root || !root->left) return root;
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// Hàm xoay trái một nút
Node* rotateLeft(Node* root) {
    if (!root || !root->right) return root;
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

// Hàm in cây theo thứ tự trung tố
void inorderTraversal(Node* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

int main() {
    // Tạo cây như hình 1
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(3);
    root->left->right = new Node(9);
    root->left->right->left = new Node(7);
    root->right->left = new Node(12);
    root->right->right = new Node(18);
    root->right->right->left = new Node(16);
    root->right->right->right = new Node(20);

    cout << "Cay ban dau (Hinh 1): ";
    inorderTraversal(root);
    cout << endl;

    // Chuyển cây sang hình 2 bằng cách xoay
    root = rotateRight(root);
    root->right = rotateLeft(root->right);

    cout << "Cay sau khi chuyen doi (Hinh 2): ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}