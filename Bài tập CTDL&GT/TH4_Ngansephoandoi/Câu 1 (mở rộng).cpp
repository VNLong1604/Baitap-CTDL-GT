#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// (a) Tính số Fibonacci đệ quy và khử đệ quy
int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n) {
    if (n <= 1) return n;
    stack<pair<int, int>> s;
    s.push({n, 0});
    int a = 0, b = 1;
    while (!s.empty()) {
        auto [num, step] = s.top(); s.pop();
        if (num <= 1) continue;
        if (step == 0) {
            s.push({num, 1});
            s.push({num - 1, 0});
        } else {
            int temp = a + b;
            a = b;
            b = temp;
        }
    }
    return b;
}

// (b) Đảo ngược số sử dụng đệ quy và khử đệ quy
int reverse_number_recursive(int n, int rev = 0) {
    if (n == 0) return rev;
    return reverse_number_recursive(n / 10, rev * 10 + n % 10);
}

int reverse_number_iterative(int n) {
    stack<int> s;
    while (n > 0) {
        s.push(n % 10);
        n /= 10;
    }
    int reversed = 0, multiplier = 1;
    while (!s.empty()) {
        reversed += s.top() * multiplier;
        s.pop();
        multiplier *= 10;
    }
    return reversed;
}

// (c) Giải bài toán Tháp Hà Nội
void hanoi_recursive(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "Di chuyển đĩa 1 từ " << from << " đến " << to << endl;
        return;
    }
    hanoi_recursive(n - 1, from, aux, to);
    cout << "Di chuyển đĩa " << n << " từ " << from << " đến " << to << endl;
    hanoi_recursive(n - 1, aux, to, from);
}

struct Move {
    int n;
    char from, to, aux;
    bool done;
};

void hanoi_iterative(int n) {
    stack<Move> s;
    s.push({n, 'A', 'C', 'B', false});
    while (!s.empty()) {
        Move &m = s.top();
        s.pop();
        if (m.n == 1) {
            cout << "Di chuyển đĩa 1 từ " << m.from << " đến " << m.to << endl;
        } else if (!m.done) {
            s.push({m.n - 1, m.aux, m.to, m.from, false});
            s.push({1, m.from, m.to, m.aux, true});
            s.push({m.n - 1, m.from, m.aux, m.to, false});
        } else {
            cout << "Di chuyển đĩa " << m.n << " từ " << m.from << " đến " << m.to << endl;
        }
    }
}

int main() {
    int n = 5;
    cout << "Fibonacci(" << n << ") đệ quy: " << fibonacci_recursive(n) << endl;
    cout << "Fibonacci(" << n << ") khử đệ quy: " << fibonacci_iterative(n) << endl;
    
    int num = 1234;
    cout << "Số đảo ngược của " << num << " đệ quy: " << reverse_number_recursive(num) << endl;
    cout << "Số đảo ngược của " << num << " khử đệ quy: " << reverse_number_iterative(num) << endl;
    
    int disks = 3;
    cout << "\nTháp Hà Nội đệ quy:\n";
    hanoi_recursive(disks, 'A', 'C', 'B');
    
    cout << "\nTháp Hà Nội khử đệ quy:\n";
    hanoi_iterative(disks);
    return 0;
}
