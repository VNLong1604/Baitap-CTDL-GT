#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Hàm kiểm tra số nguyên tố
bool laSoNguyenTo(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int m, n;
    cout << "Nhập số dòng và số cột của ma trận: ";
    cin >> m >> n;

    vector<vector<int>> maTran(m, vector<int>(n));
    cout << "Nhập các phần tử của ma trận:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> maTran[i][j];
        }
    }

    // a. Tìm số nguyên tố lớn nhất
    int soNguyenToLonNhat = -1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (laSoNguyenTo(maTran[i][j])) {
                soNguyenToLonNhat = max(soNguyenToLonNhat, maTran[i][j]);
            }
        }
    }
    if (soNguyenToLonNhat != -1) {
        cout << "\nSố nguyên tố lớn nhất trong ma trận: " << soNguyenToLonNhat << endl;
    } else {
        cout << "\nKhông có số nguyên tố nào trong ma trận." << endl;
    }

    // b. Tìm những dòng có chứa giá trị nguyên tố
    cout << "\nCác dòng có chứa số nguyên tố: ";
    for (int i = 0; i < m; ++i) {
        bool coNguyenTo = false;
        for (int j = 0; j < n; ++j) {
            if (laSoNguyenTo(maTran[i][j])) {
                coNguyenTo = true;
                break;
            }
        }
        if (coNguyenTo) {
            cout << i << " ";
        }
    }
    cout << endl;

    // c. Tìm những dòng chỉ chứa các số nguyên tố
    cout << "Các dòng chỉ chứa số nguyên tố: ";
    for (int i = 0; i < m; ++i) {
        bool toanNguyenTo = true;
        for (int j = 0; j < n; ++j) {
            if (!laSoNguyenTo(maTran[i][j])) {
                toanNguyenTo = false;
                break;
            }
        }
        if (toanNguyenTo) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}