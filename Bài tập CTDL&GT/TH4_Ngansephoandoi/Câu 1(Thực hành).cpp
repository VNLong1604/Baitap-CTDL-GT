#include <iostream>
#include <stack>
#include <string>
using namespace std;

class StackInt {
private:
    int *arr;
    int top;
    int capacity;
public:
    StackInt(int size = 100) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }
    ~StackInt() { delete[] arr; }
    bool IsEmpty() { return top == -1; }
    bool IsFull() { return top == capacity - 1; }
    void PushStack(int value) {
        if (IsFull()) throw overflow_error("Stack is full");
        arr[++top] = value;
    }
    int PopStack() {
        if (IsEmpty()) throw underflow_error("Stack is empty");
        return arr[top--];
    }
    int PeekStack() {
        if (IsEmpty()) throw underflow_error("Stack is empty");
        return arr[top];
    }
    void Clear() { top = -1; }
};

// (b) Đảo số sử dụng stack
int reverse_number(int n) {
    StackInt stack;
    while (n > 0) {
        stack.PushStack(n % 10);
        n /= 10;
    }
    int reversed_n = 0, multiplier = 1;
    while (!stack.IsEmpty()) {
        reversed_n += stack.PopStack() * multiplier;
        multiplier *= 10;
    }
    return reversed_n;
}

// (c) Kiểm tra xâu đối xứng
bool is_palindrome(const string &str) {
    StackInt stack(str.length());
    for (char ch : str) stack.PushStack(ch);
    string reversed_str = "";
    while (!stack.IsEmpty()) reversed_str += stack.PopStack();
    return str == reversed_str;
}

// (d) Chuyển số thập phân sang nhị phân
string decimal_to_binary(int n) {
    if (n == 0) return "0";
    StackInt stack;
    while (n > 0) {
        stack.PushStack(n % 2);
        n /= 2;
    }
    string result = "";
    while (!stack.IsEmpty()) result += to_string(stack.PopStack());
    return result;
}

// (e) Chuyển biểu thức trung tố sang hậu tố và tính toán
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
string infix_to_postfix(const string &expr) {
    StackInt stack(expr.length());
    string output = "";
    for (char ch : expr) {
        if (isalnum(ch)) output += ch;
        else if (ch == '(') stack.PushStack(ch);
        else if (ch == ')') {
            while (!stack.IsEmpty() && stack.PeekStack() != '(') output += stack.PopStack();
            stack.PopStack();
        } else {
            while (!stack.IsEmpty() && precedence(stack.PeekStack()) >= precedence(ch))
                output += stack.PopStack();
            stack.PushStack(ch);
        }
    }
    while (!stack.IsEmpty()) output += stack.PopStack();
    return output;
}
int evaluate_postfix(const string &expr) {
    StackInt stack(expr.length());
    for (char ch : expr) {
        if (isdigit(ch)) stack.PushStack(ch - '0');
        else {
            int b = stack.PopStack(), a = stack.PopStack();
            if (ch == '+') stack.PushStack(a + b);
            else if (ch == '-') stack.PushStack(a - b);
            else if (ch == '*') stack.PushStack(a * b);
            else if (ch == '/') stack.PushStack(a / b);
        }
    }
    return stack.PopStack();
}

int main() {
    cout << "Đảo số 1234: " << reverse_number(1234) << endl;
    cout << "Kiểm tra xâu 'radar': " << (is_palindrome("radar") ? "Đúng" : "Sai") << endl;
    cout << "Chuyển 10 sang nhị phân: " << decimal_to_binary(10) << endl;
    string exp = "3+(2*5)";
    string postfix_exp = infix_to_postfix(exp);
    cout << "Biểu thức hậu tố của '" << exp << "': " << postfix_exp << endl;
    cout << "Giá trị biểu thức: " << evaluate_postfix(postfix_exp) << endl;
    return 0;
}
