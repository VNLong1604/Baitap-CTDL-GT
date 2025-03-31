#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SoHang {
    double heSo;
    int bac;
};

bool soSanhBac(const SoHang& a, const SoHang& b) {
    return a.bac < b.bac;
}

int main() {
    int n;
    cout << "Nhập số lượng số hạng trong dãy: ";
    cin >> n;

    vector<SoHang> dayThuc(n);
    cout << "Nhập thông tin cho từng số hạng (hệ số bậc):\n";
    for (int i = 0; i < n; ++i) {
        cin >> dayThuc[i].heSo >> dayThuc[i].bac;
    }

    sort(dayThuc.begin(), dayThuc.end(), soSanhBac);

    cout << "\nDãy thức sau khi sắp xếp theo bậc tăng dần:\n";
    for (const auto& soHang : dayThuc) {
        cout << soHang.heSo << " " << soHang.bac << endl;
    }

    return 0;
}