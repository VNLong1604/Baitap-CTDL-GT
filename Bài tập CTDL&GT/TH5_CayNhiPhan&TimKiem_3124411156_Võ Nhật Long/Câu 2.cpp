#include <iostream>
#include <queue>

using namespace std;

// Định nghĩa cấu trúc nút cây
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Hàm để tạo cây theo Hình 1 (dựa trên cách hiểu cấu trúc)
Node* createTreeHinh1() {
    Node* root = new Node(10);

    Node* p1 = new Node(5);
    Node* p2 = new Node(15);

    root->left = p1;
    root->right = p2;

    p1->left = new Node(18); // Giả định nút có giá trị 18 bên trái của 5
    p1->right = new Node(18); // Giả định nút có giá trị 18 bên phải của 5
    p1->left->left = new Node(20); // Giả định nút có giá trị 20 là con trái của nút 18 bên trái

    p2->left = new Node(12);
    p2->right = new Node(9);
    p2->right->right = new Node(7); // Giả định nút có giá trị 7 là con phải của nút 9

    return root;
}

// Hàm để tạo cây theo Hình 2
Node* createTreeHinh2() {
    Node* root = new Node(10);

    root->left = new Node(15);
    root->right = new Node(5);

    root->left->left = new Node(18);
    root->left->right = new Node(12);
    root->left->left->left = new Node(20);

    root->right->right = new Node(9);
    root->right->right->right = new Node(7);

    return root;
}

// Hàm in cây theo mức (Level Order Traversal) để kiểm tra
void printLevelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();
            cout << current->value << " ";

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        cout << endl;
    }
}

// Hàm giải phóng bộ nhớ của cây (tránh memory leaks)
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Tạo cây theo Hình 1
    Node* rootHinh1 = createTreeHinh1();
    cout << "Cay Hình 1 (theo cách hiểu):" << endl;
    printLevelOrder(rootHinh1);
    cout << endl;

    // Tạo cây theo Hình 2
    Node* rootHinh2 = createTreeHinh2();
    cout << "Cay Hình 2:" << endl;
    printLevelOrder(rootHinh2);
    cout << endl;

    Node* cayDaChuyen = rootHinh2;
    cout << "Cây đã chuyển (là cây Hình 2):" << endl;
    printLevelOrder(cayDaChuyen);

    // Giải phóng bộ nhớ
    deleteTree(rootHinh1);
    deleteTree(rootHinh2);

    return 0;
}