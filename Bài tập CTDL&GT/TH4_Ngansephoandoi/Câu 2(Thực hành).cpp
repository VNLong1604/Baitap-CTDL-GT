#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class QueueInt {
private:
    int *arr;
    int front, rear, capacity;
public:
    QueueInt(int size = 100) {
        capacity = size;
        arr = new int[capacity];
        front = rear = -1;
    }
    ~QueueInt() { delete[] arr; }
    bool IsEmpty() { return front == -1; }
    bool IsFull() { return rear == capacity - 1; }
    void Enqueue(int value) {
        if (IsFull()) throw overflow_error("Queue is full");
        if (IsEmpty()) front = 0;
        arr[++rear] = value;
    }
    int Dequeue() {
        if (IsEmpty()) throw underflow_error("Queue is empty");
        int value = arr[front];
        if (front == rear) front = rear = -1;
        else front++;
        return value;
    }
    int Peek() {
        if (IsEmpty()) throw underflow_error("Queue is empty");
        return arr[front];
    }
    void Clear() { front = rear = -1; }
};

// (b) Xếp lịch cặp múa nam/nữ
void dance_pairing(queue<string>& males, queue<string>& females) {
    while (!males.empty() && !females.empty()) {
        cout << "Cặp: " << males.front() << " - " << females.front() << endl;
        males.pop(); females.pop();
    }
    if (!males.empty()) cout << "Nam còn chờ: " << males.size() << " người" << endl;
    if (!females.empty()) cout << "Nữ còn chờ: " << females.size() << " người" << endl;
}

// (c) Radix Sort sử dụng hàng đợi
void radix_sort(vector<int>& arr) {
    queue<int> buckets[10];
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        for (int num : arr) buckets[(num / exp) % 10].push(num);
        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

int main() {
    // Xếp lịch múa
    queue<string> males, females;
    males.push("Nam1"); males.push("Nam2"); males.push("Nam3");
    females.push("Nữ1"); females.push("Nữ2");
    dance_pairing(males, females);
    
    // Radix Sort
    vector<int> numbers = {170, 45, 75, 90, 802, 24, 2, 66};
    radix_sort(numbers);
    cout << "Dãy sau khi sắp xếp: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;
    return 0;
}
