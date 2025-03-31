#include <iostream>
using namespace std;

// Định nghĩa cấu trúc một nút trong danh sách liên kết
struct Node {
    int data; // Dữ liệu của nút
    Node* next; // Con trỏ trỏ tới nút kế tiếp
};

// Hàm khởi tạo danh sách liên kết rỗng
Node* TaoDS() {
    return NULL; // Danh sách ban đầu rỗng
}

// Hàm thêm một phần tử vào cuối danh sách
void ThemPT(Node*& head, int value) {
    Node* newNode = new Node{value, NULL}; // Tạo một nút mới
    if (!head) { // Nếu danh sách đang rỗng
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next; // Duyệt đến cuối danh sách
    temp->next = newNode; // Thêm nút mới vào cuối
}

// Hàm in danh sách
void InDS(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Hàm xóa một phần tử có giá trị k khỏi danh sách
void XoaSo(Node*& head, int k) {
    if (!head) return;
    while (head && head->data == k) { // Nếu phần tử đầu là k
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    Node* temp = head;
    while (temp && temp->next) {
        if (temp->next->data == k) { // Nếu tìm thấy k trong danh sách
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        } else {
            temp = temp->next;
        }
    }
}

// Hàm nối danh sách thứ hai vào cuối danh sách thứ nhất
void GopDS(Node*& list1, Node* list2) {
    if (!list1) {
        list1 = list2;
        return;
    }
    Node* temp = list1;
    while (temp->next) temp = temp->next;
    temp->next = list2;
}

int main() {
    Node* list1 = TaoDS();
    cout << "Nhập 10 số nguyên cho danh sách 1: "<<endl;
    for (int i = 0; i < 10; i++) {
        int x;
        cin >> x;
        ThemPT(list1, x);
    }
    
    cout << "Danh sách 1: ";
    InDS(list1);
    
    cout << "Nhập số cần xóa: ";
    int k;
    cin >> k;
    XoaSo(list1, k);
    
    cout << "Danh sách sau khi xóa " << k << ": ";
    InDS(list1);
    
    Node* list2 = TaoDS();
    cout << "Nhập 5 số nguyên cho danh sách 2: ";
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        ThemPT(list2, x);
    }
    
    GopDS(list1, list2);
    cout << "Danh sách 1 sau khi ghép danh sách 2: ";
    InDS(list1);
    
    return 0;
}