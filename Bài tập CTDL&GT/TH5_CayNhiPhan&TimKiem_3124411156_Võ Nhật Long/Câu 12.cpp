#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Định nghĩa cấu trúc của một nút trong cây nhị phân
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Hàm duyệt cây theo phương pháp RNL (Right-Node-Left) không đệ quy
vector<int> rnlTraversal(Node* root) {
    vector<int> result;
    stack<Node*> st;
    Node* current = root;
    Node* lastVisited = nullptr; // Theo dõi nút cuối cùng đã được duyệt

    while (!st.empty() || current != nullptr) {
       
        while (current != nullptr) {
            st.push(current);
            current = current->right;
        }

        // Lấy nút trên cùng của stack
        Node* peekNode = st.top();

        
        if (peekNode->left != nullptr && peekNode->left != lastVisited) {
            // Nếu nút bên trái tồn tại và chưa được duyệt, di chuyển sang trái
            current = peekNode->left;
        } else {
           
            result.push_back(peekNode->data);
            lastVisited = peekNode;
            st.pop();
        }
    }
    return result;
}

int main() {
    // Tạo cây nhị phân như trong hình ảnh
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);

    root->left->left = new Node(3);
    root->left->right = new Node(9);
    root->right->left = new Node(12);
    root->right->right = new Node(18);

    root->left->right->left = new Node(7);
    root->right->right->right = new Node(20);

    // Thực hiện duyệt cây theo phương pháp RNL
    vector<int> rnlResult = rnlTraversal(root);

    // In kết quả duyệt cây
    cout << "Duyệt cây theo phương pháp RNL (giảm dần): ";
    for (int value : rnlResult) {
        cout << value << " ";
    }
    cout << endl;

    // Giải phóng bộ nhớ (quan trọng để tránh rò rỉ bộ nhớ)
    // (Trong một chương trình lớn, bạn nên có một hàm riêng để giải phóng cây)
    delete root->right->right->right;
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root;

    return 0;
}